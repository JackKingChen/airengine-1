#ifndef ENGINEENTITY_HEAD_FILE
#define ENGINEENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineSceneNode.h"
namespace Air{
	
	namespace Engine{

		class	SubEntity;
	
		/**	\brief	�������������
		*
		*	�������������
		*
		***/
		class	Entity	:
			public	TProduct<Entity>,
			public	Common::INodeListener{
		public:
			struct Info{
				Info(){
					pParentNode	=	NULL;


				};
				AString						strConfigName;		///<	�����ļ���
				AString						strConfigMemery;	///<	��������
				SceneNode*					pParentNode;		///<	���ڵ�
			};
	
		public:
			Entity(CAString&	strName,Info*	pInfo);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Entity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1					Create();
	
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		Entity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1					Destroy();
	
			/**	\brief	��ȡ�ڵ�
			*   
			*	@remarks 	��ȡ�ڵ�
			*	@see		Entity
			*	@return   	SceneNode*
			*	@note
			*
			**/
			virtual	SceneNode*			GetSceneNode();
	
			/**	\brief	��ȡ��ײģ��
			*   
			*	@remarks 	��ȡ��ײģ��
			*	@see		Entity
			*	@return   	Physx::ICollision*
			*	@note
			*
			**/
			//virtual	Physics::ICollision*	GetCollision();
	
			/**	\brief	��ȡ��Ⱦģ��
			*   
			*	@remarks 	��ȡ��Ⱦģ��
			*	@see		Entity
			*	@return   	SubEntity*
			*	@note
			*
			**/
			virtual	SubEntity*			GetSubEntity();
	
			/**	\brief	����
			*   
			*	@remarks 	�˺����ɽڵ�(INode)������ ���������һЩ���¶���
			*	@see		IListener
			*	@return   	void
			*	@param		Float3 vPos
			*	@param		Float4 vQuat
			*	@param		Float3 vScale
			*	@note
			*
			**/
			virtual void UpdateMatrix(Float44* pMatrix,Float4*	pQuat,Float3*	pScale);
		protected:
			/**	\brief	���������ļ�
			*   
			*	@remarks 	���������ļ�
			*	@see		Entity
			*	@return   	U1
			*	@note
			*
			**/
			U1	ParseConfig();
	
		protected:
			SubEntity*		m_pRenderObj;			///<	��Ⱦ����
			SceneNode*			m_pNode;				///<	�ڵ�
			Info				m_Info;					///<	������Ϣ
		};

	
	};
};
#endif // ENGINEENTITY_HEAD_FILE