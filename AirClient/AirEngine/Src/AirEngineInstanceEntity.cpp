#include "AirEngineInstanceEntity.h"
#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
namespace Air{
	
	namespace	Engine{
	
	
		InstanceEntity::InstanceEntity(CAString&	strName,UInt	uiMaxInstance):Common::IProduct(strName){

			m_uiInstanceCount		=	uiMaxInstance;
			m_pModelVertexBuff		=	NULL;
			m_pInstanceVertexBuff	=	NULL;
			m_uiInstanceCount		=	0;
			//m_bNeedCheckView		=	false;
		}
	
		U1 InstanceEntity::Create(){
			//��������
			if(!CreateDeclare()){
				Destroy();
				return	false;
			}
			//����ģ������
			if(!CreateModelVertexBuff()){
				Destroy();
				return	false;
			}
			//����ʵ������
			if(!CreateInstanceVertexBuff()){
				Destroy();
				return	false;
			}
			//��������
			if(!CreateIndex()){
				Destroy();
				return	false;
			}
			//��������
// 			m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(m_strMaterialName,AString("Material"));
// 			if(m_pMaterial==NULL){
// 				Destroy();
// 				return	false;
// 			}
			return true;
		}
	
		U1 InstanceEntity::Destroy(){
// 			if(m_pModelVertexBuff!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_pModelVertexBuff);
// 				m_pModelVertexBuff	=	NULL;
// 			}
// 			if(m_pInstanceVertexBuff!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_pInstanceVertexBuff);
// 				m_pInstanceVertexBuff	=	NULL;
// 			}
// 			if(m_DrawBuff.m_pVertexDeclare!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pVertexDeclare);
// 				m_DrawBuff.m_pVertexDeclare	=	NULL;
// 			}
// 			if(m_DrawBuff.m_pIndexBuff!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pIndexBuff);
// 				m_DrawBuff.m_pIndexBuff	=	NULL;
// 			}
// 			if(m_pMaterial!=NULL){
// 				Render::System::GetSingleton()->DestroyProduct(m_pMaterial);
// 				m_pMaterial	=	NULL;
// 			}
	
			return true;
		}
	
		void InstanceEntity::Render(){
			//��������ʵ������
			//Render::System::GetSingleton()->SetVertexInstance(m_pModelVertexBuff,m_pInstanceVertexBuff,m_uiInstanceCount);
			//������Ⱦ
			//__super::Render();
			//Render::Renderable::Render();
			//��Ⱦ���֮��֤��ʵ����������Ϊ��
			//Render::System::GetSingleton()->SetVertexInstance(NULL,NULL,0);
		}
	
		void InstanceEntity::Update(){
	
		}
	}
};