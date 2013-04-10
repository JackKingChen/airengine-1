#ifndef GAMEFPSCONTROL_HEAD_FILE
#define GAMEFPSCONTROL_HEAD_FILE


#include "AirGameControl.h"
namespace Air{
	
	
	
	namespace	Game{
		class Section;
			
		/**	\brief	��һ�˳����
		*
		*	��һ�˳����
		*
		***/
		class	ENGINE_EXPORT	FPSControl	:
			public	Common::IProduct,
			public	Control
			{
		public:
			static AString	ProductTypeName;
			/**	\brief	������Ϣ
			*
			*	������Ϣ
			*
			***/
			struct	Info{
				Info(){
					pSection		=	NULL;
					//vPosition		=	Vector3::ZERO;
					vVelocity		=	3.0f;
					vCameraHeight	=	1.8f;
					pCamera			=	NULL;
				};
				Section*	pSection;		///<	�ؿ�����
				Float3		vPosition;		///<	��ʼλ��
				Real		vVelocity;		///<	�ƶ��ٶ�
				Real		vCameraHeight;	///<	������߶�
				Engine::Camera*		pCamera;
					
			};
		public:
			FPSControl(AString	strName,Info*	pInfo);
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		FPSControl
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		FPSControl
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	
			/**	\brief	��ȡ�����
			*   
			*	@remarks 	��ȡ�����
			*	@see		FPSControl
			*	@return   	Camera*
			*	@note
			*
			**/
			virtual	Engine::Camera*	GetCamera();
	
	
			/**	\brief	���̰����¼�
			*   
			*	@remarks 	���̰����¼�
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::KeyEvent & arg
			*	@note
			*
			**/
			virtual bool	keyPressed( const OIS::KeyEvent &arg );
			/**	\brief	�����ͷ��¼�
			*   
			*	@remarks 	�����ͷ��¼�
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::KeyEvent & arg
			*	@note
			*
			**/
			virtual bool	keyReleased( const OIS::KeyEvent &arg );
			/**	\brief	����ƶ��¼�
			*   
			*	@remarks 	����ƶ��¼�
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::MouseEvent & arg
			*	@note
			*
			**/
			virtual bool	mouseMoved( const OIS::MouseEvent &arg );
			/**	\brief	��갴���¼�
			*   
			*	@remarks 	��갴���¼�
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::MouseEvent & arg
			*	@param		Input::MouseButtonID id
			*	@note
			*
			**/
			virtual bool	mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			/**	\brief	����ͷ��¼�
			*   
			*	@remarks 	����ͷ��¼�
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::MouseEvent & arg
			*	@param		Input::MouseButtonID id
			*	@note
			*
			**/
			virtual bool	mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
			/**	\brief	�ֱ���ť����
			*   
			*	@remarks 	�ֱ���ť����
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::JoyStickEvent & arg
			*	@param		int button
			*	@note
			*
			**/
			virtual bool	buttonPressed( const OIS::JoyStickEvent &arg, int button );
			/**	\brief	�ֱ���ť�ͷ�
			*   
			*	@remarks 	�ֱ���ť�ͷ�
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::JoyStickEvent & arg
			*	@param		int button
			*	@note
			*
			**/
			virtual bool	buttonReleased( const OIS::JoyStickEvent &arg, int button );
			/**	\brief	�ֱ������
			*   
			*	@remarks 	�ֱ������
			*	@see		Control
			*	@return   	bool
			*	@param		const Input::JoyStickEvent & arg
			*	@param		int axis
			*	@note
			*
			**/
			virtual bool	axisMoved( const OIS::JoyStickEvent &arg, int axis );
			/**	\brief	ÿ֡����
			*   
			*	@remarks 	ÿ֡����
			*	@see		Control
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		OnFrameMove();
	
			/**	\brief	��ȡ���ƽڵ�
			*   
			*	@remarks 	
			*	@see		FPSControl
			*	@return   	SceneNode*
			*	@note
			*
			**/
			virtual	Engine::SceneNode*	GetControlNode();
			/**	\brief	λ��
			*   
			*	@remarks 	λ��
			*	@see		FPSControl
			*	@return   	void
			*	@param		Vector3 vPosition
			*	@note
			*
			**/
			virtual	void		SetPosition(Float3	vPosition);
	
			inline	U1			IsStateChange(){
				return	(m_State!=m_LastState);
			};
	
		protected:
			Info					m_Info;
			Section*				m_pSection;
			Engine::Camera*			m_pCamera;				///<	���������
			Engine::SceneNode*		m_pNode;				///<	�����������ڵ�
			Engine::SceneNode*		m_pLRNode;				///<	������ת���ƽڵ�
			Engine::SceneNode*		m_pCameraUDNode;		///<	��ͷ����ҡ�����ƽڵ�
			Engine::SceneNode*		m_pCameraNode;			///<	������ڵ�
			Real					m_fLRAngle;				///<	������ת�Ƕ�
			Real					m_fUDAngle;				///<	������ת�Ƕ�
			Real					m_fCurrentLRAngle;		///<	��ǰ������ת�Ƕ�
			Real					m_fCurrentUDAngle;		///<	������ת�Ƕ�
			//Physics::IController*		m_pController;			///<	����ģ��Ŀ�����
			enumActorState			m_State;			
			enumActorState			m_LastState;
			enumAction				m_Action;
		};

	}
	
};
#endif // GAMEFPSCONTROL_HEAD_FILE