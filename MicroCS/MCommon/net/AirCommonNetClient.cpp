#include "WinSock2.h"
#include "AirCommonNetClient.h"


namespace Air{
	
	namespace	Common{
	
		AString	NetClient::ProductTypeName="NetClient";
		NetClient::NetClient( CAString& strName,Info* pInfo )
			:IProduct(strName){
			if(pInfo!=NULL)
				m_Info	=	*pInfo;
			m_pListener	=	m_Info.pListener;
		}
	
		U1 NetClient::Create(){
			return	true;
		}
	
		U1 NetClient::Destroy(){
			if(IsConnected())
				DisConnect();
			return	true;
		}
	
		U1 NetClient::OnConnected( U32 socket,CAString& strIP,CAString& strPort ){
			if(socket	==	NULL){
				return	false;
			}
			//���������߳�
			m_ThreadSend.Start(this);
			//���������߳�
			m_ThreadReceive.Start(socket,this);
	
			return	NetConnect::OnConnected(socket,strIP,strPort);
		}
	
		U1 NetClient::OnClose( U32 uiSocket ){
			//ֹͣ�����߳�
			m_ThreadSend.StopThreadWaitForExit();
			//�ݻ�SOCKET
			DestroySocket();
			//ֹͣ�����߳�
			m_ThreadReceive.StopThread();
	
			
			return	NetConnect::OnClose(uiSocket);
		}
	
		U1 NetClient::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize ){
			return	NetConnect::OnReceive(uiSocket,pData,uiSize);
		}
	
		U1 NetClient::IsConnected(){
			return	m_Socket!=NULL;
		}
	
		U1 NetClient::Connect( Info& info ){
			//����Ѿ�����	�Ͽ�ǰ�������
			if(IsConnected()){
				DisConnect();
			}
			m_Info	=	info;
	
			CreateSocket();
	
			U16	PORT	=	(info.usPort);
	
			sockaddr_in servAddr; 
			servAddr.sin_family = AF_INET; 
			servAddr.sin_port = htons(PORT); 
			servAddr.sin_addr.S_un.S_addr = ::inet_addr(info.strIP.c_str()); 
			if (INVALID_SOCKET == (::connect(m_Socket, (sockaddr*)&servAddr, sizeof(sockaddr_in)))) 
			{ 
				OutputDebugStringA("���ӷ�����ʧ��\n"); 
				DestroySocket();
				return	false;
			} 
			char strport[32];
			itoa(m_Info.usPort,strport,10);
			OnConnected(m_Socket,info.strIP,strport);
			
			return	true;
		}
	
		U1 NetClient::DisConnect(){
			//�жϵ�ǰ״̬
			if(!IsConnected())
				return	false;
			//ֹͣ�����߳�
			m_ThreadSend.StopThreadWaitForExit();
			//�ݻ�SOCKET	//�����̻߳��Զ��ر�
			DestroySocket();
	
			//�ȴ������̹߳ر�
			m_ThreadReceive.StopThreadWaitForExit();
			return	true;
		}
	}
};