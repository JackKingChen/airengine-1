#ifndef RENDERSYSTEM_HEAD_FILE
#define RENDERSYSTEM_HEAD_FILE

#include "AirRenderHeader11.h"
#include "AirRenderStateManager11.h"

namespace Air{
	
	
	
	namespace Client{
		class ISceneNode;
	
		namespace	Render{
			class System	:	
				public	ISystem,
				public	StateManager{
			public:
				System();
				virtual ~System();
	
				/**	\brief	��ʼ��
				*   
				*	@remarks 	��ʼ��
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization();
	
				/**	\brief	��ʼ
				*   
				*	@remarks 	��ʼ
				*	@see		System
				*	@return   	bool
				*	@note
				*
				**/
				virtual bool Start();
	
	
				/**	\brief	ֹͣ��Ⱦ
				*   
				*	@remarks 	ֹͣ��Ⱦ
				*	@see		System
				*	@return   	bool
				*	@note
				*
				**/
				virtual	bool Stop();
	
				/**	\brief	�ͷ�
				*   
				*	@remarks 	�ͷ�
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release();
				/**	\brief	�����豸
				*   
				*	@remarks 	�����豸
				*	@see		IEngine
				*	@return   	long
				*	@param		void * pd3dDevice
				*	@param		const void * pBackBufferSurfaceDesc
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual void		OnD3DResetDevice(	void* pd3dDevice, const void* pBackBufferSurfaceDesc,void* pUserContext,void*	pSwapChain	= NULL );
				/**	\brief	�豸��ʧ
				*   
				*	@remarks 	�豸��ʧ
				*	@see		IEngine
				*	@return   	void
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual void		OnD3DLostDevice(	void* pUserContext );	
				/**	\brief	����ΪInstance�������㻺��
				*   
				*	@remarks 	����ΪInstance�������㻺��
				*	@see		ISystem
				*	@return   	void
				*	@param		Vertex::IBuff * pBuff
				*	@param		Vertex::IBuff * pInstanceBuff
				*	@param		UInt uiInstanceCount
				*	@note
				*
				**/
				virtual	void		SetVertexInstance(Vertex::IBuff* pBuff,Vertex::IBuff* pInstanceBuff,UInt uiInstanceCount );
				/**	\brief	������Ļ���������ļ�
				*   
				*	@remarks 	������Ļ���������ļ�
				*	@see		System
				*	@return   	void
				*	@param		AString strName
				*	@note
				*
				**/
				virtual	U1		SaveScreenToFile(CAString&	strName);
				/**	\brief	����ȫ��״̬
				*   
				*	@remarks 	����ȫ��״̬
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		SetFullScreen();
				/**	\brief	���±���
				*   
				*	@remarks 	���±���
				*	@see		ISystem
				*	@return   	U1
				*	@param		ITexture * pSrcTexture
				*	@param		RECT * rect
				*	@param		ITexture * pDstTexture
				*	@param		POINT & p
				*	@note
				*
				**/
				virtual	U1			UpdataSurface(ITexture*	pSrcTexture,RECT*	rect,ITexture*	pDstTexture,POINT& p);
	
				/**	\brief	������Ҫ��д��ѭ�����ú���
				*   
				*	@remarks 	�߳������ִ�к���
				*	@see		Thread
				*	@return   	bool
				*	@note
				*
				**/
				virtual bool RepetitionRun();
				/**	\brief	���ڳߴ�仯
				*   
				*	@remarks 	���ڳߴ�仯
				*	@see		ISystem
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			ChangeSize();
				/**	\brief	�Ƿ���Ҫ����
				*   
				*	@remarks 	�Ƿ���Ҫ����
				*	@see		ISystem
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			IsNeedReset();
	
				/**	\brief	�����豸
				*   
				*	@remarks 	�����豸
				*	@see		ISystem
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			Reset();
	
				/**	\brief	��RenderDevice����
				*   
				*	@remarks 	�豸��ʧ��ʱ��  ��Ҫ�����߳�ִ���豸����
				*	@see		System
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		SetNeedReset();

				//IDirect3D9*			GetD3D();
				
				/**	\brief	���ö�������
				*   
				*	@remarks 	���ö�������
				*	@see		IDirectXCallback
				*	@return   	U1
				*	@param		Vertex::IBuff * pBuff
				*	@note
				*
				**/
				virtual U1		SetVertexDeclare(VertexDeclare*	pDeclare);
				/**	\brief	���ö��㻺��
				*   
				*	@remarks 	���ö��㻺��
				*	@see		IDirectXCallback
				*	@return   	U1
				*	@param		Vertex::IDeclare * pDeclare
				*	@note
				*
				**/
				virtual U1		SetVertexBuffer(VertexBuffer*	pBuffer);
				/**	\brief	������������
				*   
				*	@remarks 	������������
				*	@see		IDirectXCallback
				*	@return   	U1
				*	@param		Index::IBuffer * pBuffer
				*	@note
				*
				**/
				virtual U1		SetIndexBuffer(IndexBuffer*		pBuffer);

				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		ISystem
				*	@return   	U1
				*	@param		enumShaderType type
				*	@param		U32 uiRegister
				*	@param		ITexture * pTexture
				*	@note
				*
				**/
				virtual	U1		SetTexture(enumShaderType	type,U32	uiRegister,ITexture*	pTexture);
				/**	\brief	����shader
				*   
				*	@remarks 	����shader
				*	@see		ISystem
				*	@return   	U1
				*	@param		Render::enumShaderType	type
				*	@param		IShader * pShader
				*	@note
				*
				**/
				virtual	U1		SetShader(Render::enumShaderType	type,IShader*	pShader);
				/**	\brief	���ù�դ��״̬
				*   
				*	@remarks 	���ù�դ��״̬
				*	@see		ISystem
				*	@return   	U1
				*	@param		IRasterizerState * pState
				*	@note
				*
				**/
				virtual	U1		SetRasterizerState(IRasterizerState*	pState);
				/**	\brief	�������ģ��״̬
				*   
				*	@remarks 	�������ģ��״̬
				*	@see		ISystem
				*	@return   	U1
				*	@param		IDepthStencilState * pState
				*	@note
				*
				**/
				virtual	U1		SetDepthStencilState(IDepthStencilState*	pState);
				/**	\brief	���û��״̬
				*   
				*	@remarks 	���û��״̬
				*	@see		ISystem
				*	@return   	U1
				*	@param		IBlendState * pState
				*	@note
				*
				**/
				virtual	U1		SetBlendState(IBlendState*	pState);
				virtual	U1		DrawOpt(const DrawOption&	opt);

				virtual	U1		SetConstantBuffer(enumShaderType	type,IConstantBuffer*	pBuffer);
				virtual	U1		SetConstantBuffer(IConstantBuffer*	pBuffer);
			private:
				ISceneNode*			m_pSceneNode;
	
				U1					m_bNeedReset;
				//IDirect3D9*			m_pD3D;
			};
		};
	};
};
#endif // RENDERSYSTEM_HEAD_FILE