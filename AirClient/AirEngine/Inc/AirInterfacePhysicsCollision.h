#ifndef INTERFACEPHYSICSCOLLISION_HEAD_FILE
#define INTERFACEPHYSICSCOLLISION_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceUserData.h"
#include "AirInterfacePhysicsShape.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Physics{
			class	ICollision;
			/**	\brief	�������ص�
			*
			*	�������ص�
			*
			***/
			class	ITriggerCallback{
			public:
				/**	\brief	�������¼�����
				*
				*	�������¼�����
				*
				***/
				enum	enumType{
					enEnter,
					enLeave,
					enStay,
					enUnKnown
				};
				/**	\brief	�ص��ӿ�
				*   
				*	@remarks 	�ص��ӿ�
				*	@see		ITriggerCallback
				*	@return   	void
				*	@param		enumType type
				*	@param		ICollision * pCollision
				*	@note
				*
				**/
				virtual	void	OnTrigger(enumType	type,ICollision*	pCollision)	=	NULL;
			};
			/**	\brief	��ײ����
			*
			*	��ײ����
			*
			***/
			class	ICollision	:
				public	TProduct<ICollision>{
			public:
				enum	enumType{
					enDynamic,		///<	��̬
					enStatic,		///<	��̬
					enKinematic		///<	����ѧ(�����ֶ����Ƶ�����)
				};
				/**	\brief	������Ϣ
				*
				*	������Ϣ
				*
				***/
				struct	Info{
					Info(){
						fMass		=	1.0f;
						type		=	enStatic;
						vPosition	=	Float3(0,0,0);//Float3::ZERO;
						vQuat		=	Float4(0,0,0,1);//Float4::IDENTITY;
						fDensity	=	-1.0f;	
						pCallback	=	NULL;
						initvelocity	=	Float3(0,0,0);//Float3::ZERO;
						angularDamping	=	0.5f;
					};
					/**	\brief	����Ϊ��̬����
					*   
					*	@remarks 	����Ϊ��̬����
					*	@see		Info
					*	@return   	void
					*	@param		Real density
					*	@note
					*
					**/
					void	SetDynamic(Real	density){
						type		=	enDynamic;
						fDensity	=	density;
					};
					Real		fMass;			///<	����
					Float3		vPosition;		///<	λ��
					Float4		vQuat;			///<	��ת��
					enumType	type;			///<	����
					Real		fDensity;		///<	�ܶ�	(����0 �����Ƕ�̬���� С�����Ƕ�̬����)
					Shape		shape;			///<	����
					Real		angularDamping;	///<	�����
					Float3		initvelocity;	///<	��ʶ�ٶ�
					ITriggerCallback*	pCallback;	///<	�������ص��ӿ�
				};
			public:
				ICollision(CAString&	strName,Info*	pInfo):TProduct(strName){
					if(pInfo!=NULL){
						m_Info	=	*pInfo;
					}
				}
				/**	\brief	��ȡλ��
				*   
				*	@remarks 	��ȡλ��
				*	@see		ICollision
				*	@return   	Float3
				*	@note
				*
				**/
				virtual	Float3		GetPosition()					=	NULL;
				virtual	void		SetPosition(Float3	vPosition)	=	NULL;
				virtual	void		MovePosition(Float3 vPosition)	=	NULL;
				/**	\brief	��ȡ��ת��
				*   
				*	@remarks 	��ȡ��ת��
				*	@see		ICollision
				*	@return   	Float4
				*	@note
				*
				**/
				virtual	Float4		GetQuat()						=	NULL;
				virtual	void		SetQuat(Float4	quat)		=	NULL;
				virtual	void		MoveQuat(Float4	quat)		=	NULL;
	
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		ICollision
				*	@return   	Client::Float44
				*	@note
				*
				**/
				virtual	Float44		GetMatrix()						=	NULL;
				virtual	void		SetMatrix()						=	NULL;
	
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		ICollision
				*	@return   	Client::Physx::ICollision::enumType
				*	@note
				*
				**/
				virtual	enumType	GetType()						=	NULL;
				virtual	void		SetType(enumType	type)		=	NULL;
	
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		ICollision
				*	@return   	Client::Float3
				*	@note
				*
				**/
				virtual	Float3		GetMassPosition()						=	NULL;
				virtual	void		SetMassPosition(Float3	vMass)			=	NULL;
	
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		ICollision
				*	@return   	Real
				*	@note
				*
				**/
				virtual	Real		GetMass()								=	NULL;
				virtual	void		SetMass(Real	fMass)					=	NULL;
	
	
				virtual	void		AddForce(Float3	vForce)				=	NULL;
				virtual	void		AddForceAtLocalPos(Float3	vForce,Float3	vPos)	=	NULL;
				virtual	void		AddForceAtPos(Float3	vForce,Float3	vPos)		=	NULL;
				virtual	void		AddLocalForce(Float3	vForce)			=	NULL;
				virtual	void		AddLocalForceAtLocalPos(Float3	vForce,Float3	vPos)	=	NULL;
				virtual	void		AddTorque(Float3	vTorque)			=	NULL;
				virtual	void		AddLocalTorque(Float3	vTorque)		=	NULL;
				virtual	void		AddVelocity(Float3	vVelocity)			=	NULL;
				virtual	void		AddSelfVelocity(Float3	vVelocity)		=	NULL;
	
				//virtual		void			setLinearVelocity(const NxVec3& linVel)


				Info				m_Info;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXCOLLISION_HEAD_FILE