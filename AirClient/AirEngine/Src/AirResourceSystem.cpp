#include "AirResourceSystem.h"
#include "AirResourcePackage.h"
namespace	Air{
	namespace	Engine{
		namespace	Resource{
			

			System::System(){
				m_uiMaxRecycle	=	100*1024*1024;
				m_uiRecycleSize	=	0;

				m_uiLoadIndex	=	0;
				m_uiUnloadLoadIndex	=	0;
			}

			Air::U1 System::Initialization(){
				//Start();

				AddFactory(new	NoParamFactory<Stream>());
				AddFactory(new	NoParamFactory<Package>());
				return	true;
			}

			Air::U1 System::Release(){

				//�������
// 				m_UnLoadCS.Enter();
// 
// 				m_uiRecycleSize	=	0;
// 				ProductList::iterator	i	=	m_lstUnLoad.begin();
// 				for(;i!=m_lstUnLoad.end();i++){
// 					(*i)->ReleaseRef();
// 				}
// 				m_lstUnLoad.clear();
// 				m_UnLoadCS.Enter();

				m_LoadCS.Enter();

				StreamList::iterator	i	=	m_lstLoad[0].begin();
				for(;i!=m_lstLoad[0].end();i++){
					(*i)->ReleaseRef();
				}
				i	=	m_lstLoad[1].begin();
				for(;i!=m_lstLoad[1].end();i++){
					(*i)->ReleaseRef();
				}

				m_lstLoad[0].clear();
				m_lstLoad[1].clear();
				m_LoadCS.Enter();

				m_lstPackage.clear();

				//�ݻ�������Դ
				DestroyAllProduct();
				DestroyAllFactory();

				return	true;
			}

			void System::FindWithPostfix( CAString& strPostfix,FindFileCallback* pCB ){
				PackageList::iterator	i	=	m_lstPackage.begin();
				for(;i!=m_lstPackage.end();i++){
					Package*	p	=	(Package*)(*i);
					if(p!=NULL){
						p->FindWithPostfix(strPostfix,pCB);
					}
				}
			}

			Air::U1 System::AddPackage( CAString& strPackageName ){
				if(strPackageName.empty())
					return	false;

				Package*	p	=	NULL;

				if(strPackageName.size()	<	4){
					p	=	CreateProduct<Package>(strPackageName);

				}else{
					AString	strPostfix	=	Converter::ToLowerCase(Common::GetPostfix(strPackageName));
					if(strPostfix.empty()||	strPostfix[0]=='/'||strPostfix[0]=='\\'){
						p	=	CreateProduct<Package>(strPackageName);
					}else{
						p	=	CreateProduct<Package>(strPackageName,strPostfix);
					}
				}

				if(p!=NULL){
					m_lstPackage.push_back(p);
				}
				return	true;
			}

			bool System::RepetitionRun(){
				Stream*	pFile	=	NULL;

				Sleep(100);

				U32	uiLoadIdx	=	m_uiLoadIndex&1;
				StreamList::iterator	i	=	m_lstLoad[uiLoadIdx].begin();
				if(i!=m_lstLoad[uiLoadIdx].end()){
					if((*i)->GetRefCount()	>	1)
						(*i)->ForceLoad();
					(*i)->ReleaseRef();
				}
				m_lstLoad->clear();
				//���ȼ����ļ�
				m_LoadCS.Enter();
				uiLoadIdx++;
				m_LoadCS.Leave();

// 				//������ؿ���ʱ ж���ļ�
// 				if(pFile==NULL){
// 					IProduct*	pProduct	=	NULL;
// 					m_UnLoadCS.Enter();
// 					ProductList::iterator	itr	=	m_lstUnLoad.begin();
// 					if(itr!=m_lstUnLoad.end()){
// 						if(m_uiRecycleSize	>=	m_uiMaxRecycle){
// 							m_uiRecycleSize	-=	pFile->GetSize();
// 							pProduct	=	*itr;
// 							m_lstUnLoad.erase(itr);
// 						}
// 					}
// 					m_UnLoadCS.Leave();
// 					//����
// 					if(pProduct!=NULL)
// 						pProduct->ReleaseRef();
// 					return	true;
// 				}
// 
// 				//��û�м������� Ҳû��ж������ ����Ϣ
// 				if(pFile==NULL){
// 					Sleep(10);
// 				}else{
// 					//һ�ֿ����� һ���ļ������̨���ض���	���ǻ�û�е���������ʱ�� �û��ֶ�ǿ�ƽ����˼���	����Ͳ�����μ�����
// 					if(pFile->GetState()	==	enSS_UnLoad){
// 						//ǿ�Ƽ���
// 						pFile->ForceLoad();
// 					}
// 					//����һ�����ü���	
// 					pFile->ReleaseRef();
// 				}
				return	true;
			}

			Air::U1 System::LoadBackground( Stream* pFile ){
				if(pFile==NULL)
					return	false;
				//�����һ�����ü���	��ֹ���ڼ��صĹ����� ����ж��
				pFile->AddRef();
				m_LoadCS.Enter();
				U32	uiLoadIndex	=	(m_uiLoadIndex+1)&1;
				m_lstLoad[uiLoadIndex].push_back(pFile);
				m_LoadCS.Leave();

				return	true;
			}

			Air::U1 System::PushRecycle( IProduct* p ){
				if(p==NULL)
					return	false;
				m_UnLoadCS.Enter();
// 				m_uiRecycleSize	+=	p->GetSize();
// 				m_lstUnLoad.push_back(p);
				m_UnLoadCS.Leave();
				return	true;
			}

			Air::U32 System::Find( CAString& strFileName,Data& outData ){
				//ת��ΪСд
				AString	str	=	strFileName;
				Converter::ToLowerCase(str);

				PackageList::iterator	i	=	m_lstPackage.begin();
				for(;i!=m_lstPackage.end();i++){
					Package*	p	=	(Package*)(*i);
					if(p!=NULL){
						U32	uiSize	=	p->Find(str,outData);
						if(uiSize!=0)
							return	uiSize;

					}
				}

				return	0;
			}

			Air::U32 System::Find( CAString& strFileName ){
				//PackageList::iterator	i	=	m_lstPackage.begin();
				//for(;i!=m_lstPackage.end();i++){
				//	Package*	p	=	(Package*)(*i);
				//	if(p!=NULL){
				//		U32	uiSize	=	p->Find(strFileName);
				//		if(uiSize!=0)
				//			return	uiSize;

				//	}
				//}
				return	0;
			}

			void System::SetMaxRecycleSize( U32 uiSize ){
				m_uiMaxRecycle	=	uiSize;
			}	

			Air::U32 System::GetMaxRecycleSize(){
				return	m_uiMaxRecycle;
			}

			Air::U1 System::GetFileModifyTime( CAString& strFileName,FILETIME* p )
			{
				AString	str	=	strFileName;
				Converter::ToLowerCase(str);

				PackageList::iterator	i	=	m_lstPackage.begin();
				for(;i!=m_lstPackage.end();i++){
					Package*	pkg	=	(Package*)(*i);
					if(pkg!=NULL){
						U1	bOK	=	pkg->GetFileModifyTime(str,p);
						if(bOK)
							return bOK;

					}
				}
				return false;
			}

		}
	}
}