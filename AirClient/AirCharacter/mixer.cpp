//****************************************************************************//
// mixer.cpp                                                                  //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "error.h"
#include "mixer.h"
#include "coremodel.h"
#include "corebone.h"
#include "coreanimation.h"
#include "model.h"
#include "skeleton.h"
#include "bone.h"
#include "animation.h"
#include "animation_action.h"
#include "animation_cycle.h"

 /*****************************************************************************/
/** Constructs the mixer instance.
  *
  * This function is the default constructor of the mixer instance.
  *****************************************************************************/

CalMixer::CalMixer(CalModel* pModel)
{
  assert(pModel);

  m_pModel = pModel;

  // build the animation table
  int coreAnimationCount = m_pModel->getCoreModel()->getCoreAnimationCount();

  m_vectorAnimation.reserve(coreAnimationCount);
  CalAnimation* null = 0;
  m_vectorAnimation.insert(m_vectorAnimation.begin(), coreAnimationCount, null);

  // set the animation time/duration values to default
  m_animationTime = 0.0f;
  m_animationDuration = 0.0f;
  m_timeFactor = 1.0f;
}

 /*****************************************************************************/
/** Destructs the mixer instance.
  *
  * This function is the destructor of the mixer instance.
  *****************************************************************************/

CalMixer::~CalMixer()
{
  // destroy all active animation actions
  while(!m_listAnimationAction.empty())
  {
    CalAnimationAction *pAnimationAction = m_listAnimationAction.front();
    m_listAnimationAction.pop_front();

    delete pAnimationAction;
  }

  // destroy all active animation cycles
  while(!m_listAnimationCycle.empty())
  {
    CalAnimationCycle *pAnimationCycle;
    pAnimationCycle = m_listAnimationCycle.front();
    m_listAnimationCycle.pop_front();

    delete pAnimationCycle;
  }

  // clear the animation table
  m_vectorAnimation.clear();

  m_pModel = 0;
}

///
/// Examines the given animation and if the first and last poses do not match
/// up, the first key frame is duplicated and added to the end of the animation
/// to ensure smooth looping.
///
static void addExtraKeyframeForLoopedAnim(CalCoreAnimation* anim)
{
  unsigned num_poses = anim->getPoses().size() / anim->getTrackCount();

  // Get the first pose
  std::vector<CalTransform> first_pose;
  first_pose.resize(anim->getTrackCount());
  anim->getPose(0.0f, first_pose);

  // Get the last pose
  std::vector<CalTransform> last_pose;
  last_pose.resize(anim->getTrackCount());
  anim->getPose(anim->getDuration(), last_pose);

  // Check if the first and last keyframes do not match
  bool needs_extra_keyframe = false;
  unsigned last_pose_start = (num_poses * anim->getTrackCount()) + anim->getTrackCount() - 1;
  for (unsigned track = 0; track < anim->getTrackCount(); ++track)
  {
    if (first_pose[track] != last_pose[track])
    {
      needs_extra_keyframe = true;
      break;
    }
  }

  // Add the first key frame on as a new end key frame if necessary to make the
  // looping smooth.
  if (needs_extra_keyframe)
  {
    std::vector<CalTransform> poses = anim->getPoses();
    for (unsigned track = 0; track < anim->getTrackCount(); ++track)
    {
      poses.push_back(first_pose[track]);
    }

    anim->setPoses(poses, anim->getTrackCount());
  }
}

 /*****************************************************************************/
/** Interpolates the weight of an animation cycle.
  *
  * This function interpolates the weight of an animation cycle to a new value
  * in a given amount of time. If the specified animation cycle is not active
  * yet, it is activated.
  *
  * @param id The ID of the animation cycle that should be blended.
  * @param weight The weight to interpolate the animation cycle to.
  * @param delay The time in seconds until the new weight should be reached.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalMixer::blendCycle(int id, float weight, float delay)
{
  if((id < 0) || (id >= (int)m_vectorAnimation.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // get the animation for the given id
  CalAnimation *pAnimation = m_vectorAnimation[id];

  // create a new animation instance if it is not active yet
  if(pAnimation == 0)
  {
    // take the fast way out if we are trying to clear an inactive animation
    if(weight == 0.0f) return true;

    // get the core animation
    CalCoreAnimation *pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(id);
    if(pCoreAnimation == 0) return false;

    // Ensure that the animation's first and last key frame match for proper
    // looping.
    ::addExtraKeyframeForLoopedAnim(pCoreAnimation);

    // allocate a new animation cycle instance
    CalAnimationCycle *pAnimationCycle = new CalAnimationCycle(pCoreAnimation);
    if(pAnimationCycle == 0)
    {
      CalError::setLastError(CalError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
      return false;
    }

    // insert new animation into the tables
    m_vectorAnimation[id] = pAnimationCycle;
    m_listAnimationCycle.push_front(pAnimationCycle);

    // blend the animation
    return pAnimationCycle->blend(weight, delay);
  }

  // check if this is really a animation cycle instance
  if(pAnimation->getType() != CalAnimation::TYPE_CYCLE)
  {
      CalError::setLastError(CalError::INVALID_ANIMATION_TYPE, __FILE__, __LINE__);
      return false;
  }

  // clear the animation cycle from the active vector if the target weight is zero
  if(weight == 0.0f)
  {
      m_vectorAnimation[id] = 0;
  }

  // cast it to an animation cycle
  CalAnimationCycle *pAnimationCycle;
  pAnimationCycle = (CalAnimationCycle *)pAnimation;

  // blend the animation cycle
  pAnimationCycle->blend(weight, delay);
  pAnimationCycle->checkCallbacks(0,m_pModel);
  return true;
}

 /*****************************************************************************/
/** Fades an animation cycle out.
  *
  * This function fades an animation cycle out in a given amount of time.
  *
  * @param id The ID of the animation cycle that should be faded out.
  * @param delay The time in seconds until the the animation cycle is
  *              completely removed.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool CalMixer::clearCycle(int id, float delay)
{
  // check if the animation id is valid
  if((id < 0) || (id >= (int)m_vectorAnimation.size()))
  {
    CalError::setLastError(CalError::INVALID_HANDLE, __FILE__, __LINE__);
    return false;
  }

  // get the animation for the given id
  CalAnimation *pAnimation;
  pAnimation = m_vectorAnimation[id];

  // we can only clear cycles that are active
  if(pAnimation == 0) return true;

  // check if this is really a animation cycle instance
  if(pAnimation->getType() != CalAnimation::TYPE_CYCLE)
  {
      CalError::setLastError(CalError::INVALID_ANIMATION_TYPE, __FILE__, __LINE__);
      return false;
  }

  // clear the animation cycle from the active vector
  m_vectorAnimation[id] = 0;

  // cast it to an animation cycle
  CalAnimationCycle *pAnimationCycle;
  pAnimationCycle = (CalAnimationCycle *)pAnimation;

  // set animation cycle to async state
  pAnimationCycle->setAsync(m_animationTime, m_animationDuration);

  // blend the animation cycle
  pAnimationCycle->blend(0.0f, delay);
  pAnimationCycle->checkCallbacks(0, m_pModel);
  return true;
}

/*****************************************************************************/
/** Executes an animation action.
  *
  * This function executes an animation action.
  *
  * @param id The ID of the animation action that should be blended.
  * @param delayIn The time in seconds until the animation action reaches the
  *                full weight from the beginning of its execution.
  * @param delayOut The time in seconds in which the animation action reaches
  *                 zero weight at the end of its execution.
  * @param weightTarget The weight to interpolate the animation action to.
  * @param autoLock     This prevents the Action from being reset and removed
  *                     on the last keyframe if true.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/
bool CalMixer::executeAction(int id, float delayIn, float delayOut, float weightTarget, bool autoLock)
{
  // get the core animation
  CalCoreAnimation *pCoreAnimation;
  pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(id);
  if(pCoreAnimation == 0)
  {
    return false;
  }

  // allocate a new animation action instance
  CalAnimationAction *pAnimationAction = new CalAnimationAction(pCoreAnimation);
  if(pAnimationAction == 0)
  {
    CalError::setLastError(CalError::MEMORY_ALLOCATION_FAILED, __FILE__, __LINE__);
    return false;
  }

  // insert new animation into the table
  m_listAnimationAction.push_front(pAnimationAction);

  // execute the animation
  pAnimationAction->execute(delayIn, delayOut, weightTarget, autoLock);
  pAnimationAction->checkCallbacks(0, m_pModel);
  return true;
}

/*****************************************************************************/
/** Clears an active animation action.
  *
  * This function removes an animation action from the blend list.  This is
  * particularly useful with auto-locked actions on their last frame.
  *
  * @param id The ID of the animation action that should be removed.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happened or action was not found
  *****************************************************************************/
bool CalMixer::removeAction(int id)
{
  // get the core animation
  CalCoreAnimation *pCoreAnimation;
  pCoreAnimation = m_pModel->getCoreModel()->getCoreAnimation(id);
  if(pCoreAnimation == 0)
  {
    return false;
  }

  // update all active animation actions of this model
  std::list<CalAnimationAction *>::iterator iteratorAnimationAction;
  iteratorAnimationAction = m_listAnimationAction.begin();

  while(iteratorAnimationAction != m_listAnimationAction.end())
  {
    // find the specified action and remove it
    if((*iteratorAnimationAction)->getCoreAnimation() == pCoreAnimation )
    {
        // found, so remove
      (*iteratorAnimationAction)->completeCallbacks(m_pModel);
      delete (*iteratorAnimationAction);
      iteratorAnimationAction = m_listAnimationAction.erase(iteratorAnimationAction);
      return true;
    }
    iteratorAnimationAction++;
  }
  return false;
}

 /*****************************************************************************/
/** Updates all active animations.
  *
  * This function updates all active animations of the mixer instance for a
  * given amount of time.
  *
  * @param deltaTime The elapsed time in seconds since the last update.
  *****************************************************************************/

void CalMixer::updateAnimation(float deltaTime)
{
  // update the current animation time
  if(m_animationDuration == 0.0f)
  {
    m_animationTime = 0.0f;
  }
  else
  {
    m_animationTime += deltaTime * m_timeFactor;
    if(m_animationTime >= m_animationDuration || m_animationTime<0)
    {
      m_animationTime = (float) fmod(m_animationTime, m_animationDuration);
    }
	if (m_animationTime < 0)
      m_animationTime += m_animationDuration;

  }

  // update all active animation actions of this model
  std::list<CalAnimationAction *>::iterator iteratorAnimationAction;
  iteratorAnimationAction = m_listAnimationAction.begin();

  while(iteratorAnimationAction != m_listAnimationAction.end())
  {
    // update and check if animation action is still active
    if((*iteratorAnimationAction)->update(deltaTime))
    {
      (*iteratorAnimationAction)->checkCallbacks((*iteratorAnimationAction)->getTime(),m_pModel);
      ++iteratorAnimationAction;
    }
    else
    {
      // animation action has ended, destroy and remove it from the animation list
      (*iteratorAnimationAction)->completeCallbacks(m_pModel);
      delete (*iteratorAnimationAction);
      iteratorAnimationAction = m_listAnimationAction.erase(iteratorAnimationAction);
    }
  }

  // todo: update all active animation poses of this model

  // update the weight of all active animation cycles of this model
  std::list<CalAnimationCycle *>::iterator iteratorAnimationCycle;
  iteratorAnimationCycle = m_listAnimationCycle.begin();

  float accumulatedWeight, accumulatedDuration;
  accumulatedWeight = 0.0f;
  accumulatedDuration = 0.0f;

  while(iteratorAnimationCycle != m_listAnimationCycle.end())
  {
    // update and check if animation cycle is still active
    if((*iteratorAnimationCycle)->update(deltaTime))
    {
      // check if it is in sync. if yes, update accumulated weight and duration
      if((*iteratorAnimationCycle)->getState() == CalAnimation::STATE_SYNC)
      {
        accumulatedWeight += (*iteratorAnimationCycle)->getWeight();
        accumulatedDuration += (*iteratorAnimationCycle)->getWeight() * (*iteratorAnimationCycle)->getCoreAnimation()->getDuration();
      }

      (*iteratorAnimationCycle)->checkCallbacks(m_animationTime,m_pModel);
      ++iteratorAnimationCycle;
    }
    else
    {
      // animation cycle has ended, destroy and remove it from the animation list
      (*iteratorAnimationCycle)->completeCallbacks(m_pModel);
      delete (*iteratorAnimationCycle);
      iteratorAnimationCycle = m_listAnimationCycle.erase(iteratorAnimationCycle);
    }
  }

  // adjust the global animation cycle duration
  if(accumulatedWeight > 0.0f)
  {
    m_animationDuration = accumulatedDuration / accumulatedWeight;
  }
  else
  {
    m_animationDuration = 0.0f;
  }
}

void CalMixer::updateSkeleton()
{
  // get the skeleton we need to update
  CalSkeleton *pSkeleton;
  pSkeleton = m_pModel->getSkeleton();
  if(pSkeleton == 0) return;

  // clear the skeleton state
  pSkeleton->clearState();

  // get the bone vector of the skeleton
  std::vector<CalBone *>& vectorBone = pSkeleton->getVectorBone();

  // loop through all animation actions
  std::list<CalAnimationAction *>::iterator iteratorAnimationAction;
  for(iteratorAnimationAction = m_listAnimationAction.begin(); iteratorAnimationAction != m_listAnimationAction.end(); ++iteratorAnimationAction)
  {
    // get the core animation instance
    CalCoreAnimation *pCoreAnimation;
    pCoreAnimation = (*iteratorAnimationAction)->getCoreAnimation();

    // Ask the animation for the pose at the given time
    std::vector<CalTransform> pose;
    pose.resize(pCoreAnimation->getTrackCount());
    pCoreAnimation->getPose((*iteratorAnimationAction)->getTime(), pose);

    // Blend the pose into the current bone states
    for (unsigned bone_id = 0; bone_id < pSkeleton->getCoreSkeleton()->getVectorCoreBone().size(); ++bone_id)
    {
      int track_number = pCoreAnimation->getTrackAssignment(bone_id);

      // Skip this bone if the bone does not have a track assigned in the animation
      if (track_number == -1)
      {
        continue;
      }

      // Blend the animation pose with the skeleton
      CalBone* pBone = vectorBone[bone_id];
      pBone->blendState((*iteratorAnimationAction)->getWeight(), pose[track_number].getTranslation(), pose[track_number].getRotation());
    }
  }

  // lock the skeleton state
  pSkeleton->lockState();

  // loop through all animation cycles
  std::list<CalAnimationCycle *>::iterator iteratorAnimationCycle;
  for(iteratorAnimationCycle = m_listAnimationCycle.begin(); iteratorAnimationCycle != m_listAnimationCycle.end(); ++iteratorAnimationCycle)
  {
    // get the core animation instance
    CalCoreAnimation *pCoreAnimation;
    pCoreAnimation = (*iteratorAnimationCycle)->getCoreAnimation();

    // calculate adjusted time
    float animationTime;
    if((*iteratorAnimationCycle)->getState() == CalAnimation::STATE_SYNC)
    {
      if(m_animationDuration == 0.0f)
      {
        animationTime = 0.0f;
      }
      else
      {
        animationTime = m_animationTime * pCoreAnimation->getDuration() / m_animationDuration;
      }
    }
    else
    {
      animationTime = (*iteratorAnimationCycle)->getTime();
    }

    // Ask the animation for the pose at the given time
    std::vector<CalTransform> pose;
    pose.resize(pCoreAnimation->getTrackCount());
    pCoreAnimation->getPose(animationTime, pose);

    // Blend the pose into the current bone states
    for (unsigned index = 0; index < pose.size(); ++index)
    {
      int track_number = pCoreAnimation->getTrackAssignment(index);

      // Skip this bone if the bone does not have a track assigned in the animation
      if (track_number == -1)
      {
        continue;
      }

      CalBone* pBone = vectorBone[index];
      pBone->blendState((*iteratorAnimationCycle)->getWeight(), pose[track_number].getTranslation(), pose[track_number].getRotation());
    }
  }

  // lock the skeleton state
  pSkeleton->lockState();

  // let the skeleton calculate its final state
  pSkeleton->calculateState();
}

/*****************************************************************************/
/** Returns the animation time.
  *
  * This function returns the animation time of the mixer instance.
  *
  * @return The animation time in seconds.
  *****************************************************************************/


float CalMixer::getAnimationTime()
{
	return m_animationTime;
}

/*****************************************************************************/
/** Returns the animation duration.
  *
  * This function returns the animation duration of the mixer instance.
  *
  * @return The animation duration in seconds.
  *****************************************************************************/


float CalMixer::getAnimationDuration()
{
	return m_animationDuration;
}


/*****************************************************************************/
/** Sets the animation time.
  *
  * This function sets the animation time of the mixer instance.
  *
  *****************************************************************************/


void CalMixer::setAnimationTime(float animationTime)
{
	m_animationTime=animationTime;
}

/*****************************************************************************/
/** Set the time factor.
  * 
  * This function sets the time factor of the mixer instance.
  * this time factor affect only sync animation
  *
  *****************************************************************************/


void CalMixer::setTimeFactor(float timeFactor)
{
    m_timeFactor = timeFactor;
}

/*****************************************************************************/
/** Get the time factor.
  * 
  * This function return the time factor of the mixer instance.
  *
  *****************************************************************************/

float CalMixer::getTimeFactor()
{
    return m_timeFactor;
}

/*****************************************************************************/
/** Get the model.
  * 
  * This function return the CalModel of the mixer instance.
  *
  *****************************************************************************/

CalModel *CalMixer::getCalModel() 
{ 
    return m_pModel; 
} 

/*****************************************************************************/
/** Get the animation vector.
  * 
  * This function return the animation vector of the mixer instance.
  *
  *****************************************************************************/

std::vector<CalAnimation *> & CalMixer::getAnimationVector() 
{ 
    return m_vectorAnimation; 
} 

/*****************************************************************************/
/** Get the list of the action animation.
  * 
  * This function return the list of the action animation of the mixer instance.
  *
  *****************************************************************************/

std::list<CalAnimationAction *> & CalMixer::getAnimationActionList() 
{ 
    return m_listAnimationAction; 
}

/*****************************************************************************/
/** Get the list of the cycle animation.
  * 
  * This function return the list of the cycle animation of the mixer instance.
  *
  *****************************************************************************/

std::list<CalAnimationCycle *> & CalMixer::getAnimationCycle() 
{ 
    return m_listAnimationCycle; 
} 

//****************************************************************************//
