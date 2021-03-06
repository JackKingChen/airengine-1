#include "AirAudioScene.h"
#include "AirAudioGlobal.h"

#include "AirAudioSound.h"
namespace Air{
	
	namespace	Engine{
		namespace	Audio{
	
	
			Scene::Scene( AString strName ){
				m_strName	=	strName;
				m_pCamera	=	NULL;
			}
	
	
			void Scene::Update(){
				UpdateListener(m_pCamera);
	
	// 			ISound*	pDeleteSound	=	NULL;
	// 
	// 			IFactory*	pFactory	=	GetFactory("Sound");
	// 			if(pFactory!=NULL){
	// 				IFactory::ProductList&	lst	=	pFactory->GetProductList();
	// 				IFactory::ProductListItr	i	=	lst.begin();
	// 				for(;i!=lst.end();i++){
	// 					IProduct*	pProduct	=	i->second;//(IProduct*)(*i->);
	// 					ISound*		pSound		=	dynamic_cast<ISound*>(pProduct);
	// 					if(pSound!=NULL){
	// 						if(pSound->GetRepeatCount()<0){
	// 							pDeleteSound	=	pSound;
	// 							break;
	// 						}else{
	// 							pSound->UpdateSound();
	// 						}
	// 					}
	// 				}
	// 				if(pDeleteSound!=NULL){
	// 					ISceneNode*	pParentNode	=	pDeleteSound->GetParentSceneNode();
	// 					if(pParentNode!=NULL){
	// 						pParentNode->detachObject(pDeleteSound);
	// 					}
	// 					DestroyProduct(pDeleteSound);
	// 				}
	// 			}
				
			}
	
			U1 Scene::Initialization(){
				
				return	true;
			}
	
			U1 Scene::Release(){
				StopAllSound();
				DestroyAllFactory();
				return true;
			}
	
			void Scene::SetCamera( Camera* pCamera ){
				m_pCamera	=	pCamera;
				UpdateListener(m_pCamera);
			}
	
			void Scene::UpdateListener( Camera* pCamera ){
				if(pCamera!=NULL){
					Float3	vUp		=	pCamera->GetRealUpDirection();
					Float3	vDir	=	pCamera->GetRealDirection();
					Float3	vPos	=	pCamera->GetRealPosition();
					//更新听者的位置
					alListener3f(AL_POSITION, vPos.x,vPos.y,vPos.z);
					float v[6];
					v[0] = -vDir.x;
					v[1] = -vDir.y;
					v[2] = -vDir.z;
					v[3] = vUp.x;
					v[4] = vUp.y;
					v[5] = vUp.z;
					//更新听者的面向和顶方向
					alListenerfv(AL_ORIENTATION, v);
				}
			}
	
			ISound* Scene::Play( ISound::Info* pInfo ){
				if(pInfo==NULL)
					return	NULL;
				ISound*	pSound	=	CreateProduct<ISound>(pInfo->strName,pInfo);
				if(pSound!=NULL)
					pSound->Play();
				return	pSound;
			}
	
			void Scene::StopAllSound(){
				IFactory*	pFactory	=	GetFactory("Sound");
				if(pFactory!=NULL){
					const IFactory::ProductMap&	lst	=	pFactory->GetProductList();
					IFactory::ProductMap::const_iterator	i	=	lst.begin();
					for(;i!=lst.end();i++){
						IProduct*	pProduct	=	i->second;//(IProduct*)(*i->);
						ISound*		pSound		=	static_cast<ISound*>(pProduct);
						if(pSound!=NULL){
							pSound->Stop();
						}
					}
				}
			}
	
			void Scene::DestroyAllSound(){
				IFactory*	pFactory	=	GetFactory("Sound");
				if(pFactory!=NULL){
					pFactory->DestroyAllProduct();
				}
			}
		}
	}
};