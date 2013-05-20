#include "AirGameThirdControl.h"
#include "AirGameSection.h"
#include "OIS.h"
#include "AirGameSystem.h"
#include "AirEngineScene.h"
#include "AirEngineSceneNode.h"
#include "AirGlobalSetting.h"

using namespace OIS;
namespace Air{
	

		namespace	Game{
	
			AString	ThirdControl::ProductTypeName="ThirdControl";
			ThirdControl::ThirdControl( CAString& strName,Info* pInfo )	:
				FPSControl(strName,pInfo){
				m_fMinCameraDis	=	3.0f;
				m_fMaxCameraDis	=	40.0f;
				m_fCurrentDis	=	20.0f;
				m_fTargetDis	=	m_fCurrentDis;
				m_vTargetPosition	=	m_Info.vPosition;
				m_fMoveSensitivity	=	3.0f;
			}
	
			U1 ThirdControl::Create(){
				Engine::Scene*			pScene	=	m_Info.pSection->GetScene();
				//Audio::IScene*	pAScene	=	m_Info.pSection->GetAudioScene();
				//Physx::IScene*	pXScene	=	m_Info.pSection->GetPhysxScene();
	
				m_pNode				=	pScene->GetRootNode()->CreateChildSceneNode();
				m_pNode->SetPosition(m_Info.vPosition);
				m_pNode->SetName("ThirdControl_Node");

				m_vMoveDirection	=	Float3(0,0,0);
				

				m_pCamera	=	m_Info.pCamera;

				Float3 vDir(0,-1,1);
				vDir.Normalize();
				Float3 vCameraPos	=	m_Info.vPosition	+	Float3(0,1.5,0)	-vDir*m_fCurrentDis;	
				m_pCamera->SetPosition(vCameraPos);
				m_pCamera->SetDir(vDir);
				
	
				return	true;
			}
	
			U1 ThirdControl::Destroy(){
				Engine::Scene*			pScene	=	m_Info.pSection->GetScene();

// 				}
				return	true;
			}
	
			U1 ThirdControl::Update(const FrameTime& frameTime){
	
				Real	fTimeDelta	=	frameTime.fTimeDelta;//Engine::GetGlobalSetting().m_ShaderParam.m_fTimeDelta;
				//计算灵敏度
				Real	fSensitivity		=	fTimeDelta*m_fMoveSensitivity;
	
				Float3	vDir	=	m_pCamera->GetRealDirection();
				Float3	vRight	=	m_pCamera->GetRealRightDirection();
	
	
				//更新摄像机距离
				m_fCurrentDis	+=	(m_fTargetDis-m_fCurrentDis)*fSensitivity;
				
				if(m_Info.bAllowRotate){
					//更新摄像机方向
					m_fCurrentLRAngle	+=	(m_fLRAngle	-	m_fCurrentLRAngle)*fSensitivity;
					m_fCurrentUDAngle	+=	(m_fUDAngle	-	m_fCurrentUDAngle)*fSensitivity;
					Float4	qY	=	Float4(Float3(0,1,0),(m_fCurrentLRAngle));
					m_pNode->SetQuat(qY);
				
	
	
					Float4	qX	=	Float4(Float3(1,0,0),(m_fCurrentUDAngle));

				}
					
				m_LastState		=	m_State;
				m_LastMoveState	=	m_MoveState;
				m_State		=	enAS_Stand;	
				m_MoveState	=	0;
				Float4	vMove	=	Float4(0,0,0,0);
				int iFB	=0;int iLR=0;
				if(m_pInputState->m_KeyArray[KC_W]==1){
					vMove.x	=	1.0f;
					iFB	=	1;
				}
				if(m_pInputState->m_KeyArray[KC_S]==1){
					vMove.y	=	-1.0f;
					iFB	-=	1;
				}
				if(m_pInputState->m_KeyArray[KC_A]==1){
					vMove.z	=	-1.0f;
					iLR=-1;
				}
				if(m_pInputState->m_KeyArray[KC_D]==1){
					vMove.z	=	1.0f;
					iLR+=1;
				}

				if(iFB==1){
					m_MoveState	|=	enMS_Run;
				}else if(iFB==-1){
					m_MoveState	|=	enMS_Back;
				}

				if(iLR==1){
					m_MoveState	|=	enMS_Right;
				}else if(iLR==-1){
					m_MoveState	|=	enMS_Left;
				}

				if(IsStateChange()	&&	m_pActionStateCallback!=NULL){
					m_pActionStateCallback->OnActorState(m_State,(enumMoveState)m_MoveState);
				}
	
	
				vDir.Normalize();
				vRight.Normalize();
				Float3	vMoveDir	=	vDir*(vMove.x+vMove.y)	+	vRight*(vMove.z+vMove.w);
				vMoveDir.y=0.0f;
				vMoveDir.Normalize();

				Float3	vCurrentPos	=	m_pNode->GetPosition();
				vCurrentPos			+=	vMoveDir*fSensitivity;
				m_pNode->SetPosition(vCurrentPos);
				m_pCamera->SetPosition(vCurrentPos+Float3(0,1.5,0)	-vDir*m_fCurrentDis);
					
					return true;
			}
			bool ThirdControl::mouseMoved( const OIS::MouseEvent &arg ){
	
				if(m_Info.bAllowRotate	&&	m_pInputState->m_MouseArray[OIS::MB_Right]){
					float fTimeDelta =	GetTimer().m_FrameTime.fTimeDelta;
	
					Real fXDelta	=	Real(arg.state.X.rel) * 0.9f;
					Real fYDelta	=	Real(arg.state.Y.rel) * 0.9f;	
	
					m_fLRAngle	+=	fXDelta*fTimeDelta;
					m_fUDAngle	+=	-fYDelta*fTimeDelta;
	
					if(m_fUDAngle	>=	1.57f)m_fUDAngle	=	1.56f;
					if(m_fUDAngle	<=	-1.57f)m_fUDAngle	=	-1.56f;
	
				}
	
				m_fTargetDis	-=	GetTimer().m_FrameTime.fTimeDelta*arg.state.Z.rel*0.5f;
				if(m_fTargetDis<m_fMinCameraDis)
					m_fTargetDis	=	m_fMinCameraDis;
				if(m_fTargetDis>m_fMaxCameraDis)
					m_fTargetDis	=	m_fMaxCameraDis;
				return	true;
			}
	
			bool ThirdControl::keyReleased( const OIS::KeyEvent &arg ){
				if(arg.key	==	OIS::KC_ESCAPE){
					m_pActionStateCallback->OnGameState(enExit);
				}
				using namespace OIS;
				if(m_pActionStateCallback!=NULL){
					enumAction	act	=	enA_None;
					switch(arg.key){
						case	KC_SPACE:act	=	enA_SpaceAction;
							break;
						case	KC_1:act		=	enA_MagicAttack1;
							break;					  
						case	KC_2:act		=	enA_MagicAttack2;
							break;					  
						case	KC_3:act		=	enA_MagicAttack3;
							break;					  
						case	KC_4:act		=	enA_MagicAttack4;
							break;					  
						case	KC_5:act		=	enA_MagicAttack5;
							break;
					
					}
					if(act!=enA_None){
						m_pActionStateCallback->OnAction(act);
					}
				}
				return	true;
			}
	
		}
};