//****************************************************************************//
// loader.h                                                                   //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_LOADER_H
#define CAL_LOADER_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//


#include <string>
#include <istream>
#include "global.h"
#include "datasource.h"
#include "coreanimation.h"
#include "corematerial.h"
#include "coremesh.h"
#include "coreskeleton.h"
#include "transform.h"

//****************************************************************************//
// Forward declarations                                                       //
//****************************************************************************//

class CalCoreModel;
class CalCoreBone;
class CalCoreSubmesh;

enum
{
    LOADER_ROTATE_X_AXIS = 1,
    LOADER_INVERT_V_COORD = 2,
    LOADER_FLIP_WINDING = 4
};

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

 /*****************************************************************************/
/** The loader class.
  *****************************************************************************/

class CAL3D_API CalLoader
{
// member functions
public:
  static CalCoreAnimationPtr loadCoreAnimation(const std::string& strFilename, CalCoreSkeleton *skel=NULL);
  static CalCoreMaterialPtr  loadCoreMaterial(const std::string& strFilename);
  static CalCoreMeshPtr      loadCoreMesh(const std::string& strFilename);
  static CalCoreSkeletonPtr  loadCoreSkeleton(const std::string& strFilename);

  static CalCoreAnimationPtr loadCoreAnimation(std::istream& inputStream, CalCoreSkeleton *skel=NULL);
  static CalCoreMaterialPtr  loadCoreMaterial(std::istream& inputStream);
  static CalCoreMeshPtr      loadCoreMesh(std::istream& inputStream);
  static CalCoreSkeletonPtr  loadCoreSkeleton(std::istream& inputStream);

  static CalCoreAnimationPtr loadCoreAnimation(void* inputBuffer, CalCoreSkeleton *skel=NULL);
  static CalCoreMaterialPtr  loadCoreMaterial(void* inputBuffer);
  static CalCoreMeshPtr      loadCoreMesh(void* inputBuffer);
  static CalCoreSkeletonPtr  loadCoreSkeleton(void* inputBuffer);

  static CalCoreAnimationPtr loadCoreAnimation(CalDataSource& inputSrc, CalCoreSkeleton *skel=NULL);
  static CalCoreMaterialPtr  loadCoreMaterial(CalDataSource& inputSrc);
  static CalCoreMeshPtr      loadCoreMesh(CalDataSource& inputSrc);
  static CalCoreSkeletonPtr  loadCoreSkeleton(CalDataSource& inputSrc);

  static void setLoadingMode(int flags);

private:
  static CalCoreBone *loadCoreBones(CalDataSource& dataSrc);
  static bool loadCoreKeyframe(CalDataSource& dataSrc, CalTransform& coordSys);
  static CalCoreSubmesh *loadCoreSubmesh(CalDataSource& dataSrc);
  static int loadCoreTrack(CalDataSource& dataSrc, CalCoreSkeleton *skel, std::vector<CalTransform>& trackOut);

  static CalCoreAnimationPtr loadXmlCoreAnimation(const std::string& strFilename, CalCoreSkeleton *skel=NULL);
  static CalCoreSkeletonPtr loadXmlCoreSkeleton(const std::string& strFilename);
  static CalCoreMeshPtr loadXmlCoreMesh(const std::string& strFilename);
  static CalCoreMaterialPtr loadXmlCoreMaterial(const std::string& strFilename);

  static int loadingMode;
};

#endif

//****************************************************************************//
