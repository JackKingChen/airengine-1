#ifndef AirCascadedShadowMap_h__
#define AirCascadedShadowMap_h__


#include "AirRenderSystem.h"

namespace	Air{
	namespace	Engine{
		class QuadRenderable;
		class	CascadedShadowMap	:	public	MemoryObject{
		public:
			CascadedShadowMap();

			~CascadedShadowMap();

			U1		Init(Camera* pMainCamera,U32	uiSplite	=	4);
			U1		Release();
			U1		UpdateCamera(Camera* pMainCamera);
			U1		UpdateTarget(RenderTarget* pLighting);
		protected:
			void	BlurRenderTarget(RenderTarget* pDst,RenderTarget* pSrc);
		protected:
			Camera*						m_pMainCamera;
			RenderTarget*				m_pShadowDepth;
			RenderTarget*				m_pShadowDepthTemp;

			Material*					m_pMaskMaterial;
			Material*					m_pBlurX;
			Material*					m_pBlurY;
			STD_VECTOR<Camera*>			m_vecCSMCamera;
			Float3						m_vLightDirection;
			QuadRenderable*				m_pQuad;
		};
	}
}

#endif // AirCascadedShadowMap_h__