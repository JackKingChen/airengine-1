#include "WinSock2.h"
#include "AirCommonNetConnect.h"
namespace Air{
	
	namespace	Common{
	
	
		NetConnect::NetConnect(){
			m_Socket	=	NULL;
			m_pListener	=	NULL;
			
		}
	
		NetConnect::~NetConnect(){
			m_Socket	=	NULL;
		}
	
		U1 NetConnect::Send( void* pData,U32 uiSize ){
			if(	pData	==	NULL	||
				uiSize	==	0)
			{
				return	false;
			}
	
			NetPack*	p	=	new	NetPack(m_Socket,uiSize,(AChar*)pData);
			//���뷢���б�
			m_ThreadSend.Push(p);
	
			return	true;
		}
	
		U1 NetConnect::OnClose( U32 uiSocket ){
	
			if(m_pListener!=NULL)
				m_pListener->OnClose(uiSocket);
			return	true;
		}
	
		U1 NetConnect::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize ){
			if(m_pListener!=NULL)
				m_pListener->OnReceive(uiSocket,pData,uiSize);
			return	true;
		}
	
		U1 NetConnect::CreateSocket(){
			if(m_Socket==NULL)
				m_Socket	= ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
			if(	m_Socket	==	NULL	||
				m_Socket	==	INVALID_SOCKET)
			{
				m_Socket	=	NULL;
				return	false;
			}
	
			//ϵͳ�ṩ��socket��������СΪ8K������Խ�֮����Ϊ64K�������ڴ���ʵʱ��Ƶʱ�� 
	
			//���÷��ͺͽ��ջ����� 
			int rcvbuf; 
			int rcvbufsize=sizeof(int); 
	
			if(getsockopt(m_Socket,SOL_SOCKET,SO_RCVBUF,(char*) 
				&rcvbuf,&rcvbufsize)!=SOCKET_ERROR) 
			{ 
				if(rcvbuf<65536) 
					rcvbuf=65536; 
				setsockopt(m_Socket,SOL_SOCKET,SO_RCVBUF,(char*) 
					&rcvbuf,rcvbufsize); 
			} 
	
			if(getsockopt(m_Socket,SOL_SOCKET,SO_SNDBUF,(char*) 
				&rcvbuf,&rcvbufsize)!=SOCKET_ERROR) 
			{ 
				if(rcvbuf<65536) 
					rcvbuf=65536; 
				setsockopt(m_Socket,SOL_SOCKET,SO_SNDBUF,(char*) 
					&rcvbuf,rcvbufsize); 
			}   
	
	
			return	true;
		}
	
		U1 NetConnect::DestroySocket(){
			if(m_Socket!=NULL){
				closesocket(m_Socket);
				m_Socket	=	NULL;
			}
			return	true;
		}
	
		U1 NetConnect::OnConnected( U32 socket,CAString& strIP,CAString& strPort ){
			if(m_pListener!=NULL)
				m_pListener->OnConnected(socket,strIP,strPort);
			return	true;
		}

		U32 NetConnect::GetSocket()
		{
			return	m_Socket;
		}

	}
};