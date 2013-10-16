#ifndef COMMONNETSERVER_HEAD_FILE
#define COMMONNETSERVER_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
#include "AirCommonNetSendThread.h"
#include "AirCommonNetReceiveThread.h"
#include "AirCommonNetListenThread.h"
#include "AirCommonNetConnect.h"
namespace Air{
	
	namespace Common{
	
		/**	\brief	������
		*
		*	������
		*
		***/
		class	MCOMMON_EXPORT	NetServer	:
			public	IProduct,
			public	NetConnect
		{
		public:
			static AString	ProductTypeName;
			struct	Info{
				Info(){
					pListener	=	NULL;
				};
				U16				usPort;
				NetListener*	pListener;
			};
		public:
			NetServer(CAString&	strName,Info*	pInfo);
	
			
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		NetServer
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		NetServer
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	
			/**	\brief	�������
			*   
			*	@remarks 	������ɣ��ͻ������������ӷ������ɹ� ����Ƿ���� �����пͻ������룩
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 socket
			*	@param		AString& strIP
			*	@param		AString& strPort
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
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		NetConnect
			*	@return   	U1
			*	@param		const void * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	SendAll(const void*	pData,U32	uiSize);
	
			/**	\brief	���Զ�Ŀ�귢������
			*   
			*	@remarks 	���Զ�Ŀ�귢������
			*	@see		NetServer
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@param		const void * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	Send(U32	uiSocket,const void*	pData,U32	uiSize);
		protected:
		private:
			Info				m_Info;				///<	������Ϣ
	
			NetListenThread		m_ThreadListen;		///<	�����߳�
			ReceiveThreadMap	m_mapReceiveThread;	///<	�����߳�
	
			ReceiveThreadList	m_lstUnUsedThread;	///<	δʹ�õ��߳�
			CriticalSection		m_ReceiveCS;
		};

	};
};
#endif // COMMONNETSERVER_HEAD_FILE