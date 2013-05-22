#ifndef GAMECONTROL_HEAD_FILE
#define GAMECONTROL_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceInputSystem.h"

namespace Air{
	namespace	Game{
		/**	\brief	״̬
		*
		*	״̬
		*
		***/
		enum	enumMoveState{
			enMS_NoMove			=	0,
			enMS_Left			=	1,
			enMS_Right			=	2,
			enMS_Run			=	4,
			enMS_Back			=	8,
			enMS_RunLeft		=	enMS_Run	|enMS_Left,
			enMS_RunRight		=	enMS_Run	|enMS_Right,
			enMS_BackLeft		=	enMS_Back	|enMS_Left,
			enMS_BackRight		=	enMS_Back	|enMS_Right,
		};
		enum	enumActorState{
			enAS_Stand,
			enAS_Walk,
			enAS_Idle,
			enAS_Jump,
			enAS_Jumping,
			enAS_Dieing,
			enAS_Death,
			enAS_Casting
		};
		/**	\brief	����
		*
		*	����
		*
		***/
		enum	enumAction{
			enA_None,
			enA_LAttack,
			enA_MAttack,
			enA_RAttack,
			enA_SpaceAction,
			enA_MagicAttack1,
			enA_MagicAttack2,
			enA_MagicAttack3,
			enA_MagicAttack4,
			enA_MagicAttack5,
			enA_Health,
		};
	
		enum	enumGameState{
			enLogin,
			enGame,
			enExit
		};

		enum	enumKeyEventType{
			enKET_MouseDown,
			enKET_MouseUp,
			enKET_MouseMove,
			enKET_KeyDown,
			enKET_KeyUp,
		};
		enum	enumKeyHelpType{
			enKHT_Control,
			enKHT_Alt,
			enKHT_Shift
		};

		struct Key;
		typedef 	void	(__stdcall *KeyCallback)(void*	pThis,const Key& k);
		template <typename T>
		inline KeyCallback	ConverertFunction(T t){
#ifdef _X86_
			U32* pp =	(U32*)&t;	
#else
			U64* pp	=	(U64*)&t;	
#endif
			KeyCallback* ppCB	=	(KeyCallback*)pp;
			return *ppCB;
		};
		struct Key{
			union{
				struct{
					U32 control	:	1;
					U32	alt		:	1;
					U32	shift	:	1;
					U32	evt		:	8;
					U32	mouse	:	8;
					U32	key		:	8;
					
				};
				U32 uiKeyValue;
			};
			void*			pObject;
			KeyCallback		pCB;
		};
		typedef STD_HASHMAP<U32,Key>	KeyCallBackMap;
		/**	\brief	����״̬�ص�
		*
		*	����״̬�ص�
		*
		***/
		class	IActionState{
		public:
			virtual	void	OnActorState(enumActorState	state,enumMoveState mstate)	=	NULL;
			virtual	void	OnAction(enumAction	action)	=	NULL;
			virtual	void	OnGameState(enumGameState	state)	=	NULL;
		};
			
		/**	\brief	��Ϸ�������
		*
		*	��Ϸ�������
		*
		***/
		class	ENGINE_EXPORT	Control	:
			public	Common::IProduct,
			public	::OIS::KeyListener,
			public	::OIS::MouseListener,
			public	::OIS::JoyStickListener{
		public:
			Control(CAString& strName);
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
			virtual	U1		Update(const FrameTime& frameTime);
	
			/**	\brief	���ü�����Ϣ����
			*   
			*	@remarks 	���ü�����Ϣ����
			*	@see		Control
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetKeyboardEnable(U1	bEnable){m_bEnableKeyboard	=	bEnable;};
			/**	\brief	���������Ϣ����
			*   
			*	@remarks 	���������Ϣ����
			*	@see		Control
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetMouseEnable(U1	bEnable){m_bEnableMouse	=	bEnable;};
			/**	\brief	�����ֱ���Ϣ����
			*   
			*	@remarks 	�����ֱ���Ϣ����
			*	@see		Control
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetJoyStickEnable(U1	bEnable){m_bEnableJoyStick	=	bEnable;};
			/**	\brief	�����Ƿ�����
			*   
			*	@remarks 	�����Ƿ�����
			*	@see		Control
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		GetKeyboardEnable(){return	m_bEnableKeyboard;};
			/**	\brief	����Ƿ�����
			*   
			*	@remarks 	����Ƿ�����
			*	@see		Control
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		GetMouseEnable(){return	m_bEnableMouse;};
			/**	\brief	�ֱ��Ƿ�����
			*   
			*	@remarks 	�ֱ��Ƿ�����
			*	@see		Control
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		GetJoyStickEnable(){return	m_bEnableJoyStick;};
	
			/**	\brief	����������Ϣ����
			*   
			*	@remarks 	����������Ϣ����
			*	@see		Control
			*	@return   	void
			*	@note
			*
			**/
			inline	void	SetAllEnable(U1	bEnable){
				m_bEnableKeyboard	=	bEnable;
				m_bEnableMouse		=	bEnable;
				m_bEnableJoyStick	=	bEnable;
			};
	
			/**	\brief	���һ���ӿ���
			*   
			*	@remarks 	���һ���ӿ���
			*	@see		Control
			*	@return   	void
			*	@param		Control * pControl
			*	@note
			*
			**/
			void	AddControl(Control*	pControl);
			/**	\brief	�Ƴ�һ���ӿ���
			*   
			*	@remarks 	�Ƴ�һ���ӿ���
			*	@see		Control
			*	@return   	void
			*	@param		Control * pControl
			*	@note
			*
			**/
			void	RemoveControl(Control*	pControl);
	
			/**	\brief	��ȡ���ƽڵ�
			*   
			*	@remarks 	��ȡ���ƽڵ�
			*	@see		Control
			*	@return   	ISceneNode*
			*	@note
			*
			**/
			virtual	Engine::SceneNode*		GetControlNode();
	
			/**	\brief	���ûص�
			*   
			*	@remarks 	���ûص�
			*	@see		Control
			*	@return   	void
			*	@param		IActionState * pCallback
			*	@note
			*
			**/
			inline	void	SetCallback(IActionState*	pCallback){
				m_pActionStateCallback	=	pCallback;
			}
			void			RegisterMouseCallback(OIS::MouseButtonID	mouse,const void* pObject,KeyCallback pCB,enumKeyEventType evt=enKET_MouseUp,U1 bControl=false,U1 bAlt=false,U1 bShift=false);
			void			RegisterKeyCallback(OIS::KeyCode		key,const void* pObject,KeyCallback pCB,enumKeyEventType evt=enKET_KeyUp,U1 bControl=false,U1 bAlt=false,U1 bShift=false);
			void			RegisterKeyCallback(const Key& k);
			void			UnRegisterKeyCallback(U32 key);

			Ray				GetMouseRay(S32 x,S32 y);
		protected:
			Engine::Input::State*	m_pInputState;			///<	����״̬
			U1						m_bEnableKeyboard;		///<	�Ƿ����ü�����Ϣ
			U1						m_bEnableMouse;			///<	�Ƿ����������Ϣ
			U1						m_bEnableJoyStick;		///<	�Ƿ������ֱ���Ϣ
			typedef		std::list<Control*>		ControlList;
			typedef		ControlList::iterator	ControlListItr;
	
			ControlList		m_lstControl;
	
			IActionState*	m_pActionStateCallback;
			KeyCallBackMap			m_mapKeyCallback;
		};

	}
	

};
#endif // GAMECONTROL_HEAD_FILE