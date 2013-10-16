#ifndef COMMONNETSENDTHREAD_HEAD_FILE
#define COMMONNETSENDTHREAD_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonThread.h"
#include "AirCommonLock.h"

namespace Air{
	
	
	namespace Common{
	
		
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
			virtual	U1	Start(NetListener*	pListener);
	
			/**	\brief	���������
			*   
			*	@remarks 	���������
			*	@see		NetSendThread
			*	@return   	U1
			*	@param		SendPack * pack
			*	@note
			*
			**/
			virtual	U1	Push(NetPack*	pack);
	
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
			CriticalSection	m_CS;
			Event			m_SendEvent;
			bool			m_bWaiting;
			SendPackList	m_lstSendPack;
			NetListener*	m_pListener;
		};
		
	
	};
};
#endif // COMMONNETSENDTHREAD_HEAD_FILE