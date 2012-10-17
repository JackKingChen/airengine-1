#ifndef MTRENDERTHREAD_HEAD_FILE
#define MTRENDERTHREAD_HEAD_FILE

#include "MTDoubleBuffer.h"
#include "MTThread.h"

enum enumRenderThreadState{
	enRTS_UNKNOWN,
	enRTS_Waiting,
	enRTS_Rendering,
	enRTS_RenderComplated,
	enRTS_EventResetComplated,
};

class	MT_RenderThread	:	
	public	MT_Thread,
	public	Singleton<MT_RenderThread>
{
public:
	MT_RenderThread(IDirect3DDevice9*	pDevice=NULL);
	virtual	~MT_RenderThread();
	//����
	void			Swap();
	//ͬ�� ��Ҫ�������ݶ�ȡ
	void			Sync();
	//�̺߳���
	virtual bool	RepetitionRun();
	//��ȡ˫Buffer
	MT_DoubleBuffer&	GetDBuffer(){
		return	m_DBuffer;
	};
	enumRenderThreadState	GetRenderThreadState(){
		return	m_State;
	}

	virtual bool StopThread();

	void			SetDevice(IDirect3DDevice9* pDevice){
		m_pDevice	=	pDevice;
	};
	void			SetDeviceLost(bool	bDeviceLost){
		m_bDeviceLost	=	bDeviceLost;
	};
	void			WaitRenderComplated();
	//���߳� Present��ʱ����� �������߳�ִ��������Ⱦָ��
	void			DebugRenderThread();
	//
	void			ReleaseAllObject();

	MT_IDirect3DVertexDeclaration9*	CreateVD(CONST D3DVERTEXELEMENT9*	pVertexElements);
protected:
	void			RenderFrame();
	void			DebugFrame(U8*	pBuffer,U8* pEnd);

	void			ReleaseRenderObject();
	void			ReleaseObject(ReleaseObj& obj);

protected:
	IDirect3DDevice9*		m_pDevice;
	Event					m_evtRenderWaitMain;
	Event					m_evtMainWaitRender;
	MT_DoubleBuffer			m_DBuffer;
	enumRenderThreadState	m_State;
	bool					m_bDeviceLost;
	std::vector<MT_IDirect3DVertexDeclaration9*>	m_vecVD;
};

void	Hook_IDirect3DDevice9(IDirect3DDevice9* pDevice);
void	UnHook_IDirect3DDevice9();

#endif