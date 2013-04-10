#include "AirEnginePostComposer.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirEngineSystem.h"
#include "AirEngineMaterial.h"
namespace Air{
	
	namespace	Engine{
		
	
		PostComposer::PostComposer( AString strName,AString* strMaterialName )
			:TProduct(strName){
			m_bEnable	=	true;
			//m_pMaterial	=	NULL;
			m_pTerget	=	NULL;
			m_strMaterialName	=	*strMaterialName;
		}
	
		U1 PostComposer::Create(){
	
			//��������
// 			m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<RenderMaterial*>(m_strMaterialName,AString("Material"));
// 			if(m_pMaterial==NULL)
// 				return false;
	
			//����������
			AString	strFileName;
			GlobalSetting::ParsePath(m_strMaterialName,NULL,&strFileName);
	
			//������ȾĿ��
			RenderTarget::Info info;
			
			//��ȡ������Ϣ�е�������� ��ʽ	��A8R8G8B8 F32�ȵ�
			File	file(m_strMaterialName);
			if(!file.Open()){
				return false;
			}
			IniFile	cfgFile;
			cfgFile.LoadFileFromMemory(file.GetData());
			AString	strFormat	=	cfgFile.Get("Composer","Format");
			AString	strSize		=	cfgFile.Get("Composer","Size");
			AString	strBKColor	=	cfgFile.Get("Composer","BKColor");
// 			if(strSize.empty()){
// 				info.SetRenderToTexture(1024,700,true);
// 			}else{
// 				Float4	vSize		=	GlobalSetting::ParseFloat4(strSize);
// 				info.SetRenderToTexture(vSize.x,vSize.y);
// 			}
			
// 			if(!strFormat.empty())
// 				info..format		=	(RenderTexture::enumFormat)Converter::ToS32(strFormat);
	
			//������ȾĿ��
			m_pTerget	=	Render::System::GetSingleton()->CreateProduct<RenderTarget>(strFileName,&info);
			if(m_pTerget==NULL){
				return	false;
			}
	
			if(!strBKColor.empty()){
				Float4	vColor	=	GlobalSetting::ParseFloat4(strBKColor);
				m_pTerget->SetBKColor(vColor);
			}
	
			m_pObject	=	m_pTerget;
	
			return true;
		}
	
		U1 PostComposer::Destroy(){
	
			if(m_pMaterial==NULL){
				m_pMaterial->ReleaseRef();
				m_pMaterial=NULL;
			}
		
			if(m_pTerget==NULL){
				m_pTerget->ReleaseRef();
				m_pTerget=NULL;
			}
	
			m_pObject	=	NULL;
	
			return true;
		}
	
		void PostComposer::Render(){
			if(!m_bEnable)
				return;
			if(m_pTerget!=NULL){
				//�ύ��Ⱦ����
				GetGlobalSetting().m_ShaderParam.m_pCurrentPostComposerMaterial	=	m_pMaterial;
				//��ȾĿ��
				//m_pTerget->Render();
				//��ȡ��һ֡����Ⱦ���
				//GetGlobalSetting().m_ShaderParam.m_pLastPostComposerResult	=	m_pTerget->GetTexture();
			}
		}
	}
};