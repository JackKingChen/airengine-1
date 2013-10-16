#ifndef COMMONNETCONNECT_HEAD_FILE
#define COMMONNETCONNECT_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonNetSendThread.h"
namespace Air{
	
	namespace Common{
	
		/**	\brief	��������
		*
		*	��������
		*
		***/
		class	MCOMMON_EXPORT	NetConnect	:
			public	NetListener{
		public:
			NetConnect();
			virtual	~NetConnect();
	
			/**	\brief	����SOCKET
			*   
			*	@remarks 	����SOCKET
			*	@see		NetConnect
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateSocket();
			/**	\brief	�ݻ�SOCKET
			*   
			*	@remarks 	�ݻ�SOCKET
			*	@see		NetConnect
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	DestroySocket();
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		NetConnect
			*	@return   	U1
			*	@param		void * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	Send(void*	pData,U32	uiSize);
			/**	\brief	�������
			*   
			*	@remarks 	������ɣ��ͻ������������ӷ������ɹ� ����Ƿ���� �����пͻ������룩
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 socket
			*	@param		AString& strIP
			*	@param		AString& strtPort
			*	@note
			*
			**/
			virtual	U1	OnConnected(U32	socket,CAString&	strIP,CAString&	strPort);
	
			/**	\brief	����رջص�
			*   
			*	@remarks 	����رջص�	�����������رջ����쳣�ر�
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@note
			*
			**/
			virtual	U1	OnClose(U32	uiSocket);
	
			/**	\brief	�����յ���������
			*   
			*	@remarks 	�����յ���������
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@param		AChar * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize);
			/**	\brief	��ȡSOCKET
			*   
			*	@remarks 	��ȡSOCKET
			*	@see		NetConnect
			*	@return   	U32
			*	@note
			*
			**/
			U32			GetSocket();
		protected:	
			U32				m_Socket;					///<	SOCKET ID
			NetSendThread	m_ThreadSend;
			NetListener*	m_pListener;
		};
	
		
	
	};
};
#endif // COMMONNETCONNECT_HEAD_FILE