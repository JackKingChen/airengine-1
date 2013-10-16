#include "WinSock2.h"
#include "AirCommonNetSendThread.h"
//#include "AirRandom.h"
namespace Air{
	
	
	
	namespace	Common{
	
	
		NetSendThread::NetSendThread(){
			m_pListener	=	NULL;
			m_bWaiting	=	false;
		}
	
		NetSendThread::~NetSendThread(){
	
		}
	
		U1 NetSendThread::Push( NetPack* pack ){
			//�ж����ݰ�����Ч��
			if(	pack==NULL	||
				!pack->IsValid()){
				return	false;
			}
	
			//�����б�
			m_CS.Enter();
			//�����ǲ�ѯ���˵����� �õ��Ľ�� ��Ҫ������뷽ʽ	���¼Ǻ� infernalhell 20110229
			//���NetPack����������������� ԭ��û�в���
			m_lstSendPack.push(pack);
			m_CS.Leave();
	
			if(m_bWaiting){
				m_SendEvent.Reset();
			}
			return	true;
		}
	
		U1 NetSendThread::RepetitionRun(){
			NetPack*	p	=	NULL;
	
			m_CS.Enter();
			if(!m_lstSendPack.empty()){
				p	=	m_lstSendPack.front();
				m_lstSendPack.pop();
			}
	
			m_CS.Leave();
	
			if(p==NULL){
				m_bWaiting	=	true;
				//�ȴ�1000ms
				m_SendEvent.Wait(1000);
				m_bWaiting	=	false;
			}else{
				if(p->IsValid()){
					int	iRet	=	send(p->uiSocket,p->pData,p->uiSize,0);
					if(iRet	<=	0){
						//����ʧ��
						if(m_pListener!=NULL)
							m_pListener->OnClose(p->uiSocket);
					}else{
						OutputDebugStringA("���ͳɹ�\n");
					}
				}
				//ɾ������
				delete	p;
			}
						
	
			return	true;
		}
	
		U1 NetSendThread::Start(NetListener*	pListener){
			m_pListener	=	pListener;
			if(!IsRunning())
				StartThread();
			return	true;
		}
	}
};