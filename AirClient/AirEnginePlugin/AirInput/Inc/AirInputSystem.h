#ifndef ENGINEINPUTSYSTEM_HEAD_FILE
#define ENGINEINPUTSYSTEM_HEAD_FILE

#include "AirInterfaceInputSystem.h"



namespace Air{
	
	namespace Engine{
	
		namespace	Input{
			class	System	: 
				public	::OIS::KeyListener, 
				public	::OIS::MouseListener, 
				public	::OIS::JoyStickListener,
				public	ISystem{
			public:
				System();
	
				virtual ~System();
	
				//����
				virtual bool keyPressed( const ::OIS::KeyEvent &arg );
				virtual bool keyReleased( const ::OIS::KeyEvent &arg );
				//���
				virtual bool mouseMoved( const ::OIS::MouseEvent &arg );
				virtual bool mousePressed( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id );
				virtual bool mouseReleased( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id );
	
				//�ֱ�
				virtual bool buttonPressed( const ::OIS::JoyStickEvent &arg, int button );
				virtual bool buttonReleased( const ::OIS::JoyStickEvent &arg, int button );
				virtual bool axisMoved( const ::OIS::JoyStickEvent &arg, int axis );
				virtual bool povMoved( const ::OIS::JoyStickEvent &arg, int pov );
				virtual bool vector3Moved( const ::OIS::JoyStickEvent &arg, int index);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization();
	
	
				virtual U1	Start();
				virtual U1	Stop();
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release();
	
				/**	\brief	��Ӽ��̻ص�
				*   
				*	@remarks 	��Ӽ��̻ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Add(::OIS::KeyListener*	pListener);
				/**	\brief	������ص�
				*   
				*	@remarks 	������ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		MouseListener * pListener
				*	@note
				*
				**/
				virtual	void		Add(::OIS::MouseListener*	pListener);
				/**	\brief	����ֱ��ص�
				*   
				*	@remarks 	����ֱ��ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		JoyStickListener * pListener
				*	@note
				*
				**/
				virtual void		Add(::OIS::JoyStickListener*	pListener);
	
				/**	\brief	�Ƴ����̻ص�
				*   
				*	@remarks 	�Ƴ����̻ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Remove(::OIS::KeyListener*	pListener);
				/**	\brief	�Ƴ����ص�
				*   
				*	@remarks 	�Ƴ����ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual	void		Remove(::OIS::MouseListener*	pListener);
				/**	\brief	�Ƴ��ֱ��ص�
				*   
				*	@remarks 	�Ƴ��ֱ��ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Remove(::OIS::JoyStickListener*	pListener);
	
				/**	\brief	���ûص�
				*   
				*	@remarks 	���ûص�
				*	@see		ISystem
				*	@return   	void
				*	@param		AString strName
				*	@param		U1 bEnable
				*	@note
				*
				**/
				virtual void		Enable(enumType	type,U1	bEnable);
				/**	\brief	�ص��Ƿ�������
				*   
				*	@remarks 	�ص��Ƿ�������
				*	@see		ISystem
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				virtual U1			IsEnable(enumType	type);
				/**	\brief	�������лص�
				*   
				*	@remarks 	�������лص�
				*	@see		ISystem
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				virtual void		EnableAll(U1	bEnable);
	
				/**	\brief	�������
				*   
				*	@remarks 	�������
				*	@see		System
				*	@return   	void
				*	@note
				*
				**/
				void				RemoveAll();
	
				/**	\brief	��������״̬
				*   
				*	@remarks 	��������״̬
				*	@see		System
				*	@return   	void
				*	@note
				*
				**/
				U1				Capture();
	
			private:
	
				::OIS::InputManager*	m_pInputMgr;		///<	���������
				::OIS::Keyboard*		m_pKeyboard;		///<	����
				::OIS::Mouse*			m_pMouse;			///<	���
				::OIS::JoyStick*		m_pJoyStick[4];		///<	�ֱ�
	
				U1				m_bMouseEnable;		///<	�Ƿ��������ص�
				U1				m_bKeyEnable;		///<	�Ƿ����ü��̻ص�
				U1				m_bJoyStickEnable;	///<	�Ƿ������ֱ��ص�
	
				typedef	std::list<::OIS::MouseListener*>		MouseListenList;
				typedef	std::list<::OIS::KeyListener*>			KeyListenList;
				typedef	std::list<::OIS::JoyStickListener*>	JoyStickListenList;
	
				MouseListenList		m_lstMouse;			///<	���ص��б�
				KeyListenList		m_lstKey;			///<	���̻ص��б�
				JoyStickListenList	m_lstJoyStick;		///<	�ֱ��ص��б�
			};
	
	
		}
	
	
	};
};
#endif // ENGINEINPUTSYSTEM_HEAD_FILE