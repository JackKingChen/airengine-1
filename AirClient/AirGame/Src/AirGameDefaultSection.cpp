#include "AirGameDefaultSection.h"

namespace	Air{
	namespace	Game{


		DefaultSection::DefaultSection( CAString& strName ):Section(strName)
		{
			m_pModel	=	NULL;
		}

		Air::U1 DefaultSection::Create()
		{
			__super::Create();
			AnimationModel::Info info;
			info.strTemplate	=	"��ǹ��";

			m_pModel	=	EngineSystem::GetSingleton()->CreateProduct<AnimationModel>("I",&info);
			if(m_pModel!=NULL){
				m_pControl->GetControlNode()->CreateChildSceneNode(Float3(0,0,0),Float4(Float3(-1,0,0),1.57))->attachObject(m_pModel);
				m_pModel->SetActionState("stand.CAF");
			}
			
			m_pControl->RegisterKeyCallback(OIS::KC_ESCAPE,this,ConverertFunction(&DefaultSection::OnESC));
			return true;
		}

		Air::U1 DefaultSection::Destroy()
		{
			if(m_pModel!=NULL){
				m_pModel->GetParentSceneNode()->detachObject(m_pModel);
				m_pControl->GetControlNode()->RemoveChild(m_pModel->GetParentSceneNode(),TRUE);
				SAFE_RELEASE_REF(m_pModel);
			}
			return __super::Destroy();
		}

		void DefaultSection::OnActorState( enumActorState state,enumMoveState mstate )
		{
			if(mstate	==	enMS_NoMove){
				m_pModel->SetActionState("stand.CAF");
			}else{
				switch(mstate){
					case	enMS_Left		:{
						m_pModel->SetActionState("runleft.CAF");
											 }break;
					case	enMS_Right		:{
						m_pModel->SetActionState("runright.CAF");
											 }break;
					case	enMS_Run		:{
						m_pModel->SetActionState("run.CAF");
											 }break;
					case	enMS_Back		:{
						m_pModel->SetActionState("runback.CAF");
											 }break;
					case	enMS_RunLeft	:{
						m_pModel->SetActionState("runleft.CAF","run.CAF");
											 }break;
					case	enMS_RunRight	:{
						m_pModel->SetActionState("runright.CAF","run.CAF");
											 }break;
					case	enMS_BackLeft	:{
						m_pModel->SetActionState("runbackleft.CAF","runback.CAF");
											 }break;
					case	enMS_BackRight	:{
						m_pModel->SetActionState("runbackright.CAF","runback.CAF");
											 }break;
				}
			}
		}

		void DefaultSection::OnAction( enumAction action )
		{

		}

		void DefaultSection::OnGameState( enumGameState state )
		{

		}

		void	__stdcall DefaultSection::OnESC( const Key& k )
		{

				OutputDebugStringA("esc\n");
			
		}

	}
}