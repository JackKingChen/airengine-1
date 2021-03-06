#include "AirRenderDevice.h"
#include "AirEngineRenderable.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{


			void Device::SetVD( VertexDeclare* pDeclare )
			{

			}

			void Device::SetVB( U32 uiIndex,Buffer* pBuffer )
			{

			}

			void Device::SetIB( Buffer* pBuffer )
			{

			}

			void Device::SetCB( U32 uiIndex,Buffer* pBuffer )
			{

			}

			void Device::SetCB( enumShaderType type,U32 uiIndex,Buffer* pBuffer )
			{

			}

			void Device::SetShader( enumShaderType type,Shader* pShader )
			{

			}

			void Device::SetSS( enumShaderType type,U32 uiRegister,State* pState )
			{

			}

			void Device::SetRS( State* pState )
			{

			}

			void Device::SetDSS( State* pState )
			{

			}

			void Device::SetBS( State* pState )
			{

			}


			void Device::DrawOpt( const DrawOption& opt )
			{
				m_uiDrawBatch++;
				m_uiDrawTriangleCount	+=	opt.m_uiIndexCount/3;
			}

			void	Device::SetVP( float fX,float fY,float fW,float fH )
			{

			}

			void	Device::SetSRV( enumShaderType type,U32 uiIndex,void* pSRV )
			{

			}

			void	Device::SetUAV( U32 uiCount,void** pUAV,U32 uiUAVInitCount  )
			{

			}
			void	Device::ClearUAV(void* pUAV,U32* uiClear)
			{

			};
			void	Device::ClearUAV(void* pUAV,float* fClear)
			{

			};
			void	Device::SetRTV_DSV( U32 uiCount,void** pRTV,void* pDSV )
			{

			}
			void	Device::SetRTV_DSV_UAV(U32	uiCount,void**	pRTV,void*	pDSV,U32 uiUAVStart,U32 uiUAVCount,void** pUAV,U32 uiUAVInitCount )
			{

			}

			Air::Engine::enumSystemVersion Device::GetHWVersion()
			{
				return	m_HWVersion;
			}

			Device::Device():IProduct("Device")
			{
				m_HWVersion	=	enRSV_11;

				m_uiDrawBatch			=	0;
				m_uiDrawTriangleCount	=	0;
			}

			void Device::Dispatch( U32 x,U32 y,U32 z )
			{

			}

		}
	}
}