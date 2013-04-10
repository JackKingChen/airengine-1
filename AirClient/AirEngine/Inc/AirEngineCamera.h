#ifndef ENGINECAMERA_HEAD_FILE
#define ENGINECAMERA_HEAD_FILE

#include "AirRenderCommon.h"
#include "AirEngineFrustum.h"
namespace Air{
	
	
	namespace Engine{
		class	Scene;
		class	MovableObject;

		enum	enumCameraType{
			enCT_UNKNOWN,
			enCT_MAIN,
			enCT_REFLECT,
			enCT_SHADOW,
			enCT_MAX
		};
	
		/**	\brief	�������
		*
		*	�������
		*
		***/
		class	ENGINE_EXPORT	Camera	:
			public	TProduct<Camera>,
			public	Frustum
		{
		public:
			Camera(CAString&	strName);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Camera
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		Camera
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	

	
			/**	\brief	��Ⱦ
			*   
			*	@remarks 	��Ⱦ
			*	@see		Camera
			*	@return   	void
			*	@note
			*
			**/
			void				Render2D(SInt uiWidth	=	-1,SInt uiHeight	=	-1);
	
			/**	\brief	��ȡ��Χ�������6�������Ұ����
			*   
			*	@remarks 	
			*	@see		Camera
			*	@return   	void
			*	@param		DWORD dwFace
			*	@note
			*
			**/
			void				RenderCubeMap( DWORD dwFace,SInt uiWidth	=	-1,SInt uiHeight	=	-1);

	
			Float3		GetRealDirection();
			Float3		GetRealPosition();
			Float3		GetRealRightDirection();
			Float3		GetRealUpDirection();
	
			/**	\brief	�Ƿ�Ϊ���������
			*   
			*	@remarks 	�Ƿ�Ϊ���������
			*	@see		Camera
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		IsReflect(){
				return	m_bReflect;
			}
			/**	\brief	�����Ƿ����÷���
			*   
			*	@remarks 	�����Ƿ����÷���
			*	@see		Camera
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetReflectEnable(U1	bEnable){
				m_bReflect	=	bEnable;
			};
			/**	\brief	���÷���ƽ��
			*   
			*	@remarks 	���÷���ƽ��
			*	@see		Camera
			*	@return   	void
			*	@param		Float3 normal
			*	@param		Real fDistance
			*	@note
			*
			**/
			void		SetReflectPlane(Float3 normal,Real	fDistance);


			enumCameraType			GetType(){
				return	m_Type;
			}
			void					SetType(enumCameraType	type){
				m_Type	=	type;
			};

			void			FindMovableObject(Scene*	pScene	=	NULL,Camera*	pMainCamera	=	NULL);
			void			ProcessShadowObject();
			void			AddMovableObject(MovableObject*	pObj);

			void			SetPhaseFlag(U32	flag);
			void			AddPhaseFlag(U32	flag);
			void			RemovePhaseFlag(U32	flag);
			void			ClearPhaseFlag();
			
		protected:
			Buffer*				m_pConstantBuffer;	///<	�������ConstantBuffer
	
			U1					m_bReflect;			///<	�Ƿ�Ϊ���������
			Plane				m_ReflectPlane;		///<	������հ�
	
			TVector<MovableObject*>	m_vecReflectMovable;
			TVector<MovableObject*>	m_vecShadowMovable;
			enumCameraType			m_Type;
			U32						m_PhaseFlag;
		};
	};
};
#endif // ENGINECAMERA_HEAD_FILE