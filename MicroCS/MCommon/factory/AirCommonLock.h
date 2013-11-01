#ifndef COMMONLOCK_HEAD_FILE
#define COMMONLOCK_HEAD_FILE

#include "MCommon.h"
namespace Air{
	
	namespace Common{
		/**	\brief	�ٽ�������
		*
		*	�ٽ�������
		*
		***/
		class	CriticalSection{
		public:
			inline	CriticalSection(){
				InitializeCriticalSection(&m_CriticalSection);
			};
	
			~CriticalSection(){
				DeleteCriticalSection(&m_CriticalSection);
			};
	
			inline	U32		TryEnter(){
				return TryEnterCriticalSection(&m_CriticalSection); 
			};
			inline	void	Enter(){
				EnterCriticalSection(&m_CriticalSection); 
			};
			inline	void	Leave(){
				LeaveCriticalSection(&m_CriticalSection); 
			};
	
			CRITICAL_SECTION	m_CriticalSection;//�ٽ������ü���
		};
	
		/**	\brief	�������
		*
		*	�������
		*
		***/
		class	Mutex{
		public:
			Mutex(AString	strName	=	""){
				m_hMutex	=	CreateMutexA(NULL,FALSE,strName.c_str());
			};
			~Mutex(){
				CloseHandle(m_hMutex);
			}
	
			/**	\brief	�ȴ��������
			*   
			*	@remarks 	�ȴ��������
			*	@see		Mutex
			*	@return   	void
			*	@param		U32 uiTime
			*	@note
			*
			**/
			inline	void	Enter(U32	uiTime	=	INFINITE){
				WaitForSingleObject(m_hMutex,uiTime);
			};
	
			/**	\brief	�ͷŻ������
			*   
			*	@remarks 	�ͷŻ������
			*	@see		Mutex
			*	@return   	void
			*	@note
			*
			**/
			inline	void	Leave(){
				ReleaseMutex(m_hMutex);
	
			};
	
			HANDLE	m_hMutex;	///<	���������
		};
		
		/**	\brief	�¼�
		*
		*	�¼�
		*
		***/
		class	Event{
		public:
			Event(const AChar*	strName=NULL){
				if(strName==NULL){
					m_hEvent	=	CreateEventA(NULL,FALSE,FALSE,"");
				}else{
					m_hEvent	=	CreateEventA(NULL,FALSE,FALSE,strName);
				}
				
			};
			~Event(){
				CloseHandle(m_hEvent);
			}

			/**	\brief	�����¼�
			*   
			*	@remarks 	�����¼�
			*	@see		Event
			*	@return   	void
			*	@note
			*
			**/
			void	Reset(){
				SetEvent(m_hEvent);
			}
			/**	\brief	�ȴ��¼�
			*   
			*	@remarks 	�ȴ��¼�
			*	@see		Event
			*	@return   	void
			*	@param		U32		uiTime
			*	@note
			*
			**/
			void	Wait(U32	uiTime	=	INFINITE){
				WaitForSingleObject(m_hEvent,uiTime);
			}
			HANDLE	m_hEvent;
		};
#ifndef	LOCK_ADD
#define LOCK_ADD(x,val)	InterlockedAdd(&x,val)
#endif
#ifndef	LOCK_ADD_1
#define LOCK_ADD_1(x)	InterlockedIncrement(&x)
#endif
#ifndef	LOCK_SUB_1
#define LOCK_SUB_1(x)	InterlockedDecrement(&x)
#endif
	};
};
#endif // COMMONLOCK_HEAD_FILE