#include "AirCommonReference.h"
namespace Air{
	
	namespace	Common{
	
	
		IReference::IReference(){
			m_pObject	=	NULL;
			m_uiNumRef	=	0;
		}
	
		IReference::~IReference(){
			//::OutputDebugStringA("IReference::~IReference()\n");
			//ǿ������
			//���ڷ��ڻ��ദ��  ��ΪDestroy�Ǹ����麯�� 
			//�ڻ������������е��� ���ܻᵼ��ʵ�ֲ��ִ����Ѿ��ͷ� 
			//�������麯��û��ʵ�� ��Ч���õĴ���
	// 		if(m_pObject!=NULL){
	// 			m_uiNumRef	= 1;
	// 			ReleaseRef();
	// 		}
		}
	
		U32 IReference::AddRef(){
			if(m_uiNumRef<=0){
				//����Ҫ���Ƕ��̵߳ļ���
				if(!Create())
					return false;
			}
			m_uiNumRef++;
			return m_uiNumRef;
		}
	
		U32 IReference::ReleaseRef(){
			if(m_uiNumRef<=0)
				return true;
			m_uiNumRef--;
			//����Ҫ���Ƕ��̵߳�ж��
			if(m_uiNumRef<=0){
				Destroy();
			}
			return m_uiNumRef;
		}
	}
};