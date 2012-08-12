#ifndef RENDERDEVICE_HEAD_FILE
#define RENDERDEVICE_HEAD_FILE

#include "AirRenderHeader9.h"
namespace Air{
	
	namespace Client{
	
		namespace	Render{
			/**	\brief	��Ϣ�ص�
			*   
			*	@remarks 	��Ϣ�ص�
			*	@see		
			*	@return   	LRESULT CALLBACK
			*	@param		HWND hwnd
			*	@param		UINT msg
			*	@param		WPARAM wParam
			*	@param		LPARAM lParam
			*	@note
			*
			**/
			LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			/**	\brief	DX9�豸��
			*
			*	DX9�豸��
			*
			***/
			class	Device9{
			public:
				/**	\brief	�豸������Ϣ
				*
				*	�豸������Ϣ
				*
				***/
				typedef		DisplayParam	Info;
	
				typedef	std::vector<UInt>			MsaaQualityVector;
				typedef	std::vector<D3DDISPLAYMODE>	DisplayModeVector;
				struct	Adapter{
					D3DADAPTER_IDENTIFIER9	identifier;
					HMONITOR				monitor;
					D3DDISPLAYMODE			displayMode;
					MsaaQualityVector		vecMSAAWindow;
					MsaaQualityVector		vecMSAAFull;
					D3DCAPS9				caps;
					DisplayModeVector		vecDisplayMode;
				};
	
	
				typedef	std::vector<Adapter>	AdapterVector;
			public:
				Device9(Info*	pInfo);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
				/**	\brief	�豸��ʧ
				*   
				*	@remarks 	�豸��ʧ
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Lost();
				/**	\brief	�����豸
				*   
				*	@remarks 	�����豸
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Reset();
	
				/**	\brief	��Ⱦһ֡
				*   
				*	@remarks 	��Ⱦһ֡
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	RenderOneFrame();
				/**	\brief	��ȾĿ��
				*   
				*	@remarks 	��ȾĿ��
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	RenderTarget();
				/**	\brief	��Ⱦ���ս��
				*   
				*	@remarks 	��Ⱦ���ս��
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	RenderFinal();
				/**	\brief	�����ͼ
				*   
				*	@remarks 	�����ͼ
				*	@see		Device9
				*	@return   	U1
				*	@param		AString & strName
				*	@note
				*
				**/
				U1	SetNeedSaveScreen(CAString&	strName);
				/**	\brief	����ȫ��
				*   
				*	@remarks 	����ȫ��
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	SetNeedFullScreen();
				/**	\brief	����Ƿ���Ҫ�����豸
				*   
				*	@remarks 	����Ƿ���Ҫ�����豸
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	CheckChange();
	
				/**	\brief	ȫ��
				*   
				*	@remarks 	ȫ��
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	FullScreen();
				/**	\brief	���ĳߴ�
				*   
				*	@remarks 	���ĳߴ�
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	ChangeSize();
				/**	\brief	������Ļ
				*   
				*	@remarks 	������Ļ
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	SaveScreen();
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	CreateWin();
				/**	\brief	�ݻٴ���
				*   
				*	@remarks 	�ݻٴ���
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	DestroyWin();
	
				/**	\brief	����D3D
				*   
				*	@remarks 	����D3D
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	CreateD3D();
				/**	\brief	�����豸
				*   
				*	@remarks 	�����豸
				*	@see		Device9
				*	@return   	U1
				*	@param		UInt uiAdapter
				*	@note
				*
				**/
				U1	CreateDevice(UInt uiAdapter);
				/**	\brief	�ݻ��豸
				*   
				*	@remarks 	�ݻ��豸
				*	@see		Device
				*	@return   	U1
				*	@note
				*
				**/
				U1	DestroyDevice();
	
				/**	\brief	��ʼ���豸״̬
				*   
				*	@remarks 	��ʼ���豸״̬
				*	@see		Device9
				*	@return   	void
				*	@note
				*
				**/
				void	InitDeviceState();
	
				/**	\brief	����Ϊ�豸��ʶ��Ⱦ״̬
				*   
				*	@remarks 	����Ϊ�豸��ʶ��Ⱦ״̬
				*	@see		Device9
				*	@return   	void
				*	@note
				*
				**/
				inline	void	SetDefaultDeviceState(){
					//m_pDefaultState->Apply();
				};
	
	
				D3DPRESENT_PARAMETERS	m_DeviceParam;				///<	�豸��������
				Info					m_Info;						///<	������Ϣ
				AdapterVector			m_vecAdapter;				///<	�������б�
				IDirect3D9*				m_pD3D;
				IDirect3DDevice9*		m_pDevice;					///<	DX9�豸
				IDirect3DStateBlock9*	m_pDefaultState;			///<	Ĭ����Ⱦ״̬
	
				U1						m_bPause;					///<	�Ƿ���Ҫ��ͣ
	
	
				AString					m_strSaveScreenFileName;	///<	�����ļ���
				U1						m_bNeedFullScreen;			///<	�Ƿ���Ҫȫ���л�
			};
		}
	};
};
#endif // RENDERDEVICE_HEAD_FILE