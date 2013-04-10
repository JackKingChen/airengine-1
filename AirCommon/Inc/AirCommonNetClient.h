#ifndef COMMONNETCLIENT_HEAD_FILE
#define COMMONNETCLIENT_HEAD_FILE

#include "AirCommonNet.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
#include "AirCommonNetSendThread.h"
#include "AirCommonNetReceiveThread.h"
#include "AirCommonNetConnect.h"
namespace Air{
	
	namespace Common{
	
		class	COMMON_EXPORT	NetClient	:	
			public	IProduct,
			public	NetConnect
		{
		public:
			static AString	ProductTypeName;
			struct	Info{
				Info(){	
					pListener	=	NULL;
				};
				AString			strIP;
				AString			strPort;
				NetListener*	pListener;
			};
		public:
			NetClient(CAString&	strName,Info*	pInfo);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		NetClient
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		NetClient
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
			*	@param		AString& strtPort
			*	@note
			*
			**/
			virtual	U1	OnConnected(U32	socket,AString&	strIP,AString&	strPort);
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
	
			/**	\brief	�Ƿ�������
			*   
			*	@remarks 	�Ƿ�������
			*	@see		NetClient
			*	@return   	U1
			*	@note
			*
			**/
			U1			IsConnected();
	
			/**	\brief	���ӷ�����
			*   
			*	@remarks 	���ӷ�����
			*	@see		NetClient
			*	@return   	U1
			*	@param		Info & info
			*	@note
			*
			**/
			U1			Connect(Info&	info);
			/**	\brief	�Ͽ�����
			*   
			*	@remarks 	�Ͽ�����
			*	@see		NetClient
			*	@return   	U1
			*	@note
			*
			**/
			U1			DisConnect();
	
	
			Info				m_Info;
			NetReceiveThread	m_ThreadReceive;
		};
	
	};
};
#endif // COMMONNETCLIENT_HEAD_FILE