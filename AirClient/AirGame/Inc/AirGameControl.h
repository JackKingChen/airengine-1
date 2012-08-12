#ifndef GAMECONTROL_HEAD_FILE
#define GAMECONTROL_HEAD_FILE

#include "AirGame.h"
#include "AirGameHeader.h"
namespace Air{
	
	namespace Client{
	
		namespace	Game{
			/**	\brief	״̬
			*
			*	״̬
			*
			***/
			enum	enumActorState{
				enStand,
				enWalk,
				enIdle,
				enLeft,
				enRight,
				enRun,
				enBack,
				enJump,
				enJumping,
				enDieing,
				enDeath,
				enCasting
			};
			/**	\brief	����
			*
			*	����
			*
			***/
			enum	enumAction{
				enNone,
				enAttack,
				enMagicAttack1,
				enMagicAttack2,
				enMagicAttack3,
				enMagicAttack4,
				enMagicAttack5,
				enHealth,
			};
	
			enum	enumGameState{
				enLogin,
				enGame,
				enExit
			};
			/**	\brief	����״̬�ص�
			*
			*	����״̬�ص�
			*
			***/
			class	IActionState{
			public:
				virtual	void	OnActorState(enumActorState	state)	=	NULL;
				virtual	void	OnAction(enumAction	action)	=	NULL;
				virtual	void	OnGameState(enumGameState	state)	=	NULL;
			};
			
			/**	\brief	��Ϸ�������
			*
			*	��Ϸ�������
			*
			***/
			class	GAME_EXPORT	Control	:
				public	OIS::KeyListener,
				public	OIS::MouseListener,
				public	OIS::JoyStickListener{
			public:
				Control();
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
				virtual	SceneNode*		GetControlNode();
	
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
	
			protected:
				Input::State*	m_pInputState;			///<	����״̬
				U1				m_bEnableKeyboard;		///<	�Ƿ����ü�����Ϣ
				U1				m_bEnableMouse;			///<	�Ƿ����������Ϣ
				U1				m_bEnableJoyStick;		///<	�Ƿ������ֱ���Ϣ
				typedef		std::list<Control*>		ControlList;
				typedef		ControlList::iterator	ControlListItr;
	
				ControlList		m_lstControl;
	
				IActionState*	m_pActionStateCallback;
			};
		}
	
	};
};
#endif // GAMECONTROL_HEAD_FILE