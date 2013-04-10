#ifndef AirEnginePipeline_h__
#define AirEnginePipeline_h__

#include "AirRenderSystem.h"
#include "AirCascadedShadowMap.h"
#include "AirScreenSpaceTessellation.h"
#include "AirInterfaceInputSystem.h"
#include "AirPipelineOIT.h"
#include "AirPipelineVoxelGen.h"

namespace	Air{
	namespace	Engine{
		class QuadRenderable;
		class Material;
		class Light;


		class	FrameListener{
		public:
			virtual	U1	OnBeforeRenderFrame(const	FrameTime&	frame){return	true;};
			virtual	U1	OnAfterRenderFrame(const	FrameTime&	frame){return	true;};
		};

		class	ENGINE_EXPORT	Pipeline	:	
			public	TProduct<Pipeline>,
			public	OIS::MouseListener,
			public	OIS::KeyListener,
			public	Common::MutilListenerManager<FrameListener>
		{
		public:
			Pipeline(CAString&	strName);
			

			virtual	U1		Create();
			virtual	U1		Destroy();

			virtual	void	Update(const FrameTime& frameTime);
			virtual	U1		RenderOneFrame(const FrameTime& frameTime);


			//inline function
		public:
			inline	QuadRenderable*	GetQuadRenderable(){
				return	m_pQuad;
			}
			void			SetCurrentScene(Scene*	pCurrentScene);
				
			inline	Scene*			GetCurrentScene(){
				return	m_pScene;
			};
			inline	Camera*			GetMainCamera(){
				return m_pMainCamera;
			};
			inline	RenderWindow*	GetMainWindow(){
				return	m_pMainWindow;
			};
		protected:
			Scene*			m_pScene;
			QuadRenderable*	m_pQuad;
			RenderWindow*	m_pMainWindow;
			Camera*			m_pMainCamera;
		};
		class	ENGINE_EXPORT	DefaulePipeline	:	
			public	Pipeline
		{
		public:
			static	AString	ProductTypeName;
		public:
			DefaulePipeline(CAString&	strName);
			

			virtual	U1		Create();
			virtual	U1		Destroy();

			virtual	void	Update(const FrameTime& frameTime);
			virtual	U1		RenderOneFrame(const FrameTime& frameTime);



			virtual bool mouseMoved( const OIS::MouseEvent &arg );
			virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

			virtual bool keyPressed( const OIS::KeyEvent &arg );
			virtual bool keyReleased( const OIS::KeyEvent &arg );
		protected:
			void	BlurRenderTarget(RenderTarget* pDst,RenderTarget* pSrc);
		protected:
			
			RenderTarget*	m_pMRT;

			RenderTarget*	m_pRT_AO;
			RenderTarget*	m_pRT_SO;

			RenderTarget*	m_pRT_EnvSphere;
			RenderTarget*	m_pRT_EnvSAT;
			



			
			Material*		m_pQuadCopy;
			Material*		m_pSSAO;
			Material*		m_pSSSO;

			Material*		m_pCombine;
			Material*		m_pSky;
			Material*		m_pCubeToViewSphere;
			Material*		m_pViewSphereSAT;
			Material*		m_pAmbientLight;




			Float3			vMoveDirection;
			float			fVolocity;

			CascadedShadowMap		m_CSM;
			OIT						m_OIT;
			VoxelGenerator			m_VoxelGen;

			Render::CBFrame		m_cbFrame;
		};
	}
}
#endif // AirEnginePipeline_h__
