/*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2009/12/02
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceSceneNode.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef INTERFACESCENENODE_HEAD_FILE
#define INTERFACESCENENODE_HEAD_FILE


#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirCommonLock.h"

namespace Air{
	
	
	
	namespace Engine{
		namespace	Render{
			class	Queue;
		}
	
	 	class SceneNode;
		typedef std::list<MovableObject*>					MovableObjectList;
		typedef MovableObjectList::iterator					MovableObjectListItr;
	
	
		typedef std::list<SceneNode*>								SceneNodeList;
		typedef std::list<SceneNode*>::iterator					SceneNodeListItr;

		enum	enumSceneNodeType{
			enSNT_UNKNOWN,
			enSNT_STATIC,
			enSNT_DYNAMIC,
			enSNT_MAX
		};
		enum	enumSceneNodeFlag{
			enSNF_VISIABLE,
			enSNF_MAX
		};
	
		/**	\brief	�����ڵ�
		*
		*	�����ڵ�
		*
		***/
		class ENGINE_EXPORT SceneNode : 
			public	Common::INode,
			public	Flag<enumSceneNodeFlag>{
		public:
			SceneNode();
			SceneNode(CAString&	strName,SceneNode*	pParentNode);
			virtual ~SceneNode();
			/**	\brief	���ظ������ڵ�
			*   
			*	@remarks 	���ظ������ڵ�
			*	@see		SceneNode
			*	@return   	SceneNode*
			*	@note
			*
			**/
			virtual SceneNode* GetParentSceneNode();
	
			/**	\brief	�����ӽڵ�
			*   
			*	@remarks 	�����ӳ����ڵ�
			*	@see		SceneNode
			*	@return   	SceneNode*
			*	@param		CAString&	strName
			*	@note
			*
			**/
			virtual SceneNode* CreateChildSceneNode(const	Float3&	pos	=	Float3(0,0,0),
													const	Float4&	rot	=	Float4(0,0,0,1),
													const	Float3&	scale	=	Float3(1,1,1));
			/**	\brief	������
			*   
			*	@remarks	������
			*	@see		SceneNode
			*	@return   	void
			*	@param		MovableObject * obj
			*	@note
			*
			**/
			virtual void attachObject(MovableObject* obj);
	
			/**	\brief	�Ƴ�����
			*   
			*	@remarks 	�Ƴ�����
			*	@see		SceneNode
			*	@return   	void
			*	@param		MovableObject * obj
			*	@note
			*
			**/
			virtual void detachObject(MovableObject* obj);
	
			/**	\brief	�ӳٽ������İ�
			*   
			*	@remarks 	�ӳٽ������İ�
			*	@see		SceneNode
			*	@return   	void
			*	@param		MovableObject * obj
			*	@note
			*
			**/
			//virtual	void detachObjectDelay(MovableObject* obj);
	
			/**	\brief	�Ƴ���������
			*   
			*	@remarks 	
			*	@see		SceneNode
			*	@return   	void
			*	@param		void
			*	@note
			*
			**/
			virtual void detachAllObjects(void);
	
			/**	\brief	������Ⱦ�����б�
			*   
			*	@remarks 	������Ⱦ�����б�
			*	@see		SceneNode
			*	@return   	MovableObjectList&
			*	@note
			*
			**/
			const MovableObjectList&		GetObjectList()const ;
	
			/**	\brief	�����ӳ����б�ڵ�
			*   
			*	@remarks 	�����ӳ����б�ڵ�
			*	@see		SceneNode
			*	@return   	Client::ChildSceneNodeList
			*	@note
			*
			**/
			virtual SceneNodeList GetChildSceneNodeList();
			/**	\brief	����
			*   
			*	@remarks 	����(ֻ��Ҫ���ڵ����)���½ڵ���� ���»ص��б� ���°�Χ�� ����Ƿ�ɼ� ���ýڵ��ϵ������Ƿ�ɼ�
			*	@see		SceneNode
			*	@return   	void
			*	@note
			*
			**/
			virtual void	Update(	const	Float44&	ParentGlobalWorldMatrix,
									const	Float4&		ParentGlobalWorldQuat,
									const	Float3&		ParentGlobalWorldScale,
									U1					bParentDirty);
	
			/**	\brief	���ӽڵ�
			*   
			*	@remarks 	��һ���ڵ㸽�ӵ��˽ڵ�  ��Ϊ����ڵ���ӽڵ� ����ڵ��Ѿ������������ڵ㣬����Ƴ����ǵ�֮��ĸ��ӹ�ϵ
			*	@see		INode
			*	@return   	void
			*	@param		INode * pObject
			*	@note
			*
			**/
			virtual void		AddChild(INode* pObject);
			/**	\brief	�Ƴ��ڵ�
			*   
			*	@remarks 	�Ӵ˽ڵ��Ƴ�һ���ӽڵ� ͨ��ָ�����Ƴ�
			*	@see		INode
			*	@return   	void
			*	@param		INode * pObject	
			*	@param		bool bDestroy	���ΪTRUE ��Ὣ����ڵ�ݻ�
			*	@note
			*
			**/
			virtual void		RemoveChild(INode* pObject,bool bDestroy = false);
			/**	\brief	�Ƴ������ӽڵ�
			*   
			*	@remarks 	�Ƴ������ӽڵ�
			*	@see		INode
			*	@return   	void
			*	@param		bool bDestroy
			*	@note
			*
			**/
			virtual void		RemoveAllChild(bool bDestroy = false);
			/**	\brief	��ӽڵ������
			*   
			*	@remarks 	��ӽڵ������
			*	@see		INode
			*	@return   	void
			*	@param		IListener * pListener
			*	@note
			*
			**/
			virtual void AddListener(Common::INodeListener* pListener);
			/**	\brief	�Ƴ��ڵ������
			*   
			*	@remarks 	�Ƴ��ڵ������
			*	@see		INode
			*	@return   	void
			*	@param		IListener * pListener
			*	@note
			*
			**/
			virtual void RemoveListener(Common::INodeListener* pListener);

			/**	\brief	���ҳ�������
			*   
			*	@remarks 	���ҳ�������
			*	@see		SceneNode
			*	@return   	void
			*	@param		Camera * pCamera
			*	@note
			*
			**/
			virtual	void	FindMovableObject(Camera*	pCamera);

			virtual	U1		RayCast(const Ray& ray,MovableObject*& pOutObject,float*	pOutDistance	=	NULL);
		protected:
			/**	\brief	�����ӽڵ�
			*   
			*	@remarks 	�����ӽڵ�
			*	@see		SceneNode
			*	@return   	Node*
			*	@note
			*
			**/
			virtual INode*	CreateChildImp(CAString& strName);
			
			enumSceneNodeType	GetType();
			void				SetType(enumSceneNodeType	t);

			inline	U1			IsVisiable(){
				return	HasFlag(enSNF_VISIABLE);
			};
			inline	void		SetVisiable(U1	bVisiable){
				if(bVisiable){
					AddFlag(enSNF_VISIABLE);
				}else{
					RemoveFlag(enSNF_VISIABLE);
				}
			}

		private:
			MovableObjectList	m_lstMovableObject;				///<	���ƶ������б�
				
	
		protected:
			Common::CriticalSection	m_NodeCS;					///<	�ӽڵ���
			Common::CriticalSection	m_ListenCS;					///<	��������
			Common::CriticalSection	m_ObjectCS;					///<	��Ʒ��
			enumSceneNodeType		m_Type;
			U32						m_uiFlag;					///<	����
		};
	};
};

#endif // INTERFACESCENENODE_HEAD_FILE