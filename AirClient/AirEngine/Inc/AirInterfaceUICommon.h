#ifndef INTERFACEUICOMMON_HEAD_FILE
#define INTERFACEUICOMMON_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Client{
	
		namespace	UI{
			namespace	Window{
				class	IControl;
			}
			/**	\brief	״̬ö��
			*
			*	״̬ö��
			*
			***/
			enum	enumStateType{
				enDisable,
				enNormal,
				enHover,
				enPush,
				enMax
			};
			/**	\brief	������Ϣ
			*
			*	������Ϣ
			*
			***/
			class	Message{
			public:
				enum	enumType{
					//����¼�
					enMouseEnter,		//
					enMouseLeave,
					enMouseLButtonDown,
					enMouseLButtonUp,
					enMouseMButtonDown,
					enMouseMButtonUp,
					enMouseRButtonDown,
					enMouseRButtonUp,
					enMouseWheelDown,
					enMouseWheelUp,
					enMouse3ButtonDown,
					enMouse3ButtonUp,
					enMouse4ButtonDown,
					enMouse4ButtonUp,
					enMouse5ButtonDown,
					enMouse5ButtonUp,
					enMouse6ButtonDown,
					enMouse6ButtonUp,
					enMouse7ButtonDown,
					enMouse7ButtonUp,
					//�����¼�
					enShortCutKeyDown,
					enShortCutKeyUp,
					enKeyUp,
					//��ͨ�¼�
					enEnableChange,
					enVisiableChange,
					enAlphaChange,
					enColorChange,
					enPositionChange,
					enSizeChange,
					enActiveChange,
	
					enMax
	
				};
				Message(Window::IControl*	pControl	=	NULL,Union4 u	=	0){
					m_State		=	u;
					m_pControl	=	pControl;
				}
				Window::IControl*	m_pControl;
				Union4				m_State;
			};
	
			/**	\brief	��ݼ����
			*
			*	��ݼ����
			*
			***/
			union	KeyUnion{
				KeyUnion(U8	mouse	=	0,U8 key	=	0,U1	bAlt	=	false,U1	bShift	=	false,	U1	bCtrl	=	false){
					Mouse	=	mouse;
					Key		=	key;
					Alt		=	bAlt;
					Shift	=	bShift;
					Ctrl	=	bCtrl;
				};
				/**	\brief	�ԱȰ���
				*   
				*	@remarks 	�ԱȰ���
				*	@see		ShortcutKey
				*	@return   	U1
				*	@param		ShortcutKey & key
				*	@note
				*
				**/
				inline	U1	Compare(KeyUnion&	key){
					return (Value==key.Value);
				};
				/**	\brief	�ж��Ƿ����
				*   
				*	@remarks 	�ж��Ƿ����
				*	@see		ShortcutKey
				*	@return   	U1
				*	@param		const ShortcutKey & key
				*	@note
				*
				**/
				U1	operator	==	(const KeyUnion&	key){
					return	(Value==key.Value);
				}
				U1	operator	<	(const KeyUnion&	key){
					return	(Value<key.Value);
				}
				/**	\brief	�����Ƿ���ҪAlt
				*   
				*	@remarks 	�����Ƿ���ҪAlt
				*	@see		ShortcutKey
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				inline	void	SetAlt(U1	bEnable){
					Alt		=	bEnable;
				};
				/**	\brief	�����Ƿ���ҪAlt
				*   
				*	@remarks 	�����Ƿ���ҪAlt
				*	@see		ShortcutKey
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				inline	void	SetCtrl(U1	bEnable){
					Ctrl		=	bEnable;
				};
				/**	\brief	�����Ƿ���ҪAlt
				*   
				*	@remarks 	�����Ƿ���ҪAlt
				*	@see		ShortcutKey
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				inline	void	SetShift(U1	bEnable){
					Shift	=	bEnable;
				}
				struct{
					U8					Mouse;		///<	���
					S8					MouseX;		///<	X��
					S8					MouseY;		///<	Y��
					S8					MouseZ;		///<	Z��
					U8					Key;		///<	����
					U8					Alt;		///<	Alt����
					U8					Shift;		///<	Shift����
					U8					Ctrl;		///<	Ctrl����
				};
				U64						Value;		///<	�Ƚ�ֵ
			};
	
			/**	\brief	�ص�����
			*
			*	�ص�����
			*
			***/
			class	FunctionBase{
			public:
				virtual ~FunctionBase(){};
				/**	\brief	����ִ�лص��ӿ�
				*
				*	����ִ�лص��ӿ�
				*
				***/
				virtual bool operator()(Message*	pMessage) = 0;
			};
	
			/**	\brief	��ͨ�����ص�
			*
			*	��ͨ�����ص�
			*
			***/
			class	Function	:	
				public	FunctionBase{
			public:
				typedef U1 (NormalCallBack)(Message*);
	
				Function(NormalCallBack* func) :
				m_pFunction(func)
				{}
	
				/**	\brief	���ûص�����
				*   
				*	@remarks 	���ûص�����
				*	@see		Function
				*	@return   	bool
				*	@param		const Event & evt
				*	@note
				*
				**/
				virtual bool operator()(Message*	pMessage){
					return m_pFunction(pMessage);
				}
	
				//private:
				NormalCallBack* m_pFunction;		///<	�ص�����
			};
	
			/**	\brief	��Ա�����ص�
			*
			*	��Ա�����ص�
			*
			***/
			template<typename	T_Member>
			class	MemberFunction	:
				public FunctionBase{
			public:
				//! Member function	typedef
				typedef U1(T_Member::*MemberCallBack)(Message*);
				MemberFunction(MemberCallBack func, T_Member* obj) :
				m_pFunction(func),
					m_pObject(obj){
	
				};
	
				/**	\brief	���ûص�����
				*   
				*	@remarks 	���ûص�����
				*	@see		MemberFunction
				*	@return   	bool
				*	@param		const Event & evt
				*	@note
				*
				**/
				virtual bool operator()(Message*	pMessage){
					return (m_pObject->*m_pFunction)(pMessage);
				}
	
				//private:
				MemberCallBack	m_pFunction;		///<	���Ա����
				T_Member*		m_pObject;			///<	��ָ��
			};
	
			/**	\brief	����������
			*
			*	����������
			*
			***/
			class	FunctionSlot{
			public:
				FunctionSlot(){m_pFunction=NULL;};
				FunctionSlot(U1 (*func)(Message*)){m_pFunction	=	new	Function(func);};
				//���벻��ȥ ����ʾ û�����غ������� 2 ��������ͷ����
				template<class T>
				FunctionSlot(U1 (T::*function)(Message*), T* obj)
					:m_pFunction(new	MemberFunction<T>(function,obj)){
				};
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		FunctionSlot
				*	@return   	void
				*	@note
				*
				**/
				void	Clean(){
					SAF_D(m_pFunction);
				}
	
				/**	\brief	�Ƿ�Ϊ��
				*   
				*	@remarks 	�Ƿ�Ϊ��
				*	@see		FunctionSlot
				*	@return   	U1
				*	@note
				*
				**/
				U1	IsNull(){return	m_pFunction	==	NULL;};
	
				FunctionBase*	m_pFunction;
			};
		}
	
	};
};
#endif // INTERFACEUICOMMON_HEAD_FILE