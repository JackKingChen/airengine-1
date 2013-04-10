#ifndef INTERFACEUISYSTEM_HEAD_FILE
#define INTERFACEUISYSTEM_HEAD_FILE


#include "AirInterfaceUIWindowControl.h"
#include "AirInterfaceUIRenderer.h"
#include "AirInterfaceUIKeyProcess.h"
#include "AirInterfaceUIStaticText.h"
namespace Air{
	
	namespace Engine{
	
		namespace	UI{
	
			typedef		Window::IControl	IWindow;
			/**	\brief	����ϵͳ����
			*
			*	����ϵͳ����
			*
			***/
			class	ENGINE_EXPORT	ISystem	:
				public	IPlugin,
				public	IFactoryManager,
				public	Renderer,
				public	::OIS::KeyListener,
				public	::OIS::MouseListener,
				public	KeyProcess{
			public:
				ISystem();
	
				/**	\brief	��ʼ��
				*   
				*	@remarks 	
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization();
				/**	\brief	��ʼ
				*   
				*	@remarks 	��ʼ
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Start();
				/**	\brief	�ͷ�
				*   
				*	@remarks 	�ͷ�
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release();
	
				/**	\brief	����UI
				*   
				*	@remarks 	����UI ���ڴ��������Ϣ������Ϣ �Ա㴦���Ƿ��д��ڱ�����
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Update();
	
				/**	\brief	��Ⱦ
				*   
				*	@remarks 	��Ⱦ
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Render();
				/**	\brief	���ü����
				*   
				*	@remarks 	���ü����
				*	@see		ISystem
				*	@return   	void
				*	@param		IControl * pWindow
				*	@note
				*
				**/
				virtual	void	SetActive(Window::IControl*	pWindow);
	
				/**	\brief	����һ������
				*   
				*	@remarks 	����һ������
				*	@see		ISystem
				*	@return   	IControl*
				*	@param		AString strName
				*	@param		AString strType
				#	@param		void*	pParam
				*	@note
				*
				**/
				virtual	Window::IControl*	CreateIWindow(AString	strName,AString	strType,void*	pParam	=	NULL);
				/**	\brief	�ݻ�һ������
				*   
				*	@remarks 	�ݻ�һ������
				*	@see		ISystem
				*	@return   	void
				*	@param		Window::IControl * pWindow
				*	@note
				*
				**/
				virtual	void		DestroyIWindow(Window::IControl*	pWindow);
	
				/**	\brief	���ü����
				*   
				*	@remarks 	���ü����
				*	@see		ISystem
				*	@return   	void
				*	@param		Window::IControl * pWindow
				*	@note
				*
				**/
				virtual	void		SetRootWindow(Window::IControl*	pWindow);
	
				/**	\brief	��ȡ������
				*   
				*	@remarks 	��ȡ������
				*	@see		ISystem
				*	@return   	Window::IControl*
				*	@note
				*
				**/
				Window::IControl*	GetRootWindow(){
					return	m_pRootWindow;
				};
				/**	\brief	��ȡ�����
				*   
				*	@remarks 	��ȡ�����
				*	@see		ISystem
				*	@return   	Window::IControl*
				*	@note
				*
				**/
				Window::IControl*	GetActiveWindow(){
					return	m_pActiveWindow;
				};
				/**	\brief	���̰����¼�
				*   
				*	@remarks 	���̰����¼�
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::KeyEvent & arg
				*	@note
				*
				**/
				virtual bool	keyPressed( const ::OIS::KeyEvent &arg );
				/**	\brief	�����ͷ��¼�
				*   
				*	@remarks 	�����ͷ��¼�
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::KeyEvent & arg
				*	@note
				*
				**/
				virtual bool	keyReleased( const ::OIS::KeyEvent &arg );
				/**	\brief	����ƶ��¼�
				*   
				*	@remarks 	����ƶ��¼�
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::MouseEvent & arg
				*	@note
				*
				**/
				virtual bool	mouseMoved( const ::OIS::MouseEvent &arg );
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
				virtual bool	mousePressed( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id );
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
				virtual bool	mouseReleased( const ::OIS::MouseEvent &arg, ::OIS::MouseButtonID id );
				/**	\brief	Windows��Ϣ�ص�
				*   
				*	@remarks 	Windows��Ϣ�ص�
				*	@see		IEngine
				*	@return   	long
				*	@param		HWND hWnd
				*	@param		UINT uMsg
				*	@param		WPARAM wParam
				*	@param		LPARAM lParam
				*	@param		bool * pbNoFurtherProcessing
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual long	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,void* pUserContext );
	
				virtual	void	OnResetDevice();
			protected:
				/**	\brief	��Ⱦ������
				*   
				*	@remarks 	��Ⱦ������
				*	@see		ISystem
				*	@return   	void
				*	@param		Window::IControl * pWindow
				*	@note
				*
				**/
				void	RenderWindowTree(Window::IControl*	pWindow);
	
				/**	\brief	���µ�ǰ����״̬
				*   
				*	@remarks 	���µ�ǰ����״̬
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyUnion & k
				*	@param		const OIS::KeyCode & code
				*	@param		U1 bDown
				*	@param		U1 bMouse
				*	@note
				*
				**/
				void	UpdateKey(KeyUnion&	k,const ::OIS::KeyCode&	code,U1	bDown,U1	bMouse	=	false);
			protected:
				Window::IControl*		m_pRootWindow;
				Window::IControl*		m_pActiveWindow;
				KeyUnion				m_Key;
			};
		}
	
	};
};
#endif // INTERFACEUISYSTEM_HEAD_FILE