#ifndef COMMONNETLISTENTHREAD_HEAD_FILE
#define COMMONNETLISTENTHREAD_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonThread.h"
#include "AirCommonLock.h"
namespace Air{
	
	namespace Common{
		
		class	COMMON_EXPORT	NetListenThread	
			:	public	Thread{
		public:
			NetListenThread();
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		NetListenThread
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@note
			*
			**/
			virtual	U1	Start(U32	uiSocket,NetListener*	pListener);
	
			/**	\brief	��Ϣ����ѭ��
			*   
			*	@remarks 	��Ϣ����ѭ��
			*	@see		NetReceiveThread
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	RepetitionRun();
	
			U32				m_Socket;
			NetListener*	m_pListener;
		};
		
	
	};
};
#endif // COMMONNETLISTENTHREAD_HEAD_FILE