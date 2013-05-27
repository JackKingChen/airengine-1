//*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.



 \author    InfernalHell	Xinhe
 \date      2009/10/21
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  InterfaceNode.h
 \note     
       
 \attention:
			�ڵ���
       
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACENODE_HEAD_FILE
#define INTERFACENODE_HEAD_FILE


#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirInterfaceObject.h"

namespace Air{
	
	namespace Common{

		class	INode;
	
		/**	\brief	�ڵ������
		*
		*	�ڵ������
		*
		***/
		class COMMON_EXPORT INodeListener{
		public:
			INodeListener();
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		INodeListener
			*	@return   	void
			*	@param		const	Float44& pMatrix
			*	@param		const	Float4 & pQuat
			*	@param		const	Float3 & pScale
			*	@note
			*
			**/
			virtual void UpdateMatrix(	const	Float44& matWorld,
										const	Float4&	pQuat,
										const	Float3&	pScale,
										U1		bParentDirty);

			U1		m_bDirty;
		};
		typedef std::list<INodeListener*>				NodeListenerList;				///<	�ڵ�������б�
		typedef std::list<INodeListener*>::iterator		NodeListenerListItr;			///<	�ڵ�������б������
	
		typedef std::list<INode*>						NodeList;			///<	�ӽڵ��б�
		typedef std::list<INode*>::iterator				NodeListItr;		///<	�ӽڵ��б������
		//class INodeListener
		/**	\brief	�ڵ����
		*
		*	�����ƶ����κ����嶼Ҫ�̳��ڴ�
		*
		***/
		class COMMON_EXPORT INode : 
			public IObject{
		public:
			INode();
			virtual ~INode();
	
			/**	\brief	�����ӽڵ�
			*   
			*	@remarks 	����һ���ӽڵ�
			*	@see		INode
			*	@return   	INode*
			*	@param		CAString& strName
			*	@note
			*
			**/
			virtual INode*		CreateChild();
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
			
			/**	\brief	��ȡ�ӽڵ����
			*   
			*	@remarks 	��ȡ�ӽڵ����������ĸ���
			*	@see		INode
			*	@return   	int
			*	@note
			*
			**/
			inline	U32 GetChildCount()const{
				return	m_lstChild.size();
			};

			/**	\brief	�ж��Ƿ�����ӽڵ�
			*   
			*	@remarks 	�ж��Ƿ�����ӽڵ�
			*	@see		INode
			*	@return   	bool
			*	@note
			*
			**/
			inline	U1		Empty()const{
				return m_lstChild.empty();	
			};
			/**	\brief	��ȡָ��
			*   
			*	@remarks 	
			*	@see		INode
			*	@return   	void*
			*	@note
			*
			**/
			virtual void*		getHandle();
	
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
	
			/**	\brief	��ȡ�������
			*   
			*	@remarks 	����ڸ��ڵ㣨û�и��ڵ� ���ʾ���Ǹ��ڵ㣩
			*	@see		INode
			*	@return   	Client::Vector3
			*	@note
			*
			**/
			const Float3&		GetPosition()const;
			/**	\brief	�����������
			*   
			*	@remarks 	Ŀǰ������ֱ��ȥ����ȫ������ �����Ҫʵ��ֱ������ȫ������ ��ý�����Ҫ���ڵĽڵ� ��Ϊ�����ĵ�һ���ӽڵ� ����֮��˽ڵ��״̬�����Ѹ���״̬  �����Ӱ�쵽 GetGlobalMatrix����
			*	@see		INode
			*	@return   	void
			*	@param		Float3 vPos
			*	@note
			*
			**/
			void		SetPosition(const	Float3& vPos);
			void		SetPosition(float x,float y,float z);
			/**	\brief	��ȡ�����Ԫ��
			*   
			*	@remarks 	���������ת���� ����ڸ��ڵ����ת����
			*	@see		INode
			*	@return   	Client::Float4
			*	@note
			*
			**/
			const	Float4&	GetQuat()const;
			/**	\brief	���������ת����
			*   
			*	@remarks 	���������ת���� ����֮��˽ڵ��״̬�����Ѹ���״̬  �����Ӱ�쵽 GetGlobalMatrix����
			*	@see		INode
			*	@return   	void
			*	@param		Float4 vQuat
			*	@note
			*
			**/
			void		SetQuat(const	Float4& vQuat);
			/**	\brief	��ȡ�������ϵ��
			*   
			*	@remarks 	��ȡ�������ϵ��
			*	@see		INode
			*	@return   	Client::Vector3
			*	@note
			*
			**/
			const	Float3&		GetScale()const;
			/**	\brief	�����������ϵ��
			*   
			*	@remarks 	�����������ϵ�� ����֮��˽ڵ��״̬�����Ѹ���״̬  �����Ӱ�쵽 GetGlobalMatrix����
			*	@see		INode
			*	@return   	void
			*	@param		Vector3 vScale
			*	@note
			*
			**/
			void		SetScale(const	Float3& vScale);
			void		SetScale(float fScale);
			/**	\brief	��ȡȫ��λ��
			*   
			*	@remarks 	��ȡȫ��λ��
			*	@see		INode
			*	@return   	Client::Float3
			*	@note
			*
			**/
			const	Float3&		GetGlobalPosition()const;
			/**	\brief	��ȡȫ������ϵ��
			*   
			*	@remarks	��ڵ����
			*	@see		INode
			*	@return   	Client::Vector3
			*	@note
			*
			**/
			const	Float3&		GetGlobalScale()const;
			/**	\brief	��ȡȫ����ת����
			*   
			*	@remarks 	��ڵ����
			*	@see		INode
			*	@return   	Client::Quaternion
			*	@note
			*
			**/
			const	Float4&		GetGlobalQuat()const;
			/**	\brief	��ȡȫ�ֱ任����
			*   
			*	@remarks 	��ڵ����
			*	@see		INode
			*	@return   	Client::Matrix4
			*	@note
			*
			**/
			const	Float44&	GetGolbalMatrix()const;
	
			/**	\brief	 ֱ�ӻ�ȡȫ������
			*   
			*	@remarks 	����ڵ����
			*	@see		INode
			*	@return   	Common::Vector3
			*	@note
			*
			**/
			Float3		GetGlobalScaleImmediately();
			/**	\brief	ֱ�ӻ�ȡȫ����ת
			*   
			*	@remarks 	����ڵ����
			*	@see		INode
			*	@return   	Common::Quaternion
			*	@note
			*
			**/
			Float4	GetGlobalQuatImmediately();
			/**	\brief	ֱ�ӻ�ȡȫ�־���
			*   
			*	@remarks 	����ڵ����
			*	@see		INode
			*	@return   	Common::Matrix4
			*	@note
			*
			**/
			Float44		GetGlobalMatrixImmediately();
	
			/**	\brief	��ȡ�������
			*   
			*	@remarks 	��ȡ�������
			*	@see		INode
			*	@return   	Common::Matrix4
			*	@note
			*
			**/
			const	Float44&		GetMatrix()const;
	
			/**	\brief	�����ӽڵ��б�
			*   
			*	@remarks 	�����ӽڵ��б�
			*	@see		INode
			*	@return   	Client::ChildList
			*	@note
			*
			**/
			const NodeList&	GetChildNodeList()const;
	
			/**	\brief	��ӽڵ������
			*   
			*	@remarks 	��ӽڵ������
			*	@see		INode
			*	@return   	void
			*	@param		IListener * pListener
			*	@note
			*
			**/
			void AddListener(INodeListener* pListener);
			/**	\brief	�Ƴ��ڵ������
			*   
			*	@remarks 	�Ƴ��ڵ������
			*	@see		INode
			*	@return   	void
			*	@param		IListener * pListener
			*	@note
			*
			**/
			void RemoveListener(INodeListener* pListener);
			/**	\brief	����
			*   
			*	@remarks 	�˺����ɽڵ�(INode)������ ���������һЩ���¶���
			*	@see		IListener
			*	@return   	void
			*	@note
			*
			**/
			virtual void Update(const	Float44&	ParentGlobalWorldMatrix,
								const	Float4&		ParentGlobalWorldQuat,
								const	Float3&		ParentGlobalWorldScale,
								U1					bParentDirty);
			/**	\brief	����һ�����캯��
			*   
			*	@remarks 	��Scene������
			*	@see		INode
			*	@return   	
			*	@param		char * strName
			*	@param		INode * pParentNode
			*	@note
			*
			**/
			INode(INode* pParentNode);
			/**	\brief	�����ӽڵ�
			*   
			*	@remarks 	������������ ��д�˺��� ����NEW�����ʱ��ʹ��
			*	@see		INode
			*	@return   	INode*
			*	@note
			*
			**/
			virtual INode* CreateChildImp();
			
		protected:
			NodeList			m_lstChild;					///<	�ӽڵ��б�
			INode*				m_pParentNode;				///<	�����ĸ��ڵ�ָ��
			Float3				m_vPos;						///<	�������
			Float3				m_vScale;					///<	�������
			Float4				m_qQuat;					///<	�����ת
			Float44				m_matWorld;					///<	����������
			
			NodeListenerList	m_lstListener;				///<	������
	
			Float44				m_GlobalWorldMatrix;		///<	ȫ�־���	���̼߳������ ��������������
			Float3				m_GlobaPosition;
			Float4				m_GlobalWorldQuat;			///<	ȫ����ת
			Float3				m_GlobalScale;				///<	ȫ������

			U1					m_bDirty;					///<	�Ƿ���Ҫ�ؽ��������
		};
	 };
};
#endif