#include "AirEngineMovableObject.h"
#include "AirRandom.h"
#include "AirEngineSceneNode.h"
#include "AirGlobalSetting.h"
#include "AirEngineSystem.h"
namespace Air{
	
	
	namespace Engine{
	
		MovableObject::MovableObject(){
			m_pParentNode	=	NULL;
			m_uiVisiableFrame	=	0;;
			m_bDirty		=	true;

			AddFlag(enMOF_DEFAULT			);
			AddFlag(enMOF_REFLECT			);
			AddFlag(enMOF_CASTSHADOW		);
			AddFlag(enMOF_VISIABLE			);
			AddFlag(enMOF_DYNAMIC			);
			AddFlag(enMOF_UPDATE			);
			AddFlag(enMOF_NEED_FRUSTUM_CULL	);
		}
	
		MovableObject::~MovableObject(){
			if(m_pParentNode!=NULL){
				m_pParentNode->detachObject(this);
			}				
		}
	
	 	SceneNode* MovableObject::GetParentSceneNode(){
	 		return	m_pParentNode;
	 	}
		const BoundingBox& MovableObject::GetWorldBoundingBox()const{
			return	m_WorldBound;
		}

		void MovableObject::Prepare(Float44*	pMatrix){
			//���¾��� �������Χ�� ����Ⱦʱʹ��
			//m_CS.Enter();
			m_ResultMatrix	=	*(Float44*)pMatrix;
			//memcpy(&m_ResultBound,&m_WorldBound,sizeof(BoundBox));
			//m_CS.Leave();
	
			
		}
	
		void MovableObject::Update( const	Float44&	ParentGlobalWorldMatrix,
									const	Float4&		ParentGlobalWorldQuat,
									const	Float3&		ParentGlobalWorldScale,
									U1					bParentDirty )
		{
			//m_CS.Enter();
			if(bParentDirty || m_bDirty){
				m_WorldMatrix		=	ParentGlobalWorldMatrix;
				m_WorldBound		=	m_BoundingBox.Transform(ParentGlobalWorldMatrix);
				m_bDirty			=	false;
			}

			//Update();
		}
	
		void MovableObject::Update(const FrameTime& frameTime){
	
		}
	
		Float44* MovableObject::GetWorldMatrix(){
			return	&m_WorldMatrix;
		}

		const BoundingBox& MovableObject::GetOrginBoundingBox()const{
			return	m_BoundingBox;
		}

// 		void MovableObject::CheckIsInView( PlaneList& lstPlane ){
// 
// 		}

		Air::U1 MovableObject::IsInView(){
			return	m_bInView;
		}

		void MovableObject::SetBoundBox( const Float3& vMin,const Float3& vMax ){
			m_BoundingBox.vMin	=	vMin;
			m_BoundingBox.vMax	=	vMax;
			m_bDirty		=	true;
		}

		void MovableObject::SetParent( SceneNode* pParentNode ){
			m_pParentNode	=	pParentNode;
			//�������ڵ�ʱ ����Ͱ�Χ����Ҫ����
			m_bDirty		=	true;
		}

		Air::U1 MovableObject::IsAttached(){
			return	m_pParentNode!=NULL;
		}

		void MovableObject::ProcessRenderObject(U32	uiPhaseFlag){

			RenderableVector::iterator	i		=	m_vecRenderable.begin();
			RenderableVector::iterator	iEnd	=	m_vecRenderable.end();
			for(;i!=iEnd;i++){
				if((*i)->IsVisiable())
					(*i)->AddToRenderQueue(uiPhaseFlag);
			}
		}

		Air::U1 MovableObject::RayCast( const Ray& ray,float* pOutDistance /*= NULL*/ )
		{
			return	ray.Intersect(m_WorldBound,pOutDistance);
		}

		Air::U1 MovableObject::OnCameraCull( Camera* pCamera )
		{
			if(!HasFlag(enMOF_VISIABLE))
				return false;
			U1	bVisable	=	pCamera->IsVisiable(m_WorldBound);
			if(bVisable)
				m_uiVisiableFrame	=	GetTimer().m_FrameTime.uiFrameIndex;
			return bVisable;
		}

// 		Buffer* MovableObject::GetObjectConstantBuffer(){
// 			
// 			return	m_pObjectCB;
// 		}

	
	};
};