#ifndef INTERFACEINPUTSYSTEM_HEAD_FILE
#define INTERFACEINPUTSYSTEM_HEAD_FILE

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "OIS.h"

namespace Air{
	
	namespace	Engine{
		namespace	Input{
			typedef	Air::Common::IPlugin	IPlugin;
		
			class State{
			public:
				State(){
					m_iX				=	0;
					m_iY				=	0;
					m_iXDelta			=	0;
					m_iYDelta			=	0;
					m_iZDelta			=	0;
		
					memset(m_KeyArray,	0,MAX_NAME);
					memset(m_MouseArray,0,8);
				};
				Air::SInt			m_iX;
				Air::SInt			m_iY;
				Air::SInt			m_iXDelta;
				Air::SInt			m_iYDelta;
				Air::SInt			m_iZDelta;
				Air::S8				m_KeyArray[MAX_NAME];		///<	���̰���״̬
				Air::S8				m_MouseArray[8];			///<	��갴��״̬
			};
		
			/**	\brief	����ϵͳ�ӿ�
			*
			*	����ϵͳ�ӿ�
			*
			***/
			class	ISystem	:	
				public	Common::ISystem,
				public	State{
			public:
				ISystem():Common::ISystem("InputSystem"){

				};
		
				enum	enumType{
					enKey,
					enMouse,
					enJoyStick
				};
				/**	\brief	��Ӽ��̻ص�
				*   
				*	@remarks 	��Ӽ��̻ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Add(::OIS::KeyListener*	pListener)					=	NULL;
				/**	\brief	������ص�
				*   
				*	@remarks 	������ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		MouseListener * pListener
				*	@note
				*
				**/
				virtual	void		Add(::OIS::MouseListener*	pListener)				=	NULL;
				/**	\brief	����ֱ��ص�
				*   
				*	@remarks 	����ֱ��ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		JoyStickListener * pListener
				*	@note
				*
				**/
				virtual void		Add(::OIS::JoyStickListener*	pListener)		=	NULL;
		
				/**	\brief	�Ƴ����̻ص�
				*   
				*	@remarks 	�Ƴ����̻ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Remove(::OIS::KeyListener*	pListener)				=	NULL;
				/**	\brief	�Ƴ����ص�
				*   
				*	@remarks 	�Ƴ����ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual	void		Remove(::OIS::MouseListener*	pListener)			=	NULL;
				/**	\brief	�Ƴ��ֱ��ص�
				*   
				*	@remarks 	�Ƴ��ֱ��ص�
				*	@see		ISystem
				*	@return   	void
				*	@param		KeyListener * pListener
				*	@note
				*
				**/
				virtual void		Remove(::OIS::JoyStickListener*	pListener)		=	NULL;
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
				virtual void		Enable(enumType	type,U1	bEnable)					=	NULL;
				/**	\brief	�ص��Ƿ�������
				*   
				*	@remarks 	�ص��Ƿ�������
				*	@see		ISystem
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				virtual U1			IsEnable(enumType	type)							=	NULL;
				/**	\brief	�������лص�
				*   
				*	@remarks 	�������лص�
				*	@see		ISystem
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				virtual void		EnableAll(U1	bEnable)								=	NULL;
		
		
				/**	\brief	��ȡ��Ϣ
				*
				*	��ȡ��Ϣ
				*
				***/
				virtual U1			Capture()	=	NULL;
		
				
				/**	\brief	�������λ��
				*   
				*	@remarks 	�������λ��
				*	@see		ISystem
				*	@return   	void
				*	@param		SInt x
				*	@param		SInt y
				*	@note
				*
				**/
				//virtual	void		SetCursorPosition(SInt x,SInt y)	=	NULL;
		
			public:
		
			};
		};
	};
};


#endif // INTERFACEINPUTSYSTEM_HEAD_FILE