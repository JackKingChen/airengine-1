#include "AirCommonSystemManager.h"

namespace	Air{
	namespace	Common{


		ISystemManager::ISystemManager(AString	strTypeName){
			m_strName		=	strTypeName;
			m_pActiveSys	=	NULL;
		}

		ISystemManager::~ISystemManager(){

		}

		Air::U1 ISystemManager::Initialization(){
			if(m_pActiveSys!=NULL){
				return	m_pActiveSys->Initialization();
			}else{
				SystemListItr	i	=	m_lstSystem.begin();
				for(;i!=m_lstSystem.end();i++){
					m_pActiveSys	=	(ISystem*)(*i);
					if(m_pActiveSys!=NULL){
						return	m_pActiveSys->Initialization();
					}
				}
			}
			return	false;
		}

		Air::U1 ISystemManager::Release(){
			if(m_pActiveSys!=NULL){
				m_pActiveSys->Release();
				m_pActiveSys	=	NULL;
			}
			SystemListItr	i	=	m_lstSystem.begin();
			for(;i!=m_lstSystem.end();i++){
				m_pActiveSys	=	(ISystem*)(*i);
				if(m_pActiveSys!=NULL){
					SAF_D(m_pActiveSys)
				}
			}
			m_lstSystem.clear();
			return	true;
		}

		void ISystemManager::SwitchSystem( ISystem* pSys ){
			ISystem*	pOldSys	=	m_pActiveSys;
			ISystem*	pNewSys	=	pSys;
			if(m_pListener!=NULL){
				m_pListener->BeforeSwitchSystem(this,pOldSys,pNewSys);
			}
			if(m_pActiveSys!=NULL){
				m_pActiveSys->Stop();
				m_pActiveSys->Release();
			}
			m_pActiveSys	=	pSys;
			if(m_pListener!=NULL){
				m_pListener->OnSwitchSystem(this,pOldSys,pNewSys);
			}
			if(m_pActiveSys!=NULL){
				m_pActiveSys->Initialization();
				m_pActiveSys->Start();
			}
			if(m_pListener!=NULL){
				m_pListener->BeforeSwitchSystem(this,pOldSys,pNewSys);
			}
		}

		Air::Common::SystemList ISystemManager::GetSystemList(){
			return	m_lstSystem;
		}

		void ISystemManager::AddSystem( ISystem* pSys ){
			if(pSys!=NULL)
				m_lstSystem.push_back(pSys);
		}

		void ISystemManager::RemoveSystem( ISystem* pSys ){
			if(pSys!=NULL)
				m_lstSystem.remove(pSys);
			//�����ǰ����ϵͳΪ�Ƴ���ϵͳ �򽫼���ϵͳָ��Ϊ��
			if(pSys	==	m_pActiveSys){
				m_pActiveSys->Release();
				m_pActiveSys	=	NULL;
			}
		}

		SystemManagerGroup::SystemManagerGroup(){

		}

		SystemManagerGroup::~SystemManagerGroup(){

		}

		void SystemManagerGroup::AddSystem( ISystem* pSys,U1	bInitWhenNewManager ){
			if(pSys==NULL)
				return;

			AString	strType	=	pSys->GetType();

			SystemManagerMapItr	i	=	m_mapSystemMgr.find(strType);
			if(i!=m_mapSystemMgr.end()){
				ISystemManager*	pSystemMgr	=	i->second;
				if(pSystemMgr!=NULL)
					pSystemMgr->AddSystem(pSys);
			}else{
				ISystemManager*	pSystemMgr	=	new	ISystemManager(strType);
				//���ü���
				pSystemMgr->SetListener(this);
				//���ϵͳ
				pSystemMgr->AddSystem(pSys);
				//�����б�
				m_mapSystemMgr[strType]	=	pSystemMgr;
				m_lstSystemMgr.push_back(pSystemMgr);

				if(bInitWhenNewManager){
					pSystemMgr->Initialization();
				}

			}

		}

		void SystemManagerGroup::AddSystemManager( ISystemManager* pSystemMgr ,U1	bInit){
			if(pSystemMgr==NULL)
				return;
			AString	strTypeName	=	pSystemMgr->GetName();
			if(strTypeName.empty()){
				return;
			}
			//����Ѿ����� ���Ƴ�
			SystemManagerMapItr	i	=	m_mapSystemMgr.find(strTypeName.c_str());
			if(i!=m_mapSystemMgr.end()){
				ISystemManager*	pSysMgr	=	i->second;
				m_lstSystemMgr.remove(pSysMgr);
				if(pSysMgr!=NULL){
					pSysMgr->Release();
					SAF_D(pSysMgr);
				}
				m_mapSystemMgr.erase(i);
			}

			//���ü���
			pSystemMgr->SetListener(this);
			//�����б�
			m_mapSystemMgr[strTypeName.c_str()]	=	pSystemMgr;
			m_lstSystemMgr.push_back(pSystemMgr);

			if(bInit){
				pSystemMgr->Initialization();
			}
		}

		void SystemManagerGroup::RemoveSystemManager( ISystemManager* pSystemMgr ){
			if(pSystemMgr==NULL)
				return;
			AString	strTypeName	=	pSystemMgr->GetName();
			if(strTypeName.empty()){
				return;
			}
			//����Ѿ����� ���Ƴ�
			SystemManagerMapItr	i	=	m_mapSystemMgr.find(strTypeName.c_str());
			if(i!=m_mapSystemMgr.end()){
				ISystemManager*	pSysMgr	=	i->second;
				m_lstSystemMgr.remove(pSysMgr);
				if(pSysMgr!=NULL){
					pSysMgr->Release();
					SAF_D(pSysMgr);
				}
				m_mapSystemMgr.erase(i);
			}
		}

		Air::U1 SystemManagerGroup::InitAllSystemManager(){
			SystemManagerListItr	i	=	m_lstSystemMgr.begin();
			for(;i!=m_lstSystemMgr.end();i++){
				ISystemManager*	pSysMgr	=	(ISystemManager*)(*i);
				if(pSysMgr!=NULL){
					pSysMgr->Initialization();
				}

			}
			return	true;
		}

		Air::U1 SystemManagerGroup::ReleaseAllSystemManager(){
			//�����ͷ�
			SystemManagerList::reverse_iterator	i	=	m_lstSystemMgr.rbegin();
			for(;i!=m_lstSystemMgr.rend();i++){
				ISystemManager*	pSysMgr	=	(ISystemManager*)(*i);
				if(pSysMgr!=NULL){
					pSysMgr->Release();
					SAF_D(pSysMgr);
				}
				
			}
			m_lstSystemMgr.clear();
			m_mapSystemMgr.clear();
			return	true;
		}

		void SystemManagerGroup::RemoveSystem( ISystem* pSys ){
			if(pSys==NULL)
				return;
			
			SystemManagerMapItr	i	=	m_mapSystemMgr.find(pSys->GetType().c_str());
			if(i!=m_mapSystemMgr.end()){
				ISystemManager*	pSystemMgr	=	i->second;
				if(pSystemMgr!=NULL){
					pSystemMgr->RemoveSystem(pSys);
				}
			}
		}

		Air::U1 SystemManagerGroup::StartAllSystemManager(){
			SystemManagerListItr	i	=	m_lstSystemMgr.begin();
			for(;i!=m_lstSystemMgr.end();i++){
				ISystemManager*	pSysMgr	=	(ISystemManager*)(*i);
				if(pSysMgr!=NULL){
					ISystem*	pSys	=	pSysMgr->GetActiveSystem();
					if(pSys!=NULL){
						pSys->Start();
					}
				}

			}
			return	true;
		}

		Air::U1 SystemManagerGroup::StopAllSystemManager(){
			SystemManagerListItr	i	=	m_lstSystemMgr.begin();
			for(;i!=m_lstSystemMgr.end();i++){
				ISystemManager*	pSysMgr	=	(ISystemManager*)(*i);
				if(pSysMgr!=NULL){
					ISystem*	pSys	=	pSysMgr->GetActiveSystem();
					if(pSys!=NULL){
						pSys->Stop();
					}
				}

			}
			return	true;
		}
	}
}