#include "WinSock2.h"
#include "AirCommonNetServer.h"


namespace Air{
	
	namespace	Common{
	
		AString	NetServer::ProductTypeName="NetServer";
		NetServer::NetServer( CAString& strName,Info* pInfo )
			:IProduct(strName){
			if(pInfo!=NULL){
				m_Info		=	*pInfo;
			}
	
			m_pListener	=	m_Info.pListener;
		}
	
		U1 NetServer::Create(){
	
			//����SOCKET
			if(!CreateSocket())
				return	false;
	
			U16	PORT	=	(m_Info.usPort);
	
			// ��socket��һ�����ص�ַ 
			sockaddr_in sin; 
			sin.sin_family = AF_INET; 
			sin.sin_port = htons(PORT); 
			sin.sin_addr.S_un.S_addr = INADDR_ANY; 
			if (::bind(m_Socket, (LPSOCKADDR)&sin, sizeof(sockaddr_in)) == SOCKET_ERROR) 
			{ 
				OutputDebugStringA("��ʧ��\n");
				return	false; 
			}
	
			// ����socket�������״̬ 
			if (::listen(m_Socket, 10) == SOCKET_ERROR) 
			{ 
				OutputDebugStringA("����ʧ��\n"); 
				return	false; 
			} 
	
			//���������߳�
			m_ThreadListen.Start(m_Socket,this);
			//���������߳�
			m_ThreadSend.Start(this);
	
	
	
			return	true;
		}
	
		U1 NetServer::OnConnected(U32	socket,CAString&	strIP,CAString&	strPort){
			//�ж�SOCKET ID�Ƿ���Ч
			if(socket!=NULL){
				
	
				//�½�һ�������߳�
				NetReceiveThread*	pThread	=	NULL;
				m_ReceiveCS.Enter();
	
				if(m_lstUnUsedThread.empty()){
					m_ReceiveCS.Leave();
	
					pThread	=	new	NetReceiveThread;
				}else{
					ReceiveThreadList::iterator	i	=	m_lstUnUsedThread.begin();
					pThread	=	(NetReceiveThread*)(*i);
					m_lstUnUsedThread.erase(i);
					m_ReceiveCS.Leave();
				}
				//�����б�
				m_mapReceiveThread[socket]	=	pThread;
	
				if(pThread->IsRunning()){
					pThread->StopThreadWaitForExit();
				}
				//�����߳�
				pThread->Start(socket,this);
			}
			return	NetConnect::OnConnected(socket,strIP,strPort);
		}
	
		U1 NetServer::OnClose( U32 uiSocket ){
			if(uiSocket!=NULL){
				//�ر�SOCKET
				closesocket(uiSocket);
				//����
				m_ReceiveCS.Enter();
				ReceiveThreadMap::iterator	i	=	m_mapReceiveThread.find(uiSocket);
				if(i!=m_mapReceiveThread.end()){
					NetReceiveThread*	pThread	=	i->second;
					m_mapReceiveThread.erase(i);
	
					if(pThread!=NULL){
						pThread->StopThread();
						//����δʹ���б���
						m_lstUnUsedThread.push_back(pThread);
					}
				}
				m_ReceiveCS.Leave();
			}
			return	NetConnect::OnClose(uiSocket);
		}
	
		U1 NetServer::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize ){
			if(	m_Socket==	NULL	||
				pData	==	NULL	||
				uiSize	==	0)
			{
				return	false;
			}
			return	NetConnect::OnReceive(uiSocket,pData,uiSize);
		}
	
		U1 NetServer::Destroy(){
	
			//�ر�SOCKET
			DestroySocket();
	
			//�ر�SOCKET ֹͣ�����߳� ������ܰ�ȫ�˳�
			if(!m_ThreadListen.StopThreadWaitForExit()){
	
			}
			//ֹͣ�����߳�
			if(!m_ThreadSend.StopThreadWaitForExit()){
			}
	
	
			m_ReceiveCS.Enter();
	
			std::list<U32>					lstSocket;
			std::list<NetReceiveThread*>	lstThread;
			
			//��ȡ���н����̵߳�ID �� �߳�ָ��
			ReceiveThreadMap::iterator	i	=	m_mapReceiveThread.begin();
			for(;i!=m_mapReceiveThread.end();i++){
				lstSocket.push_back(i->first);
				lstThread.push_back(i->second);
			}
			m_ReceiveCS.Leave();
			
			//�ر�SOCKET
			std::list<U32>::iterator	ii	=	lstSocket.begin();
			for(;ii!=lstSocket.end();ii++){
				U32	uiSocket	=	(U32)(*ii);
				//�ر�Socket	�����ʹ�����߳��Զ��˳�
				closesocket(uiSocket);
			}
	
			//�ȴ������̹߳ر�
			std::list<NetReceiveThread*>::iterator	it	=	lstThread.begin();
			for(;it!=lstThread.end();it++){
				NetReceiveThread*	p	=	(NetReceiveThread*)(*it);
				while(p->IsRunning()){
					p->StopThreadWaitForExit();
				}
			}
	
			m_ReceiveCS.Enter();
			//���δʹ�õ��߳�
			ReceiveThreadList::iterator	itr	=	m_lstUnUsedThread.begin();
			for(;itr!=m_lstUnUsedThread.end();itr++){
				NetReceiveThread*	p	=	(NetReceiveThread*)(*itr);
				if(p!=NULL){
					if(p->IsRunning()){
						p->StopThreadWaitForExit();
					}
				}
				SAFE_DELETE(p);
			}
			m_lstUnUsedThread.clear();
			m_ReceiveCS.Leave();
	
	
			return	true;
		}
	
		U1 NetServer::SendAll( const void* pData,U32 uiSize ){
			
			
			//�����н����߳� ����ͬһ����
			ReceiveThreadMap::iterator	i	=	m_mapReceiveThread.begin();
			for(;i!=m_mapReceiveThread.end();i++){
				NetPack*	p	=	new	NetPack(i->first,uiSize,(AChar*)pData);
				m_ThreadSend.Push(p);
				
			}
			return	true;
		}
	
		U1 NetServer::Send( U32 uiSocket,const void* pData,U32 uiSize ){
			ReceiveThreadMap::iterator	i	=	m_mapReceiveThread.find(uiSocket);
			if(i!=m_mapReceiveThread.end()){
				NetPack*	p	=	new	NetPack(uiSocket,uiSize,(AChar*)pData);
				m_ThreadSend.Push(p);
			}
			return	true;
		}
	}
};
