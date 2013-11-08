#include "StdAfx.h"
#include "IOCPModel.h"
//#include "MainDlg.h"




// ÿһ���������ϲ������ٸ��߳�(Ϊ������޶ȵ��������������ܣ���������ĵ�)
#define WORKER_THREADS_PER_PROCESSOR 2
// ͬʱͶ�ݵ�Accept���������(���Ҫ����ʵ�ʵ�����������)
#define MAX_POST_ACCEPT              10
// ���ݸ�Worker�̵߳��˳��ź�
#define EXIT_CODE                    NULL


// �ͷ�ָ��;����Դ�ĺ�

// �ͷ�ָ���
#define RELEASE(x)                      {if(x != NULL ){delete x;x=NULL;}}
// �ͷž����
#define RELEASE_HANDLE(x)               {if(x != NULL && x!=INVALID_HANDLE_VALUE){ CloseHandle(x);x = NULL;}}
// �ͷ�Socket��
#define RELEASE_SOCKET(x)               {if(x !=INVALID_SOCKET) { closesocket(x);x=INVALID_SOCKET;}}



CIOCPModel::CIOCPModel(void):
							m_nThreads(0),
							m_hShutdownEvent(NULL),
							m_hIOCompletionPort(NULL),
							m_phWorkerThreads(NULL),
							m_strIP("127.0.0.1"),
							m_nPort(DEFAULT_PORT),
							//m_pMain(NULL),
							m_lpfnAcceptEx( NULL ),
							m_pListenContext( NULL ),
							m_pListener(NULL)
{
}


CIOCPModel::~CIOCPModel(void)
{
	// ȷ����Դ�����ͷ�
	this->Stop();
}




///////////////////////////////////////////////////////////////////
// �������̣߳�  ΪIOCP�������Ĺ������߳�
//         Ҳ����ÿ����ɶ˿��ϳ�����������ݰ����ͽ�֮ȡ�������д�����߳�
///////////////////////////////////////////////////////////////////

DWORD WINAPI CIOCPModel::_WorkerThread(LPVOID lpParam)
{    
	THREADPARAMS_WORKER* pParam = (THREADPARAMS_WORKER*)lpParam;
	CIOCPModel* pIOCPModel = (CIOCPModel*)pParam->pIOCPModel;
	int nThreadNo = (int)pParam->nThreadNo;
	
	printf(("�������߳�������ID: %d.\n"),nThreadNo);

	OVERLAPPED           *pOverlapped = NULL;
	PER_SOCKET_CONTEXT   *pSocketContext = NULL;
	DWORD                dwBytesTransfered = 0;

	// ѭ����������֪�����յ�Shutdown��ϢΪֹ
	while (WAIT_OBJECT_0 != WaitForSingleObject(pIOCPModel->m_hShutdownEvent, 0))
	{
		BOOL bReturn = GetQueuedCompletionStatus(
			pIOCPModel->m_hIOCompletionPort,
			&dwBytesTransfered,
			(PULONG_PTR)&pSocketContext,
			&pOverlapped,
			INFINITE);

		// ����յ������˳���־����ֱ���˳�
		if ( EXIT_CODE==(DWORD)pSocketContext )
		{
			break;
		}

		// �ж��Ƿ�����˴���
		if( !bReturn )  
		{  
			DWORD dwErr = GetLastError();

			// ��ʾһ����ʾ��Ϣ
			if( !pIOCPModel->HandleError( pSocketContext,dwErr ) )
			{
				break;
			}

			continue;  
		}  
		else  
		{  	
			// ��ȡ����Ĳ���
			PER_IO_CONTEXT* pIoContext = CONTAINING_RECORD(pOverlapped, PER_IO_CONTEXT, m_Overlapped);  

			// �ж��Ƿ��пͻ��˶Ͽ���
			if((0 == dwBytesTransfered) && ( RECV_POSTED==pIoContext->m_OpType || SEND_POSTED==pIoContext->m_OpType))  
			{  
				//TRACE( _T("�ͻ��� %s:%d �Ͽ�����."),inet_ntoa(pSocketContext->m_ClientAddr.sin_addr), ntohs(pSocketContext->m_ClientAddr.sin_port) );
				// �ͷŵ���Ӧ����Դ
				pIOCPModel->_RemoveContext( pSocketContext );

 				continue;  
			}  
			else
			{
				switch( pIoContext->m_OpType )  
				{  
					 // Accept  
				case ACCEPT_POSTED:
					{ 
						pIoContext->m_uiTotalSize	=	dwBytesTransfered;
						// Ϊ�����Ӵ���ɶ��ԣ�������ר�ŵ�_DoAccept�������д�����������
						pIOCPModel->_DoAccpet( pSocketContext, pIoContext );						
						

					}
					break;

					// RECV
				case RECV_POSTED:
					{
						pIoContext->m_uiTotalSize	+=	dwBytesTransfered;
						// Ϊ�����Ӵ���ɶ��ԣ�������ר�ŵ�_DoRecv�������д����������
						pIOCPModel->_DoRecv( pSocketContext,pIoContext );
					}
					break;

					// SEND
					// �����Թ���д�ˣ�Ҫ������̫���ˣ���������⣬Send�������������һЩ
				case SEND_POSTED:
					{
						pIoContext->m_uiSend += dwBytesTransfered;
						pIOCPModel->_DoSend(pSocketContext,pIoContext);
					}
					break;
				default:
					// ��Ӧ��ִ�е�����
					TRACE(_T("_WorkThread�е� pIoContext->m_OpType �����쳣.\n"));
					break;
				} //switch
			}//if
		}//if

	}//while

	TRACE(_T("�������߳� %d ���˳�.\n"),nThreadNo);

	// �ͷ��̲߳���
	RELEASE(lpParam);	

	return 0;
}



//====================================================================================
//
//				    ϵͳ��ʼ������ֹ
//
//====================================================================================




////////////////////////////////////////////////////////////////////
// ��ʼ��WinSock 2.2
bool CIOCPModel::LoadSocketLib()
{    
	WSADATA wsaData;
	int nResult;
	nResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	// ����(һ�㶼�����ܳ���)
	if (NO_ERROR != nResult)
	{
		TRACE(_T("��ʼ��WinSock 2.2ʧ�ܣ�\n"));
		return false; 
	}

	return true;
}

//////////////////////////////////////////////////////////////////
//	����������
bool CIOCPModel::Start()
{
	// ��ʼ���̻߳�����
	InitializeCriticalSection(&m_csContextList);

	// ����ϵͳ�˳����¼�֪ͨ
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// ��ʼ��IOCP
	if (false == _InitializeIOCP())
	{
		TRACE(_T("��ʼ��IOCPʧ�ܣ�\n"));
		return false;
	}
	else
	{
		printf(("\nIOCP��ʼ�����\n."));
	}

	// ��ʼ��Socket
	if( false==_InitializeListenSocket() )
	{
		TRACE(_T("Listen Socket��ʼ��ʧ�ܣ�\n"));
		this->_DeInitialize();
		return false;
	}
	else
	{
		TRACE(_T("Listen Socket��ʼ�����."));
	}

	TRACE(_T("ϵͳ׼���������Ⱥ�����....\n"));

	return true;
}


////////////////////////////////////////////////////////////////////
//	��ʼ����ϵͳ�˳���Ϣ���˳���ɶ˿ں��߳���Դ
void CIOCPModel::Stop()
{
	if( m_pListenContext!=NULL && m_pListenContext->m_Socket!=INVALID_SOCKET )
	{
		// ����ر���Ϣ֪ͨ
		SetEvent(m_hShutdownEvent);

		for (int i = 0; i < m_nThreads; i++)
		{
			// ֪ͨ���е���ɶ˿ڲ����˳�
			PostQueuedCompletionStatus(m_hIOCompletionPort, 0, (DWORD)EXIT_CODE, NULL);
		}

		// �ȴ����еĿͻ�����Դ�˳�
		WaitForMultipleObjects(m_nThreads, m_phWorkerThreads, TRUE, INFINITE);

		// ����ͻ����б���Ϣ
		this->_ClearContextList();

		// �ͷ�������Դ
		this->_DeInitialize();

		TRACE(_T("ֹͣ����\n"));
	}	
}


////////////////////////////////
// ��ʼ����ɶ˿�
bool CIOCPModel::_InitializeIOCP()
{
	// ������һ����ɶ˿�
	m_hIOCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0 );

	if ( NULL == m_hIOCompletionPort)
	{
		TRACE(_T("������ɶ˿�ʧ�ܣ��������: %d!\n"), WSAGetLastError());
		return false;
	}

	// ���ݱ����еĴ�����������������Ӧ���߳���
	m_nThreads = WORKER_THREADS_PER_PROCESSOR * _GetNoOfProcessors();
	
	// Ϊ�������̳߳�ʼ�����
	m_phWorkerThreads = new HANDLE[m_nThreads];
	
	// ���ݼ�����������������������߳�
	DWORD nThreadID;
	for (int i = 0; i < m_nThreads; i++)
	{
		THREADPARAMS_WORKER* pThreadParams = new THREADPARAMS_WORKER;
		pThreadParams->pIOCPModel = this;
		pThreadParams->nThreadNo  = i+1;
		m_phWorkerThreads[i] = ::CreateThread(0, 0, _WorkerThread, (void *)pThreadParams, 0, &nThreadID);
	}

	TRACE(_T(" ���� _WorkerThread %d ��.\n"), m_nThreads );

	return true;
}


/////////////////////////////////////////////////////////////////
// ��ʼ��Socket
bool CIOCPModel::_InitializeListenSocket()
{
	// AcceptEx �� GetAcceptExSockaddrs ��GUID�����ڵ�������ָ��
	GUID GuidAcceptEx = WSAID_ACCEPTEX;  
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS; 

	// ��������ַ��Ϣ�����ڰ�Socket
	struct sockaddr_in ServerAddress;

	// �������ڼ�����Socket����Ϣ
	m_pListenContext = new PER_SOCKET_CONTEXT;

	// ��Ҫʹ���ص�IO�������ʹ��WSASocket������Socket���ſ���֧���ص�IO����
	m_pListenContext->m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_pListenContext->m_Socket) 
	{
		TRACE(_T("��ʼ��Socketʧ�ܣ��������: %d.\n"), WSAGetLastError());
		return false;
	}
	else
	{
		TRACE(_T("WSASocket() ���.\n"));
	}

	// ��Listen Socket������ɶ˿���
	if( NULL== CreateIoCompletionPort( (HANDLE)m_pListenContext->m_Socket, m_hIOCompletionPort,(DWORD)m_pListenContext, 0))  
	{  
		TRACE(_T("�� Listen Socket����ɶ˿�ʧ�ܣ��������: %d/n"), WSAGetLastError());  
		RELEASE_SOCKET( m_pListenContext->m_Socket );
		return false;
	}
	else
	{
		TRACE(_T("Listen Socket����ɶ˿� ���.\n"));
	}

	// ����ַ��Ϣ
	ZeroMemory((char *)&ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	// ������԰��κο��õ�IP��ַ�����߰�һ��ָ����IP��ַ 
	//ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);                      
	GetLocalIP();
	TRACE(_T("Local IP %s\n"),m_strIP.c_str());
	ServerAddress.sin_addr.s_addr = inet_addr(m_strIP.c_str());         
	ServerAddress.sin_port = htons(m_nPort);                          

	// �󶨵�ַ�Ͷ˿�
	if (SOCKET_ERROR == bind(m_pListenContext->m_Socket, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress))) 
	{
		TRACE(_T("bind()����ִ�д���.\n"));
		return false;
	}
	else
	{
		TRACE(_T("bind() ���.\n"));
	}

	// ��ʼ���м���
	if (SOCKET_ERROR == listen(m_pListenContext->m_Socket,SOMAXCONN))
	{
		TRACE(_T("Listen()����ִ�г��ִ���.\n"));
		return false;
	}
	else
	{
		TRACE(_T("Listen() ���.\n"));
	}

	// ʹ��AcceptEx��������Ϊ���������WinSock2�淶֮���΢�������ṩ����չ����
	// ������Ҫ�����ȡһ�º�����ָ�룬
	// ��ȡAcceptEx����ָ��
	DWORD dwBytes = 0;  
	if(SOCKET_ERROR == WSAIoctl(
		m_pListenContext->m_Socket, 
		SIO_GET_EXTENSION_FUNCTION_POINTER, 
		&GuidAcceptEx, 
		sizeof(GuidAcceptEx), 
		&m_lpfnAcceptEx, 
		sizeof(m_lpfnAcceptEx), 
		&dwBytes, 
		NULL, 
		NULL))  
	{  
		TRACE(_T("WSAIoctl δ�ܻ�ȡAcceptEx����ָ�롣�������: %d\n"), WSAGetLastError()); 
		this->_DeInitialize();
		return false;  
	}  

	// ��ȡGetAcceptExSockAddrs����ָ�룬Ҳ��ͬ��
	if(SOCKET_ERROR == WSAIoctl(
		m_pListenContext->m_Socket, 
		SIO_GET_EXTENSION_FUNCTION_POINTER, 
		&GuidGetAcceptExSockAddrs,
		sizeof(GuidGetAcceptExSockAddrs), 
		&m_lpfnGetAcceptExSockAddrs, 
		sizeof(m_lpfnGetAcceptExSockAddrs),   
		&dwBytes, 
		NULL, 
		NULL))  
	{  
		TRACE(_T("WSAIoctl δ�ܻ�ȡGuidGetAcceptExSockAddrs����ָ�롣�������: %d\n"), WSAGetLastError());  
		this->_DeInitialize();
		return false; 
	}  


	// ΪAcceptEx ׼��������Ȼ��Ͷ��AcceptEx I/O����
	for( int i=0;i<MAX_POST_ACCEPT;i++ )
	{
		// �½�һ��IO_CONTEXT
		PER_IO_CONTEXT* pAcceptIoContext = m_pListenContext->GetNewIoContext();

		if( false==this->_PostAccept( pAcceptIoContext ) )
		{
			m_pListenContext->RemoveContext(pAcceptIoContext);
			return false;
		}
	}

	TRACE( _T("Ͷ�� %d ��AcceptEx�������"),MAX_POST_ACCEPT );

	return true;
}

////////////////////////////////////////////////////////////
//	����ͷŵ�������Դ
void CIOCPModel::_DeInitialize()
{
	// ɾ���ͻ����б�Ļ�����
	DeleteCriticalSection(&m_csContextList);

	// �ر�ϵͳ�˳��¼����
	RELEASE_HANDLE(m_hShutdownEvent);

	// �ͷŹ������߳̾��ָ��
	for( int i=0;i<m_nThreads;i++ )
	{
		RELEASE_HANDLE(m_phWorkerThreads[i]);
	}
	
	RELEASE(m_phWorkerThreads);

	// �ر�IOCP���
	RELEASE_HANDLE(m_hIOCompletionPort);

	// �رռ���Socket
	RELEASE(m_pListenContext);

	TRACE(_T("�ͷ���Դ���.\n"));
}


//====================================================================================
//
//				    Ͷ����ɶ˿�����
//
//====================================================================================


//////////////////////////////////////////////////////////////////
// Ͷ��Accept����
bool CIOCPModel::_PostAccept( PER_IO_CONTEXT* pAcceptIoContext )
{
//	ASSERT( INVALID_SOCKET!=m_pListenContext->m_Socket );

	// ׼������
	DWORD dwBytes = 0;  
	pAcceptIoContext->m_OpType = ACCEPT_POSTED;  
	WSABUF *p_wbuf   = &pAcceptIoContext->m_wsaBuf;
	OVERLAPPED *p_ol = &pAcceptIoContext->m_Overlapped;
	
	// Ϊ�Ժ�������Ŀͻ�����׼����Socket( ������봫ͳaccept�������� ) 
	pAcceptIoContext->m_sockAccept  = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);  
	if( INVALID_SOCKET==pAcceptIoContext->m_sockAccept )  
	{  
		TRACE(_T("��������Accept��Socketʧ�ܣ��������: %d"), WSAGetLastError()); 
		return false;  
	} 

	// Ͷ��AcceptEx
	if(FALSE == m_lpfnAcceptEx( m_pListenContext->m_Socket, pAcceptIoContext->m_sockAccept, p_wbuf->buf, p_wbuf->len - ((sizeof(SOCKADDR_IN)+16)*2),   
								sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, &dwBytes, p_ol))  
	{  
		if(WSA_IO_PENDING != WSAGetLastError())  
		{  
			TRACE(_T("Ͷ�� AcceptEx ����ʧ�ܣ��������: %d"), WSAGetLastError());  
			return false;  
		}  
	} 

	return true;
}

////////////////////////////////////////////////////////////
// ���пͻ��������ʱ�򣬽��д���
// �����е㸴�ӣ���Ҫ�ǿ������Ļ����Ϳ����׵��ĵ���....
// ������������Ļ�����ɶ˿ڵĻ������������һ�����

// ��֮��Ҫ֪�����������ListenSocket��Context��������Ҫ����һ�ݳ������������Socket��
// ԭ����Context����Ҫ���������Ͷ����һ��Accept����
//
bool CIOCPModel::_DoAccpet( PER_SOCKET_CONTEXT* pSocketContext, PER_IO_CONTEXT* pIoContext )
{
	SOCKADDR_IN* ClientAddr = NULL;
	SOCKADDR_IN* LocalAddr = NULL;  
	int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);  

	///////////////////////////////////////////////////////////////////////////
	// 1. ����ȡ������ͻ��˵ĵ�ַ��Ϣ
	// ��� m_lpfnGetAcceptExSockAddrs �����˰�~~~~~~
	// ��������ȡ�ÿͻ��˺ͱ��ض˵ĵ�ַ��Ϣ������˳��ȡ���ͻ��˷����ĵ�һ�����ݣ���ǿ����...
	this->m_lpfnGetAcceptExSockAddrs(pIoContext->m_wsaBuf.buf, pIoContext->m_wsaBuf.len - ((sizeof(SOCKADDR_IN)+16)*2),  
		sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, (LPSOCKADDR*)&LocalAddr, &localLen, (LPSOCKADDR*)&ClientAddr, &remoteLen);  

	//TRACE( _T("�ͻ��� %s:%d ����.\n"), inet_ntoa(ClientAddr->sin_addr), ntohs(ClientAddr->sin_port) );
	//TRACE( _T("�ͻ��� %s:%d ��Ϣ��%s.\n"),inet_ntoa(ClientAddr->sin_addr), ntohs(ClientAddr->sin_port),pIoContext->m_wsaBuf.buf );
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. ������Ҫע�⣬���ﴫ��������ListenSocket�ϵ�Context�����Context���ǻ���Ҫ���ڼ�����һ������
	// �����һ���Ҫ��ListenSocket�ϵ�Context���Ƴ���һ��Ϊ�������Socket�½�һ��SocketContext

	PER_SOCKET_CONTEXT* pNewSocketContext = new PER_SOCKET_CONTEXT;
	pNewSocketContext->m_Socket           = pIoContext->m_sockAccept;
	memcpy(&(pNewSocketContext->m_ClientAddr), ClientAddr, sizeof(SOCKADDR_IN));

	if(m_pListener!=NULL){
		m_pListener->OnConnected(pNewSocketContext);
	}

	// ����������ϣ������Socket����ɶ˿ڰ�(��Ҳ��һ���ؼ�����)
	if( false==this->_AssociateWithIOCP( pNewSocketContext ) )
	{
		RELEASE( pNewSocketContext );
		return false;
	}  
	// 2.5�������͵�IOContext �ڽ�������_DoRecv �п��ܻᷢ����������  ����Ҫ�Ƚ���Send
	pNewSocketContext->CreateSendIoContext();

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. �������������µ�IoContext�����������Socket��Ͷ�ݵ�һ��Recv��������
	PER_IO_CONTEXT* pNewIoContext	=	pNewSocketContext->GetNewIoContext();
	pNewIoContext->m_OpType			=	RECV_POSTED;
	pNewIoContext->m_sockAccept		=	pNewSocketContext->m_Socket;
	pNewIoContext->m_uiTotalSize	=	pIoContext->m_uiTotalSize;
	// ���Buffer��Ҫ���������Լ�����һ�ݳ���
	memcpy( pNewIoContext->m_szBuffer,pIoContext->m_szBuffer,pIoContext->m_uiTotalSize );

	// �����֮�󣬾Ϳ��Կ�ʼ�����Socket��Ͷ�����������
	if( false==this->_DoRecv( pNewSocketContext,pNewIoContext) )
	{
		pNewSocketContext->RemoveContext( pNewIoContext );
		return false;
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////
	// 4. ���Ͷ�ݳɹ�����ô�Ͱ������Ч�Ŀͻ�����Ϣ�����뵽ContextList��ȥ(��Ҫͳһ���������ͷ���Դ)
	this->_AddToContextList( pNewSocketContext );

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 5. ʹ�����֮�󣬰�Listen Socket���Ǹ�IoContext���ã�Ȼ��׼��Ͷ���µ�AcceptEx
	pIoContext->ResetBuffer();
	return this->_PostAccept( pIoContext ); 	
}

////////////////////////////////////////////////////////////////////
// Ͷ�ݽ�����������
bool CIOCPModel::_PostRecv( PER_IO_CONTEXT* pIoContext )
{
	// ��ʼ������
	DWORD dwFlags = 0;
	DWORD dwBytes = 0;
	pIoContext->m_wsaBuf.buf	=	&pIoContext->m_szBuffer[pIoContext->m_uiTotalSize];
	pIoContext->m_wsaBuf.len	=	MAX_BUFFER_LEN - pIoContext->m_uiTotalSize;

	WSABUF *p_wbuf   = &pIoContext->m_wsaBuf;
	OVERLAPPED *p_ol = &pIoContext->m_Overlapped;

	pIoContext->ResetBuffer();
	pIoContext->m_OpType = RECV_POSTED;

	// ��ʼ����ɺ󣬣�Ͷ��WSARecv����
	int nBytesRecv = WSARecv( pIoContext->m_sockAccept, p_wbuf, 1, &dwBytes, &dwFlags, p_ol, NULL );

	// �������ֵ���󣬲��Ҵ���Ĵ��벢����Pending�Ļ����Ǿ�˵������ص�����ʧ����
	if ((SOCKET_ERROR == nBytesRecv) && (WSA_IO_PENDING != WSAGetLastError()))
	{
		TRACE(_T("Ͷ�ݵ�һ��WSARecvʧ�ܣ�"));
		return false;
	}
	return true;
}

bool CIOCPModel::_PostSend( PER_IO_CONTEXT* pIoContext ){
		// ��ʼ������
	DWORD dwFlags = 0;
	DWORD dwSendNumBytes = 0;
	pIoContext->m_wsaBuf.buf	=	&pIoContext->m_szBuffer[pIoContext->m_uiSend];
	pIoContext->m_wsaBuf.len	=	pIoContext->m_uiTotalSize - pIoContext->m_uiSend;

	WSABUF *p_wbuf   = &pIoContext->m_wsaBuf;
	OVERLAPPED *p_ol = &pIoContext->m_Overlapped;

	pIoContext->m_OpType = SEND_POSTED;

	//Ͷ��WSASend���� -- ��Ҫ�޸�
	int nRet = WSASend(pIoContext->m_sockAccept, &pIoContext->m_wsaBuf, 1, &dwSendNumBytes, dwFlags,
		&pIoContext->m_Overlapped, NULL);

	// �������ֵ���󣬲��Ҵ���Ĵ��벢����Pending�Ļ����Ǿ�˵������ص�����ʧ����
	if ((SOCKET_ERROR == nRet) && (WSA_IO_PENDING != WSAGetLastError()))
	{
		TRACE(_T("Ͷ��WSASendʧ��\n"));
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////
// ���н��յ����ݵ����ʱ�򣬽��д���
bool CIOCPModel::_DoRecv( PER_SOCKET_CONTEXT* pSocketContext, PER_IO_CONTEXT* pIoContext )
{
	// �Ȱ���һ�ε�������ʾ���֣�Ȼ�������״̬��������һ��Recv����
	SOCKADDR_IN* ClientAddr = &pSocketContext->m_ClientAddr;
	//TRACE( _T("�յ�  %s:%d ��Ϣ��%s\n"),inet_ntoa(ClientAddr->sin_addr), ntohs(ClientAddr->sin_port),pIoContext->m_wsaBuf.buf );
	if(m_pListener!=NULL){
		m_pListener->OnRecvComplated(pSocketContext,pIoContext);
	}
	// Ȼ��ʼͶ����һ��WSARecv����
	return _PostRecv( pIoContext );
}

bool CIOCPModel::_DoSend( PER_SOCKET_CONTEXT* pSocketContext, PER_IO_CONTEXT* pIoContext )
{
	if (pIoContext->m_uiSend < pIoContext->m_uiTotalSize)
	{
		//����δ�ܷ����꣬������������
		return _PostSend(pIoContext);
	}
	else
	{				
		
		if(m_pListener!=NULL){
			m_pListener->OnSendComplated(pSocketContext,pIoContext);
		}
	}
	return true;
}

/////////////////////////////////////////////////////
// �����(Socket)�󶨵���ɶ˿���
bool CIOCPModel::_AssociateWithIOCP( PER_SOCKET_CONTEXT *pContext )
{
	// �����ںͿͻ���ͨ�ŵ�SOCKET�󶨵���ɶ˿���
	HANDLE hTemp = CreateIoCompletionPort((HANDLE)pContext->m_Socket, m_hIOCompletionPort, (DWORD)pContext, 0);

	if (NULL == hTemp)
	{
		TRACE(_T("ִ��CreateIoCompletionPort()���ִ���.������룺%d"),GetLastError());
		return false;
	}

	return true;
}




//====================================================================================
//
//				    ContextList ��ز���
//
//====================================================================================


//////////////////////////////////////////////////////////////
// ���ͻ��˵������Ϣ�洢��������
void CIOCPModel::_AddToContextList( PER_SOCKET_CONTEXT *pHandleData )
{
	EnterCriticalSection(&m_csContextList);

	m_arrayClientContext.push_back(pHandleData);	
	
	LeaveCriticalSection(&m_csContextList);
}

////////////////////////////////////////////////////////////////
//	�Ƴ�ĳ���ض���Context
void CIOCPModel::_RemoveContext( PER_SOCKET_CONTEXT *pSocketContext )
{
	if(m_pListener!=NULL){
		m_pListener->OnClosed(pSocketContext);
	}
	SOCKET	uiSocket	=	pSocketContext->m_Socket;
	EnterCriticalSection(&m_csContextList);

	std::list<PER_SOCKET_CONTEXT*>::iterator	i	=	m_arrayClientContext.begin();
	for( ;i!=m_arrayClientContext.end();i++ )
	{
		if( pSocketContext==*i)
		{
			RELEASE( pSocketContext );			
			m_arrayClientContext.erase(i);			
			break;
		}
	}

	LeaveCriticalSection(&m_csContextList);


}

////////////////////////////////////////////////////////////////
// ��տͻ�����Ϣ
void CIOCPModel::_ClearContextList()
{
	EnterCriticalSection(&m_csContextList);

	std::list<PER_SOCKET_CONTEXT*>::iterator	i	=	m_arrayClientContext.begin();
	for( ;i!=m_arrayClientContext.end();i++ )
	{
		delete	*i;
	}

	m_arrayClientContext.clear();

	LeaveCriticalSection(&m_csContextList);
}



//====================================================================================
//
//				       ����������������
//
//====================================================================================



////////////////////////////////////////////////////////////////////
// ��ñ�����IP��ַ
std::string CIOCPModel::GetLocalIP()
{
	// ��ñ���������
	char hostname[MAX_PATH] = {0};
	gethostname(hostname,MAX_PATH);                
	struct hostent FAR* lpHostEnt = gethostbyname(hostname);
	if(lpHostEnt == NULL)
	{
		return "127.0.0.1";
	}

	// ȡ��IP��ַ�б��еĵ�һ��Ϊ���ص�IP(��Ϊһ̨�������ܻ�󶨶��IP)
	LPSTR lpAddr = lpHostEnt->h_addr_list[0];      

	// ��IP��ַת�����ַ�����ʽ
	struct in_addr inAddr;
	memmove(&inAddr,lpAddr,4);
	m_strIP = std::string( inet_ntoa(inAddr) );        
	//std::string	s	=	std::string( inet_ntoa(inAddr) );
	return m_strIP;
}

///////////////////////////////////////////////////////////////////
// ��ñ����д�����������
int CIOCPModel::_GetNoOfProcessors()
{
	SYSTEM_INFO si;

	GetSystemInfo(&si);

	return si.dwNumberOfProcessors;
}

/////////////////////////////////////////////////////////////////////
// ������������ʾ��ʾ��Ϣ
//void CIOCPModel::_ShowMessage(const CString szFormat,...) const
//{
//	// ���ݴ���Ĳ�����ʽ���ַ���
//	CString   strMessage;
//	va_list   arglist;
//
//	// ����䳤����
//	va_start(arglist, szFormat);
//	strMessage.FormatV(szFormat,arglist);
//	va_end(arglist);
//
//	// ������������ʾ
//	//CMainDlg* pMain = (CMainDlg*)m_pMain;
//	//if( m_pMain!=NULL )
//	//{
//	//	pMain->AddInformation(strMessage);
//		TRACE( strMessage+_T("\n") );
//	//}	
//}

/////////////////////////////////////////////////////////////////////
// �жϿͻ���Socket�Ƿ��Ѿ��Ͽ���������һ����Ч��Socket��Ͷ��WSARecv����������쳣
// ʹ�õķ����ǳ��������socket�������ݣ��ж����socket���õķ���ֵ
// ��Ϊ����ͻ��������쳣�Ͽ�(����ͻ��˱������߰ε����ߵ�)��ʱ�򣬷����������޷��յ��ͻ��˶Ͽ���֪ͨ��

bool CIOCPModel::_IsSocketAlive(SOCKET s)
{
	int nByteSent=send(s,"",0,0);
	if (-1 == nByteSent) return false;
	return true;
}

///////////////////////////////////////////////////////////////////
// ��ʾ��������ɶ˿��ϵĴ���
bool CIOCPModel::HandleError( PER_SOCKET_CONTEXT *pContext,const DWORD& dwErr )
{
	// ����ǳ�ʱ�ˣ����ټ����Ȱ�  
	if(WAIT_TIMEOUT == dwErr)  
	{  	
		// ȷ�Ͽͻ����Ƿ񻹻���...
		if( !_IsSocketAlive( pContext->m_Socket) )
		{
			TRACE( _T("��⵽�ͻ����쳣�˳���\n") );
			this->_RemoveContext( pContext );
			return true;
		}
		else
		{
			TRACE( _T("���������ʱ��������...\n") );
			return true;
		}
	}  

	// �����ǿͻ����쳣�˳���
	else if( ERROR_NETNAME_DELETED==dwErr )
	{
		//TRACE( _T("��⵽�ͻ����쳣�˳���") );
		this->_RemoveContext( pContext );
		return true;
	}

	else
	{
		TRACE( _T("��ɶ˿ڲ������ִ��󡣴�����룺%d\n"),dwErr );
		return true;
	}
}




