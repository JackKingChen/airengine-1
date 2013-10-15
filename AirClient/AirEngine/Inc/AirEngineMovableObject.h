//*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.



 \author    InfernalHell	Xinhe
 \date      2009/10/21
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceMovableObject.h
 \note     
       
 \attention:
			���ƶ�����Ⱦ�������
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACEMOVABLEOBJECT_HEAD_FILE
#define INTERFACEMOVABLEOBJECT_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceObject.h"
#include "AirCommonProduct.h"
#include "AirEngineRenderable.h"

namespace Air{
	
	
	namespace Engine{
		class	SceneNode;
		class	Camera;
		enum	enumMovableObjectFlag{
			enMOF_DEFAULT,			///<	�Ƿ���Ա����������
			enMOF_REFLECT,			///<	�Ƿ��������
			enMOF_CASTSHADOW,		///<	�Ƿ�Ͷ����Ӱ
			enMOF_VISIABLE,			///<	�Ƿ�ɼ�
			enMOF_DYNAMIC,			///<	�Ƿ�Ϊ��̬����
			enMOF_UPDATE,			///<	�Ƿ���Ҫ����
			enMOF_NEED_FRUSTUM_CULL,///<	�Ƿ���Ҫ��׶�ü�
			enMOF_UPDATE_IN_VIEW,	///<	ֻ�ڿɼ���ʱ�����

			enMOF_MAX
		};
		/**	\brief	���ƶ�����Ⱦ�������
		*
		*	�������Ⱦ�Ϳ��ƶ������������ ��Ϊ����Ļ���������
		*
		***/
		class ENGINE_EXPORT MovableObject :
			public	Common::IProduct,
			public	Flag<enumMovableObjectFlag>{
		public:
			MovableObject(const AString& strName);
			virtual ~MovableObject();
			virtual	U1			Create();
			virtual	U1			Destroy();
			U1					IsAttached();
			void				SetParent(SceneNode*	pParentNode);
			/**	\brief	���س������ڵ�
			*   
			*	@remarks 	���س������ڵ�
			*	@see		MovableObject
			*	@return   	SceneNode*
			*	@note
			*
			**/
			virtual SceneNode*	GetParentSceneNode();
			/**	\brief	��ȡ��Χ��
			*   
			*	@remarks 	��ȡ��Χ��
			*	@see		MovableObject
			*	@return   	BoundBox&
			*	@note
			*
			**/
			virtual	const BoundingBox&	GetWorldBoundingBox()const;
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		MovableObject
			*	@return   	void
			*	@note
			*
			**/
			virtual	void		Prepare(Float44*	pMatrix);
			/**	\brief	׼����Ⱦ
			*   
			*	@remarks 	׼����Ⱦ
			*	@see		MovableObject
			*	@return   	void
			*	@param		Float44 * pWorldMatrix
			*	@param		Float4 * pWorldQuat
			*	@param		Float3 * pWorldScale
			*	@note
			*
			**/
			virtual	void		Update(	const	Float44&	ParentGlobalWorldMatrix,
										const	Float4&		ParentGlobalWorldQuat,
										const	Float3&		ParentGlobalWorldScale,
										U1					bParentDirty);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		MovableObject
			*	@return   	void
			*	@note
			*
			**/
			virtual	void		Update(const FrameTime& frameTime);
	
			/**	\brief	��ȡ���վ���
			*   
			*	@remarks 	��ȡ���վ���
			*	@see		MovableObject
			*	@return   	Client::Float44
			*	@note
			*
			**/
			Float44*					GetWorldMatrix();

			/**	\brief	��ȡԭʼ��Χ��
			*   
			*	@remarks 	�����Χ��û�о�������ת��
			*	@see		ICullable
			*	@return   	BoundBox&
			*	@note
			*
			**/
			const	BoundingBox&		GetOrginBoundingBox()const;
			/**	\brief	��ȡ��Χ��
			*   
			*	@remarks 	��ȡ��Χ��
			*	@see		ICullable
			*	@return   	Common::BoundSphere
			*	@note
			*
			**/
			Sphere			GetBoundSphere();

			/**	\brief	�Ƿ�����Ұ
			*   
			*	@remarks 	�Ƿ�����Ұ
			*	@see		ICullable
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		IsInView();

			/**	\brief	�ֶ����°�Χ��
			*   
			*	@remarks 	�ֶ����°�Χ��
			*	@see		ICullable
			*	@return   	void
			*	@param		Float3 & vMin
			*	@param		Float3 & vMax
			*	@note
			*
			**/
			void			SetBoundBox(const Float3& vMin,const Float3& vMax);

			void			SetCheckView(U1	bEnable	=	true){
				m_bNeedCheckView	=	bEnable;
			};

			virtual	void	ProcessRenderObject(U32	uiPhaseFlag);

			virtual	U1		RayCast(const	Ray&	ray,float*	pOutDistance	=	NULL);

			virtual	U1		OnCameraCull(Camera*	pCamera);
		protected:
			BoundingBox			m_WorldBound;		///<	�����Χ��
			Float44				m_WorldMatrix;		///<	�������
			Float44				m_ResultMatrix;		///<	��Ⱦ��������վ���
			BoundingBox			m_BoundingBox;			///<	��Χ��
			U1					m_bDirty;			///<	����ľ���Ͱ�Χ���Ƿ���Ҫ����

			U1					m_bInView;			///<	�Ƿ�����Ұ��
			U1					m_bNeedCheckView;	///<	�Ƿ���Ҫ��׶�ü�
			SceneNode*			m_pParentNode;
			//Buffer*		m_pObjectCB;	

			RenderableVector	m_vecRenderable;
			U32					m_uiVisiableFrame;	
		};
	};
};
#endif