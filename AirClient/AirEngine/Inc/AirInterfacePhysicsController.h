#ifndef INTERFACEPHYSICSCONTROLLER_HEAD_FILE
#define INTERFACEPHYSICSCONTROLLER_HEAD_FILE
namespace Air{
	
	namespace Engine{
	
		namespace	Physics{
			class	IController;
			/**	\brief	��ײ��Ϣ
			*
			*	��ײ��Ϣ
			*
			***/
			struct	CollisionHit{
				//ICollision*	pCollision;
				Float3		vPosition;
				Float3		vNormal;
				Float3		vDirection;
				Real		fLength;
			};
			/**	\brief	��ײ�ص�
			*
			*	��ײ�ص�
			*
			***/
			class	IHitCallBack{
			public:
				virtual	~IHitCallBack(){};
				/**	\brief	����ײ������
				*   
				*	@remarks 	����ײ������
				*	@see		IHitCallBack
				*	@return   	void
				*	@param		CollisionHit * pHit
				*	@note
				*
				**/
				virtual	void	OnCollisionHit(CollisionHit*	pHit)			=	NULL;
				/**	\brief	����ײ��������
				*   
				*	@remarks 	����ײ��������
				*	@see		IHitCallBack
				*	@return   	void
				*	@param		IController * pController
				*	@note
				*
				**/
				virtual	void	OnControllerHit(IController*	pController)	=	NULL;
			};
			/**	\brief	��ɫ������
			*
			*	��ɫ������
			*
			***/
			class	IController{
			public:
				enum	enumType{
					enBox,
					enCapsule
				};
				struct	Info{
					Info(){
						size			=	Float3(0.5f,1.8f,0.5f);
						initPosition	=	Float3(0,1,0);//::UNIT_Y;
						slopeLimit		=	0.785f;
						stepOffset		=	0.5f;
						type			=	enCapsule;
						upDirType		=	1;
						skinWidth		=	0.2f;
						pCallBack		=	NULL;
					};
					
					Float3			size;			///<	x���� z��� y�߶�
					Float3			initPosition;	///<	��ʼλ��
					Real			slopeLimit;		///<	�¶�����
					Real			stepOffset;		///<	�ɿ�Խ��̨�׸߶�
					Real			skinWidth;		///<	Ƥ�����
					enumType		type;			///<	��ײ����
					UInt			upDirType;		///<	����������	x=0 y=1 z=2
					IHitCallBack*	pCallBack;		///<	�ص�����
				};
	
				/**	\brief	����λ��
				*   
				*	@remarks 	����λ��
				*	@see		IController
				*	@return   	void
				*	@param		Float3 vPosition
				*	@note
				*
				**/
				virtual	void		SetPosition(Float3	vPosition)	=	NULL;
				/**	\brief	��ȡλ��
				*   
				*	@remarks 	��ȡλ��
				*	@see		IController
				*	@return   	Client::Float3
				*	@note
				*
				**/
				virtual	Float3		GetPosition()					=	NULL;
				/**	\brief	�ƶ�
				*   
				*	@remarks 	�ƶ�
				*	@see		IController
				*	@return   	void
				*	@param		Float3 vDirection
				*	@note
				*
				**/
				virtual	void		Move(Float3	vDirection)		=	NULL;
	
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		IController
				*	@return   	Client::Physx::IController::enumType
				*	@note
				*
				**/
				virtual	enumType	GetType()						=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXCONTROLLER_HEAD_FILE