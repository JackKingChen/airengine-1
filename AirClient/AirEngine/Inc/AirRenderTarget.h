#ifndef INTERFACERENDERTARGET_HEAD_FILE
#define INTERFACERENDERTARGET_HEAD_FILE

#include "AirRenderTexture.h"
#include "AirEngineViewport.h"
namespace Air{
	
	namespace Engine{
	
		class	Camera;
		class	Scene;
		class	MovableObject;

	
		namespace	Render{
			enum	enumTargetClearFlag{
				enTCF_UNKNOWN,
				enTCF_STENCIL	=	1,
				enTCF_TARGET	=	2,
				enTCF_ZBUFFER	=	4,
				enTCF_MAX
			};
			typedef	enumTextureFormat		TFormat;
			typedef	std::vector<Texture*>	TextureVector;

			/**	\brief	��ȾĿ�������
			*
			*	��ȾĿ�������
			*
			***/
			class TargetListener{
			public:
				/**	\brief	��Ⱦǰ�ص�
				*   
				*	@remarks 	��Ⱦǰ�ص�
				*	@see		Listener
				*	@return   	void
				*	@note
				*
				**/
				virtual void	BeforeRender()	=	NULL;
				/**	\brief	��Ⱦ�лص�
				*   
				*	@remarks 	��Ⱦ�лص�
				*	@see		Listener
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnRender()		=	NULL;
				/**	\brief	��Ⱦ��ص�
				*   
				*	@remarks 	��Ⱦ��ص�
				*	@see		Listener
				*	@return   	void
				*	@note
				*
				**/
				virtual void	AfterRender()	=	NULL;
			};

			/**	\brief	��ȾĿ��ӿ�
			*
			*	��ȾĿ��ӿ�
			*
			***/
			class	ENGINE_EXPORT	Target	:
				public	IProduct,
				public	Common::MutilListenerManager<TargetListener>{
			public:
				/**	\brief	����ȾĿ��
				*
				*	����ȾĿ��
				*
				***/
				struct ENGINE_EXPORT	Info{
					std::vector<Texture::Info>		vecTextureInfo;	///<	����ȾĿ��
					TFormat							depthFormat;	///<	��ȸ�ʽ
					Target*							extraDepth;		///<	ʹ���ⲿ���	�����������
					Float4							clearColor;		///<	������ɫ
					U1								bUseDepth;		///<	�ж���ȾĿ���Ƿ���Ҫ���
					HWND							extraWnd;
					HWND							parentWnd;
					U1								bFullScreen;
					

					Info();

					/**	\brief	����Ϊ��һ��ȾĿ��
					*   
					*	@remarks 	����Ϊ��һ��ȾĿ��
					*	@see		Info
					*	@return   	void
					*	@param		UInt uiWidth
					*	@param		UInt uiHeight
					*	@param		TFormat fmt
					*	@param		U1 bDepth
					*	@param		Target * pExtraTarget
					*	@note
					*
					**/
					void	SetSingleTarget(	UInt		uiWidth,
												UInt		uiHeight,
												TFormat		fmt,	
												U1			bDepth	=	false,
												Target*	pExtraTarget	=	NULL);
					/**	\brief	����Ϊ����Ļ�������ȾĿ��
					*   
					*	@remarks 	����Ϊ����Ļ�������ȾĿ��
					*	@see		Info
					*	@return   	void
					*	@param		TFormat fmt
					*	@param		U1 bDepth
					*	@param		Target * pExtraTarget
					*	@note
					*
					**/
					void	SetSingleTargetScreen(	TFormat		fmt,
													float		fScale	=	1.0f,
													U1			bDepth	=	false,
													Target*	pExtraTarget	=	NULL);

					/**	\brief	����Ϊ����ȾĿ��
					*   
					*	@remarks 	����Ϊ����ȾĿ��
					*	@see		Info
					*	@return   	void
					*	@param		UInt uiWidth
					*	@param		UInt uiHeight
					*	@param		UInt uiNumTarget
					*	@param		TFormat * pFmtArray
					*	@param		U1 bDepth
					*	@param		Target * pExtraTarget
					*	@note
					*
					**/
					void	SetMutilTarget(	UInt		uiWidth,
											UInt		uiHeight,
											UInt		uiNumTarget,
											TFormat*	pFmtArray,
											U1			bDepth			=	false,
											Target*	pExtraTarget	=	NULL);

					/**	\brief	����Ϊ��Ļ����Ķ���ȾĿ��
					*   
					*	@remarks 	����Ϊ��Ļ����Ķ���ȾĿ��
					*	@see		Info
					*	@return   	void
					*	@param		UInt uiNumTarget
					*	@param		TFormat * pFmtArray
					*	@param		U1 bDepth
					*	@param		Target * pExtraTarget
					*	@note
					*
					**/
					void	SetMutilTargetScreen(	UInt		uiNumTarget,
													TFormat*	pFmtArray,
													float		fScale			=	1.0f,
													U1			bDepth			=	false,
													Target*	pExtraTarget	=	NULL);

					void	SetRenderWindow(U32		uiWidth,
											U32		uiHeight,
											U1		bWindow			=	true,
											HWND	parentWindow	=	NULL,
											HWND	extraWindow		=	NULL);
				};
			public:
				static AString ProductTypeName;
				Target(CAString&	strName,	Info*	pInfo);

				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1			Create();
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1			Destroy();
				/**	\brief	��ʼ��Ⱦ
				*   
				*	@remarks 	��ʼ��Ⱦ
				*	@see		Target
				*	@return   	U1
				*	@param		Scene*	pScene
				*	@note
				*
				**/
				virtual U1			Update();
				/**	\brief	����ǰ����
				*   
				*	@remarks 	��Ҫ������RT DEPTHSTENCIL BEGINSCENE֮��
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1			BeforeUpdate(U32	uiFace	=	0);
				/**	\brief	���½����Ĵ���
				*   
				*	@remarks 	���½����Ĵ��� EndScene֮��
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				virtual	U1			AfterUpdate(U1 bSwapBuffer	=	true);
				/**	\brief	���ñ�����ɫ
				*   
				*	@remarks 	���ñ�����ɫ
				*	@see		Target
				*	@return   	U1
				*	@param		Float4 uiColor
				*	@note
				*
				**/
				inline void		SetBKColor(const Float4&	color){
					m_Info.clearColor	=	color;
				};
	
				/**	\brief	������ȾĿ������
				*   
				*	@remarks 	������ȾĿ������
				*	@see		Target
				*	@return   	void
				*	@param		MovableObject * pObject
				*	@note
				*
				**/
				virtual	void		SetRenderObject(MovableObject*	pObject){};
	
				/**	\brief	��ȡ��ȾĿ������
				*   
				*	@remarks 	��ȡ��ȾĿ������
				*	@see		Target
				*	@return   	MovableObject*
				*	@note
				*
				**/
				virtual	MovableObject*	GetRenderObject(){return NULL;};
				/**	\brief	�ؽ�
				*   
				*	@remarks 	�ؽ�
				*	@see		Target
				*	@return   	void
				*	@param		Info & info
				*	@note
				*
				**/
				virtual	void		ReCreate(Info&	info)	=	NULL;
				/**	\brief	���Phase��Ϣ
				*   
				*	@remarks 	���Phase��Ϣ
				*	@see		Target
				*	@return   	void
				*	@param		enumPhaseIndex uiPhaseIndex
				*	@note
				*
				**/
				void				AddPhaseFlag(enumPhaseIndex	uiPhaseIndex);
				/**	\brief	�Ƴ�Phase��Ϣ
				*   
				*	@remarks 	�Ƴ�Phase��Ϣ
				*	@see		Target
				*	@return   	void
				*	@param		enumPhaseIndex uiPhaseIndex
				*	@note
				*
				**/
				void				RemovePhaseFlag(enumPhaseIndex	uiPhaseIndex);
				/**	\brief	��ȡPhase��Ϣ
				*   
				*	@remarks 	��ȡPhase��Ϣ
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				U32					GetPhaseFlag();
				/**	\brief	����Phase��Ϣ
				*   
				*	@remarks 	����Phase��Ϣ
				*	@see		Target
				*	@return   	void
				*	@note
				*
				**/
				void				ClearPhaseFlag();
				/**	\brief	��ȡ������
				*   
				*	@remarks 	��ȡ������
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				virtual	U32					GetWidth();
				/**	\brief	��ȡ����߶�
				*   
				*	@remarks 	��ȡ����߶�
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				virtual	U32					GetHeight();
				/**	\brief	��ȡ�������
				*   
				*	@remarks 	��ȡ�������
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				virtual	U32					GetDepth();

				/**	\brief	���ü���״̬
				*   
				*	@remarks 	���ü���״̬
				*	@see		Target
				*	@return   	void
				*	@param		U1 bActive
				*	@note
				*
				**/
				void				SetActive(U1	bActive);
				/**	\brief	�жϵ�ǰ�ӿڼ���
				*   
				*	@remarks 	���û�м��� �򲻻�����Ⱦ�����и��´�RT
				*	@see		Target
				*	@return   	Air::U1
				*	@note
				*
				**/
				U1					IsAvtive();

				/**	\brief	����ӿ�
				*   
				*	@remarks 	����ӿ�
				*	@see		Target
				*	@return   	Viewport*
				*	@param		Camera * pCamera
				*	@param		U32 uiZOrder
				*	@param		Real x
				*	@param		Real y
				*	@param		Real w
				*	@param		Real h
				*	@note
				*
				**/
				Viewport*			AddCamera(	Camera*	pCamera,
												U32		uiZOrder	=	0,
												Real	x			=	0.0f,
												Real	y			=	0.0f,
												Real	w			=	1.0f,
												Real	h			=	1.0f);
				/**	\brief	�Ƴ��ӿ�
				*   
				*	@remarks 	�Ƴ��ӿ�
				*	@see		Target
				*	@return   	void
				*	@param		U32 uiZOrder
				*	@note
				*
				**/
				void				RemoveViewport(U32		uiZOrder);
				/**	\brief	����ӿ�
				*   
				*	@remarks 	����ӿ�
				*	@see		Target
				*	@return   	void
				*	@param		Viewport * pVP
				*	@param		U32 uiZOrder
				*	@note
				*
				**/
				void				AddViewport(Viewport*	pVP,
												U32		uiZOrder	=	0);
				/**	\brief	�Ƴ������ӿ�
				*   
				*	@remarks 	�Ƴ������ӿ�
				*	@see		Target
				*	@return   	void
				*	@note
				*
				**/
				void				RemoveAllViewport();
				/**	\brief	����ʹ���ⲿ���
				*   
				*	@remarks 	����ʹ���ⲿ���
				*	@see		Target
				*	@return   	void
				*	@param		Target * pTarget
				*	@note
				*
				**/
				void				SetUseExtraDepth(Target*	pTarget);

				/**	\brief	���һ�������ʾ
				*   
				*	@remarks 	���һ�������ʾ
				*	@see		Target
				*	@return   	void
				*	@param		enumTargetClearFlag flag
				*	@note
				*
				**/
				void				AddClearFlag(enumTargetClearFlag	flag);
				/**	\brief	�Ƴ�һ�������ʾ
				*   
				*	@remarks 	�Ƴ�һ�������ʾ
				*	@see		Target
				*	@return   	void
				*	@param		enumTargetClearFlag flag
				*	@note
				*
				**/
				void				RemoveClearFlag(enumTargetClearFlag	flag);
				/**	\brief	���������ʾ
				*   
				*	@remarks 	���������ʾ
				*	@see		Target
				*	@return   	void
				*	@param		U32 flag
				*	@note
				*
				**/
				void				SetClearFlag(U32	flag);
				/**	\brief	���������ʾ
				*   
				*	@remarks 	���������ʾ
				*	@see		Target
				*	@return   	void
				*	@param		U1 bClearStencil
				*	@param		U1 bClearTarget
				*	@param		U1 bClearZBuffer
				*	@note
				*
				**/
				void				SetClearFlag(U1	bClearStencil,U1 bClearTarget,U1 bClearZBuffer);
				/**	\brief	��ȡ�����ʾ
				*   
				*	@remarks 	��ȡ�����ʾ
				*	@see		Target
				*	@return   	Air::U32
				*	@note
				*
				**/
				U32					GetClearFlag();


				void	FindActiveCamera( CameraSet& setCamera );

				virtual		void*	GetRTV(U32	uiIdx	=	0);
				virtual		void*	GetSRV(U32	uiIdx	=	0);
				virtual		void*	GetUAV(U32	uiIdx	=	0);
				virtual		void*	GetDepthRTV()				=	NULL;
				virtual		void*	GetDepthSRV()				=	NULL;
				virtual		void*	GetBackBuffer(U32	uiIdx	=	0);
				virtual		void*	GetDepthBuffer()			=	NULL;

				virtual		void	ReSize(U32	width,U32	height);

				virtual		void	OnMainWindowSize(Window* pMainWindow);
			protected:
				Info				m_Info;						///<	������Ϣ
				TextureVector		m_vecTexture;				///<	��������
				Camera*				m_pCamera;					///<	�󶨵������
				U1					m_bActive;					///<	�Ƿ񼤻�
				PhaseOption			m_PhaseOpt;					///<	�׶�����
				U32					m_ClearFlag;				///<	��������
				ViewportMap			m_mapViewport;				///<	�ӿ��б�

			};
	
			typedef		std::list<Target*>		TargetList;
			typedef		TargetList::iterator	TargetListItr;
			/**	\brief	��ȾĿ�������
			*
			*	��ȾĿ�������
			*
			***/
			class	TargetManager{
			public:
				/**	\brief	����һ��Ҫ��Ⱦ��Ŀ��
				*   
				*	@remarks 	����һ��Ҫ��Ⱦ��Ŀ��
				*	@see		Renderer
				*	@return   	void
				*	@param		Window::IControl * pControl
				*	@note
				*
				**/
				virtual	void	AddTarget(Render::Target*	pTarget){
					if(pTarget==NULL)
						return;
					m_lstTarget.push_back(pTarget);
				};
				/**	\brief	�Ƴ�һ����ȾĿ��
				*   
				*	@remarks 	�Ƴ�һ����ȾĿ��
				*	@see		Renderer
				*	@return   	void
				*	@param		Render::Target * pTarget
				*	@note
				*
				**/
				virtual	void	RemoveTarget(Render::Target*	pTarget){
					if(pTarget==NULL)
						return;
					m_lstTarget.remove(pTarget);
				};
				/**	\brief	��ȾĿ��
				*   
				*	@remarks 	��ȾĿ��
				*	@see		Renderer
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	RenderTarget(){
					class RenderTargetCall: std::unary_function<Target*, void>
					{
					public:
						result_type operator()(argument_type i){
							i->Update();
						}
					};
					std::for_each(m_lstTarget.begin(),m_lstTarget.end(),RenderTargetCall());

				};
	
				TargetList			m_lstTarget;
			};
		}
	};
};
#endif // INTERFACERENDERTARGET_HEAD_FILE