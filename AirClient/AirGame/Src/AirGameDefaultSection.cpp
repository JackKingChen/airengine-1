#include "AirGameDefaultSection.h"
#include "AirGameFreeControl.h"

namespace	Air{
	namespace	Game{

		AString	DefaultSection::ProductTypeName="DefaultSection";
		DefaultSection::DefaultSection( CAString& strName ):Section(strName)
		{
			m_pModel	=	NULL;
			m_pParticle	=		NULL;
			m_fShootTime	=	0.0f;
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

			Engine::Particle::Info parInfo;
			parInfo.strTemplate	=	"Billboard";
			m_pParticle=Engine::ParticleSystem::GetSingleton()->CreateProduct<Engine::Particle>("123",&parInfo);
			m_pParticle->EnableEmitter(false);
			m_pModel->attachObject("Ref_Weapon",m_pParticle);
			
			m_pControl->RegisterKeyCallback(OIS::KC_ESCAPE,this,ConverertFunction(&DefaultSection::OnESC));
			m_pControl->RegisterMouseCallback(OIS::MB_Left,this,ConverertFunction(&DefaultSection::OnFireStart),enKET_MouseDown);
			m_pControl->RegisterMouseCallback(OIS::MB_Left,this,ConverertFunction(&DefaultSection::OnFireEnd),enKET_MouseUp);
			return true;
		}

		Air::U1 DefaultSection::Destroy()
		{
			if(m_pParticle!=NULL){
				if(m_pModel!=NULL)
					m_pModel->detachObject(m_pParticle);
				SAFE_RELEASE_REF(m_pParticle);
			}
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

		void	__stdcall DefaultSection::OnFireEnd( const Key& k )
		{
			
			m_pParticle->EnableEmitter(false);
		}

		void	__stdcall DefaultSection::OnFireStart( const Key& k )
		{
			m_pModel->PlayAction("shootlow.CAF",0.05);
			m_pParticle->EnableEmitter(true);
			m_fShootTime	=	0.0f;
		}

		Control* DefaultSection::OnCreateControl()
		{
			ThirdControl::Info info;
			info.bAllowRotate	=	false;
			info.pSection		=	this;
			info.pCamera		=	m_pScene->GetMainCamera();
			info.vPosition		=	Float3(0,-0.15,0);
			return GameSystem::GetSingleton()->CreateProduct<ThirdControl>(m_strProductName+"_ThirdControl",&info);
		}

		void DefaultSection::Update( const FrameTime& fFrameTime )
		{
			__super::Update(fFrameTime);
			if(m_pParticle->IsEmitterEnable()){
				m_fShootTime+=fFrameTime.fTimeDelta;
				if(m_fShootTime>0.5f){
					m_fShootTime-=0.5f;
					m_pModel->PlayAction("shootlow.CAF",0.0);
				}
			}
			
			POINT	p;
			p.x	=	Engine::GetGlobalSetting().m_pInputSystem->m_iX;
			p.y	=	Engine::GetGlobalSetting().m_pInputSystem->m_iY;//arg.state.Y.abs;

			RECT	r;
			GetClientRect(Engine::GetGlobalSetting().m_EngineParam.hWnd,&r);

			POINT	size;
			size.x	=	r.right		-	r.left;
			size.y	=	r.bottom	-	r.top;

			Ray	ray	=	m_pScene->GetMainCamera()->BuildRay(p.x/(float)size.x,p.y/(float)size.y);

			{
				Float3 Pos	=	ray.m_vStart	+	ray.m_vDirection*ray.m_vStart.y/abs(ray.m_vDirection.y);
				Float3 vDir	=	Pos	-	m_pControl->GetControlNode()->GetPosition()*Float3(1,0,1);
				vDir.Normalize();
				float fDot =	acos(vDir.Dot(Float3(0,0,1)));
				//Float3 vAxis	=	Float3(0,0,1).Cross(vDir).Normalize();
				if(vDir.x < 0){
					fDot*=-1;
				}
				m_pControl->GetControlNode()->SetQuat(Float4(Float3(0,1,0),fDot));
				
			}
		}

		AString	EditorSection::ProductTypeName="EditorSection";
		Control* EditorSection::OnCreateControl()
		{
			FreeControl::Info info;
			info.bAllowRotate	=	false;
			info.pSection		=	this;
			info.pCamera		=	m_pScene->GetMainCamera();
			
			return GameSystem::GetSingleton()->CreateProduct<FreeControl>(m_strProductName+"_FreeControl",&info);
		}

		Air::U1 EditorSection::Create()
		{
			 __super::Create();

			 return	true;
		}

		Air::U1 EditorSection::Destroy()
		{

			return __super::Destroy();
		}

		EditorSection::EditorSection( CAString& strName ):Section(strName)
		{

		}

	}
}