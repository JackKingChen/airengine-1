#ifndef COMMONNETSENDTHREAD_HEAD_FILE
#define COMMONNETSENDTHREAD_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonThread.h"
#include "AirCommonLock.h"

namespace Air{
	
	
	namespace Common{
		struct SendBuffer{
			U8	Buffer[8192];
			U32	uiSize;
			U32	uiSend;
		};
		
		typedef	std::queue<NetPack*>	SendPackList;
		/**	\brief	���Ͷ���
		*
		*	���Ͷ���
		*
		***/
		class	MCOMMON_EXPORT	NetSendThread	
			:	public	Thread{
		public:
			NetSendThread();
			virtual	~NetSendThread();
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		NetSendThread
			*	@return   	U1
			*	@param		NetListener * pListener
			*	@note
			*
			**/
			virtual	U1	Start(U32 uiSocket,NetListener*	pListener);
	
			/**	\brief	���������
			*   
			*	@remarks 	���������
			*	@see		NetSendThread
			*	@return   	U1
			*	@param		SendPack * pack
			*	@note
			*
			**/
			virtual	U1	Send(const void*	pData,U32	uiSize);
	
			/**	\brief	����ѭ��
			*   
			*	@remarks 	����ѭ��
			*	@see		NetSendThread
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	RepetitionRun();
		protected:
			virtual	U32	GetSendData(void* p);
		protected:
			CriticalSection	m_CS;
			Event			m_SendEvent;
			U32				m_uiSocket;
			NetListener*	m_pListener;
			SendBuffer		m_SendBuffer[2];
			U32				m_SendIndex;
			OVERLAPPED		m_Overlapped;
		};
		
	
	};
};
#endif // COMMONNETSENDTHREAD_HEAD_FILE