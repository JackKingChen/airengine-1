#ifndef INTERFACEUIEVENT_HEAD_FILE
#define INTERFACEUIEVENT_HEAD_FILE

#include "AirInterfaceUICommon.h"
namespace Air{
	
	namespace Client{
	
		namespace	UI{
			namespace	Event{
				/**	\brief	��Ϣ������
				*
				*	��Ϣ������
				*
				***/
				class	ENGINE_EXPORT	Sender{
				public:
					Sender();
					virtual	~Sender();
					/**	\brief	����¼�
					*
					*	����¼�
					*
					***/
					virtual	void	AddEvent(Message::enumType	type,const FunctionSlot& slot){
						m_pFunctionArray[type]	=	slot.m_pFunction;
					}
					
					/**	\brief	�Ƴ��¼�
					*   
					*	@remarks 	�Ƴ��¼�
					*	@see		Sender
					*	@return   	void
					*	@param		enumType type
					*	@note
					*
					**/
					void	RemoveEvent(Message::enumType	type);
					/**	\brief	�Ƴ������¼�
					*   
					*	@remarks 	�Ƴ������¼�
					*	@see		Sender
					*	@return   	void
					*	@note
					*
					**/
					void	RemoveAllEvent();
					/**	\brief	ִ���¼�
					*   
					*	@remarks 	ִ���¼�
					*	@see		Sender
					*	@return   	U1
					*	@param		enumType type
					*	@param		const Event & evt
					*	@note
					*
					**/
					U1	ExecuteEvent(Message::enumType	type,Message*	pMessage);
				private:
					FunctionBase* m_pFunctionArray[Message::enMax];		///<	�¼�����
				};
			};
		}
	};
};
#endif // INTERFACEUIEVENT_HEAD_FILE