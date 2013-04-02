#ifndef INTERFACEUIControlCONTROL_HEAD_FILE
#define INTERFACEUIControlCONTROL_HEAD_FILE

#include "AirInterfaceUIWindowState.h"
#include "OIS.h"
namespace Air{
	
	namespace Engine{
	
		class		Font;
	
		namespace	UI{
			namespace	Window{
	
	
				/**	\brief	UI����Ԫ��
				*	
				*	UI����Ԫ��
				*
				***/
				class	ENGINE_EXPORT	IControl	:
					public	State,
					public	::OIS::MouseListener,
					public	::OIS::KeyListener,
					public	Common::IProduct{
				public:
					typedef		std::list<IControl*>			WindowList;
					typedef		WindowList::iterator			WindowListItr;
				public:
					static	Float2	TopLeft;
					static	Float2	TopMiddle;
					static	Float2	TopRight;
					static	Float2	MiddleLeft;
					static	Float2	Middle;
					static	Float2	MiddleRight;
					static	Float2	BottomLeft;
					static	Float2	BottomMiddle;
					static	Float2	BottomRight;
				public:
					IControl(CAString&	strName,StateArray*	pArray,Info*	pInfo);
	
					/**	\brief	����
					*   
					*	@remarks 	����
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Create();
					/**	\brief	�ݻ�
					*   
					*	@remarks 	�ݻ�
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Destroy();
					/**	\brief	���һ���ӽڵ�
					*   
					*	@remarks 	���һ���ӽڵ�
					*	@see		IControl
					*	@return   	void
					*	@param		IControl * pWindow
					*	@note
					*
					**/
					void			AddChild(IControl*	pWindow);
					/**	\brief	�Ƴ�һ���ӽڵ�
					*   
					*	@remarks 	�Ƴ�һ���ӽڵ�
					*	@see		IControl
					*	@return   	void
					*	@param		IControl * pWindow
					*	@note
					*
					**/
					void			RemoveChild(IControl*	pWindow);
	
					/**	\brief	�Ƴ������ӽڵ�
					*   
					*	@remarks 	�Ƴ������ӽڵ�
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			RemoveAllChild();
	
					/**	\brief	�ݻ��ӽڵ�
					*   
					*	@remarks 	�ݻ��ӽڵ�
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			DestroyChild(IControl*	pWindow);
	
					/**	\brief	�ݻ������ӽڵ�
					*   
					*	@remarks 	�ݻ������ӽڵ�
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			DestroyAllChild();
	
					/**	\brief	����
					*	
					*	@remarks 	����
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	Updata();
					virtual	void	SetCenter(Float2	vCenter	=	TopLeft);
					virtual	Float2	GetCenter();
					virtual	void	SetPosition(Float2&	vPosition);
					virtual	Float2	GetPosition();
					virtual	Float2	GetAbsolutelyPosition();
					virtual	void	SetWindowSize(Float2&	vSize);
					virtual	Float2	GetWindowSize();
					virtual	void	SetColor(Float3 vColor);
					virtual	Float3	GetColor();
					virtual	void	SetAlpha(Real	fAlpha);
					virtual	Real	GetAlpha();
					virtual	void	SetColorAlpha(Float4	v);
					virtual	Float4	GetColorAlpha();
					virtual	Float4	GetPositionSize();
					/**	\brief	�ж��Ƿ�����ڴ�������
					*   
					*	@remarks 	�ж��Ƿ�����ڴ�������
					*	@see		IControl
					*	@return   	IControl*
					*	@note
					*
					**/
					virtual	IControl*		IsMouseInWindow();
	
					/**	\brief	��Ⱦ
					*   
					*	@remarks 	��Ⱦ
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	Render();
	
					virtual	void	RenderCache();
					virtual	void	RenderUI();
	
					/**	\brief	�Ƿ�Ϊ������
					*   
					*	@remarks 	�Ƿ�Ϊ������
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					U1				IsRootWindow(){
						return	(m_pParent==NULL);
					}
	
					/**	\brief	ˢ��
					*   
					*	@remarks 	ˢ��
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			Refresh();
	
					/**	\brief	��ȡ��һ���Ӵ���
					*   
					*	@remarks 	��ȡ��һ���Ӵ���
					*	@see		IControl
					*	@return   	IControl*
					*	@note
					*
					**/
					IControl*		GetFirstChildWindow();
					/**	\brief	��ȡ�Ӵ���
					*   
					*	@remarks 	��ȡ�Ӵ���
					*	@see		IControl
					*	@return   	IControl*
					*	@param		AString strName
					*	@note
					*
					**/
					IControl*		GetChildWindow(AString	strName);
					/**	\brief	��ȾԪ��
					*   
					*	@remarks 	
					*	@see		State
					*	@return   	void
					*	@param		ElementArray&	eArray
					*	@note
					*
					**/
					virtual	void	BeforeRenderElement(ElementArray&	eArray);
	
					/**	\brief	�Ƿ񱻸ı�
					*   
					*	@remarks 	����λ�� ��С ��ɫ ����
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					U1				IsChanged();
					/**	\brief	��������UI��Ҫ������Ⱦ
					*   
					*	@remarks 	����豸��ʧʱ �Ļָ�
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					void			SetNeedReRender();
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
				protected:
					/**	\brief	���ø��ڵ�
					*   
					*	@remarks 	���ø��ڵ�
					*	@see		IControl
					*	@return   	void
					*	@param		IControl * pParent
					*	@note
					*
					**/
					void	SetParent(IControl*	pParent);
	
					/**	\brief	ˢ�´�С
					*   
					*	@remarks 	ˢ�´�С
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RefreshSize();
					/**	\brief	ˢ��λ��
					*   
					*	@remarks 	ˢ��λ��
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RefreshPosition();
	
					/**	\brief	ˢ����ɫ
					*   
					*	@remarks 	ˢ����ɫ
					*	@see		IControl
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RefreshColor();
				protected:
					Float4				m_vAbsolutelyPosition;
					
					
					U32*				m_piOrginScreenWidth;			///<	��Ļ��
					U32*				m_piOrginScreenHeight;			///<	��Ļ��
	
					IControl*			m_pParent;						///<	���ڵ�
					WindowList			m_lstWindow;
	
					//Font*				m_pFont;
					RenderTarget*		m_pTarget;
				};
			}
		};
	
	};
};
#endif // INTERFACEUIControl_HEAD_FILE