#include "AirRenderTexture11.h"
#include "AirRenderGlobal11.h"
#include "AirRenderDevice11.h"

static const GUID ___IID_ID3D11Texture2D={0x6f15aaf2,0xd208,0x4e89,0x9a,0xb4,0x48,0x95,0x35,0xd3,0x4f,0x9c};
static const GUID ___IID_ID3D11Texture3D={0x037e866e,0xf56d,0x4357,0xa8,0xaf,0x9d,0xab,0xbe,0x6e,0x25,0x0e};

namespace Air{
	
	namespace	Engine{
		extern	Render::Device11*	pDevice;
		namespace	Render{
	
	
			Texture11::Texture11(CAString&	strTextureName,Info*	pInfo)
				:	Texture(strTextureName,pInfo),
				m_pTexture2D(NULL),
				m_pTextureCube(NULL),
				m_pTexture3D(NULL){

					m_pStream	=	NULL;
					m_pSurface	=	NULL;

					m_pSRV		=	NULL;
					m_pUAV		=	NULL;
					m_pRTV		=	NULL;
			}
			U1 Texture11::Create(){
				DxDevice*	pDxDevice	=	(DxDevice*)pDevice->GetDevice();

				if(m_Info.format	==	enTFMT_UNKNOWN){
					Data data;
					ResourceSystem::GetSingleton()->Find(m_strProductName,data);

					if(!data.IsNull()){
						D3DX11_IMAGE_INFO	imgInfo;
						D3DX11GetImageInfoFromMemory(data.buff,data.size,NULL,&imgInfo,NULL);
						D3DX11_IMAGE_LOAD_INFO	loadInfo;
						MemoryZero(loadInfo);
						D3DX11CreateShaderResourceViewFromMemory(pDxDevice,data.buff,data.size,0,NULL,&m_pSRV,NULL);
						m_Info.width	=	imgInfo.Width;
						m_Info.height	=	imgInfo.Height;
						m_Info.depth	=	imgInfo.Depth;
						m_Info.format	=	(enumTextureFormat)imgInfo.Format;
						m_Info.mipmap	=	imgInfo.MipLevels;
						m_Info.viewFlag	=	enVF_SRV;
						m_Info.usage	=	enUSAGE_MANAGED;

						D3D11_SHADER_RESOURCE_VIEW_DESC	srvDesc;
						m_pSRV->GetDesc(&srvDesc);
						m_Info.format	=	(enumTextureFormat)srvDesc.Format;
						m_Info.mipmap	=	srvDesc.Texture2D.MipLevels;

						ID3D11Resource*	pResource	=	NULL;
						//这里会增加引用计数
						m_pSRV->GetResource(&pResource);
						if(pResource!=NULL){

							//这里会再次增加引用计数
							HRESULT	hr	=	D3D_OK;
							hr	=	pResource->QueryInterface(___IID_ID3D11Texture2D,(void**)&m_pTexture2D);
							if(FAILED(hr)){
								hr	=	pResource->QueryInterface(___IID_ID3D11Texture3D,(void**)&m_pTexture3D);
								if(SUCCEEDED(hr)){
									m_Info.type	=	enTT_Texture3D;
								}
							}else{
								m_Info.type	=	enTT_Texture2D;

							}

							pResource->Release();
						}

						if(imgInfo.MiscFlags&D3D11_RESOURCE_MISC_TEXTURECUBE){
							m_Info.type	=	enTT_TextureCUBE;
						}
					}else{
						return	false;
					}

				}else{
					switch(m_Info.type){
						case	enTT_Texture2D:{
							D3D11_TEXTURE2D_DESC	desc;
							MemoryZero(desc);
							
							desc.ArraySize	=	1;
							if(m_Info.viewFlag	&	enVF_SRV){
								desc.BindFlags	|=	D3D11_BIND_SHADER_RESOURCE;
							}
							if(m_Info.viewFlag	&	enVF_RTV){
								desc.BindFlags	|=	D3D11_BIND_RENDER_TARGET;
							}
							if(m_Info.viewFlag	&	enVF_UAV){
								desc.BindFlags	|=	D3D11_BIND_UNORDERED_ACCESS;
							}
							if(m_Info.viewFlag	&	enVF_DSV){
								desc.BindFlags	|=	D3D11_BIND_DEPTH_STENCIL;
							}
							if(m_Info.usage	==	enUSAGE_DYNAMIC){
								desc.CPUAccessFlags	=	D3D11_CPU_ACCESS_WRITE;
								desc.Usage			=	D3D11_USAGE_DYNAMIC;
							}


							if(m_Info.fScreenScale	>	0.0f){
								RenderWindow*	pWindow	=	RenderSystem::GetSingleton()->GetMainWindow();
								desc.Width		=	(UINT)pWindow->GetWidth()*m_Info.fScreenScale;
								desc.Height		=	(UINT)pWindow->GetHeight()*m_Info.fScreenScale;

								m_Info.width	=	desc.Width;
								m_Info.height	=	desc.Height;
							}else{
								desc.Width		=	m_Info.width;
								desc.Height		=	m_Info.height;
							}
							desc.Format		=	(DXGI_FORMAT)m_Info.format;
							desc.MipLevels	=	m_Info.mipmap;
							desc.SampleDesc.Count	=	1;
							desc.SampleDesc.Quality	=	0;
							desc.MiscFlags			=	0;
							//支持生成MipMap
							if(m_Info.bAutoMipMap){
								desc.MiscFlags	|=	D3D11_RESOURCE_MISC_GENERATE_MIPS;
							}

							HRESULT	hr	=	pDxDevice->CreateTexture2D(&desc,NULL,&m_pTexture2D);
							if(hr!=S_OK)
							{
								return false;
							}

							if(m_Info.viewFlag&enVF_SRV){
								D3D11_SHADER_RESOURCE_VIEW_DESC	srvDesc;
								MemoryZero(srvDesc);
								srvDesc.Format				=	desc.Format;
								srvDesc.ViewDimension		=	D3D11_SRV_DIMENSION_TEXTURE2D;
								srvDesc.Texture2D.MipLevels	=	desc.MipLevels;
								pDxDevice->CreateShaderResourceView(m_pTexture2D,&srvDesc,&m_pSRV);
							}
							if(m_Info.viewFlag&enVF_RTV){
								D3D11_RENDER_TARGET_VIEW_DESC	rtvDesc;
								MemoryZero(rtvDesc);
								rtvDesc.Format				=	desc.Format;
								rtvDesc.ViewDimension		=	D3D11_RTV_DIMENSION_TEXTURE2D;
								pDxDevice->CreateRenderTargetView(m_pTexture2D,&rtvDesc,&m_pRTV);
							}
							if(m_Info.viewFlag&enVF_UAV){
								D3D11_UNORDERED_ACCESS_VIEW_DESC	uavDesc;
								MemoryZero(uavDesc);
								uavDesc.Format				=	desc.Format;
								uavDesc.ViewDimension		=	D3D11_UAV_DIMENSION_TEXTURE2D;
								pDxDevice->CreateUnorderedAccessView(m_pTexture2D,&uavDesc,&m_pUAV);
							}
								

							break;}
					}
				}
				return	true;
			}
	
			U1 Texture11::Destroy( ){
				
				SAFE_RELEASE(m_pTexture2D);
				SAFE_RELEASE(m_pTexture3D);
				SAFE_RELEASE(m_pTextureCube);
				SAFE_RELEASE(m_pSRV);
				SAFE_RELEASE(m_pRTV);
				SAFE_RELEASE(m_pUAV);

				return	true;
			}

			void* Texture11::GetBuffer()
			{
				switch(m_Info.type){
					case enTT_Texture2D:return	m_pTexture2D;
				}
				return	NULL;
			}

			void* Texture11::GetRTV()
			{
				return	m_pRTV;
			}

			void* Texture11::GetUAV()
			{
				return	m_pUAV;
			}

			void* Texture11::GetSRV()
			{
				return	m_pSRV;
			}

			void Texture11::CopyBufferTo( Texture* pDest )
			{
				if(pDest==NULL)
					return;
				DxContext*	pContext	=	(DxContext*)(pDevice->GetContext());
				ID3D11Resource*	pSrcResource	=	(ID3D11Resource*)GetBuffer();
				ID3D11Resource*	pDestResource	=	(ID3D11Resource*)pDest->GetBuffer();
				if(pSrcResource	==	NULL	||	pDestResource	==	NULL)
					return;
				pContext->CopyResource(pDestResource,pSrcResource);
			}

			void Texture11::GenMipMap()
			{
				if(m_Info.viewFlag&enVF_RTV	){
					if(!m_Info.bAutoMipMap){
						return;
					}
				}
				if(m_Info.mipmap	==	1)
					return;

				DxContext*	pContext	=	(DxContext*)(pDevice->GetContext());
				pContext->GenerateMips(m_pSRV);
			}

			bool Texture11::Write( void* pData,U32	uiPitch,RECT* pRect )
			{
				if(m_pTexture2D==NULL)
					return	false;
				
				DxContext*	pContext	=	(DxContext*)(pDevice->GetContext());
				
				HRESULT	hr	=	D3D_OK;

				if(pRect==NULL){
					pContext->UpdateSubresource(m_pTexture2D,0,NULL,pData,uiPitch,0);
				}else{
					D3D11_BOX	box={pRect->left,pRect->top,0,pRect->right,pRect->bottom,1};
					pContext->UpdateSubresource(m_pTexture2D,0,&box,pData,uiPitch,0);

				}
				return	true;
			}

		}
	}
};