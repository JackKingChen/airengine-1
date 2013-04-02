#include "AirInterfaceAlphaObjectManager.h"
#include "AirGlobalSetting.h"
namespace Air{
	
	
	namespace	Engine{
		
	
		IAlphaObjectManager::IAlphaObjectManager(){
			m_pCameraPosition	=	&GetGlobalSetting().m_ShaderParam.m_vCurrentPosition;
		}
	
		void IAlphaObjectManager::PushAlphaObject( AlphaObject obj ){
			if(obj.pRenderObj==NULL)
				return;
// 			static	Float3	vOjectPos	=	Float3(0,0,0);//::ZERO;
// 			//����û��ʹ��std::list::sort ���Է�������������std::list<int> 10000�����ڣ� ���ַ�����4������
// 			vOjectPos	=	obj.mat.transpose().getTrans();
// 			obj.fDistance	=	vOjectPos.distance(*m_pCameraPosition);
// 	
// 			AObjectListItr	i	=	m_lstAlphaObject.begin();
// 			for(;i!=m_lstAlphaObject.end();i++){
// 				AlphaObject&	object	=	(AlphaObject)(*i);
// 				if(obj.fDistance	<	object.fDistance){
// 					m_lstAlphaObject.insert(i,obj);
// 					return;
// 				}
// 			}
// 			m_lstAlphaObject.push_back(obj);
			//::OutputDebugStringA("�����͸������\n");
		}
		void IAlphaObjectManager::RenderAlphaObject(){
			//����Զ�ľ��뿪ʼ��Ⱦ��͸������
// 			AObjectListRItr	i	=	m_lstAlphaObject.rbegin();
// 			for(;i!=m_lstAlphaObject.rend();i++){
// 				AlphaObject&	obj	=	(AlphaObject)(*i);
// 				GetGlobalSetting().m_ShaderParam.UpdataWorldMatrix(&obj.mat);
// 				obj.pRenderObj->RenderAlpha();
// 				//::OutputDebugStringA("��Ⱦ��͸������\n");
// 			}
// 			m_lstAlphaObject.clear();
		}
	}
};