#ifndef ENGINEINSTANCEENTITY_HEAD_FILE
#define ENGINEINSTANCEENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderSystem.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
	
		/**	\brief	ʵ����
		*
		*	ʵ����
		*
		***/
		class	ENGINE_EXPORT	InstanceEntity	:
			public	MovableObject{
		public:
			InstanceEntity(CAString&	strName,UInt	uiMaxInstance);
			
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	
			/**	\brief	����ģ�Ͷ��㻺��
			*   
			*	@remarks 	����ģ�Ͷ��㻺��
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateModelVertexBuff()		=	NULL;
			/**	\brief	����ʵ�嶥�㻺��
			*   
			*	@remarks 	����ʵ�嶥�㻺��
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateInstanceVertexBuff()	=	NULL;
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateDeclare()				=	NULL;
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateIndex()				=	NULL;
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		InstanceEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Update();
	
			/**	\brief	��Ⱦ
			*   
			*	@remarks 	��Ⱦ
			*	@see		InstanceEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Render();
	
			/**	\brief	����ʵ�����
			*   
			*	@remarks 	����ʵ�����
			*	@see		InstanceEntity
			*	@return   	void
			*	@param		UInt uiCount
			*	@note
			*
			**/
			inline	void	SetInstanceCount(UInt	uiCount){
				m_uiInstanceCount	=	uiCount;
			}
		protected:
			Render::Vertex::IBuff*	m_pModelVertexBuff;		///<	ģ������
			Render::Vertex::IBuff*	m_pInstanceVertexBuff;	///<	ʵ������
			UInt					m_uiInstanceCount;		///<	ʵ�����
			AString					m_strMaterialName;
		};
	
	};
};
#endif // ENGINEINSTANCEENTITY_HEAD_FILE