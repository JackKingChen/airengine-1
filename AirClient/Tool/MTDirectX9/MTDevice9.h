#ifndef MTDEVICE9_HEAD_FILE
#define MTDEVICE9_HEAD_FILE

#include "MTHeader.h"
#include "MTRenderThread.h"


class	MT_IDirect3D9	:	public	MT_IUnknown
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3D9->QueryInterface(riid,ppvObj);
	};

	/*** IDirect3D9 methods ***/
	STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction){
		return	m_pIDirect3D9->RegisterSoftwareDevice(pInitializeFunction);
	};
	STDMETHOD_(UINT, GetAdapterCount)(THIS){
		return	m_pIDirect3D9->GetAdapterCount();
	};
	STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier){
		return	m_pIDirect3D9->GetAdapterIdentifier(Adapter,Flags,pIdentifier);
	};
	STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter,D3DFORMAT Format){
		return	m_pIDirect3D9->GetAdapterModeCount(Adapter,Format);
	};
	STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode){
		return	m_pIDirect3D9->EnumAdapterModes(Adapter,Format,Mode,pMode);
	};
	STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode){
		return	m_pIDirect3D9->GetAdapterDisplayMode(Adapter,pMode);
	};
	STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed){
		return	m_pIDirect3D9->CheckDeviceType(Adapter,DevType,AdapterFormat,BackBufferFormat,bWindowed);
	};
	STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat){
		return	m_pIDirect3D9->CheckDeviceFormat(Adapter,DeviceType,AdapterFormat,Usage,RType,CheckFormat);
	};
	STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels){
		return	m_pIDirect3D9->CheckDeviceMultiSampleType(Adapter,DeviceType,SurfaceFormat,Windowed,MultiSampleType,pQualityLevels);
	};
	STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat){
		return	m_pIDirect3D9->CheckDepthStencilMatch(Adapter,DeviceType,AdapterFormat,RenderTargetFormat,DepthStencilFormat);
	};
	STDMETHOD(CheckDeviceFormatConversion)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat){
		return	m_pIDirect3D9->CheckDeviceFormatConversion(Adapter,DeviceType,SourceFormat,TargetFormat);
	};
	STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps){
		return	m_pIDirect3D9->GetDeviceCaps(Adapter,DeviceType,pCaps);
	};
	STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter){
		return	m_pIDirect3D9->GetAdapterMonitor(Adapter);
	};
	STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,MT_IDirect3DDevice9** ppReturnedDeviceInterface);
public:
	MT_IDirect3D9(IDirect3D9* pIDirect3D9);
	virtual	~MT_IDirect3D9();

public:
	::IDirect3D9*	m_pIDirect3D9;
	
};

class MT_IDirect3D9Ex	:	public	MT_IDirect3D9
{
    /*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3D9Ex->QueryInterface(riid,ppvObj);
	};
    //STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    //STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirect3D9 methods ***/
    //STDMETHOD_(UINT, GetAdapterCount)(THIS) PURE;
    //STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier) PURE;
    //STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter,D3DFORMAT Format) PURE;
    //STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode) PURE;
    //STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode) PURE;
    //STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) PURE;
    //STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) PURE;
    //STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels) PURE;
    //STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) PURE;
    //STDMETHOD(CheckDeviceFormatConversion)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat) PURE;
    //STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps) PURE;
    //STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter) PURE;
    //STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) PURE;
	STDMETHOD_(UINT, GetAdapterModeCountEx)(THIS_ UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter ){
		return	m_pIDirect3D9Ex->GetAdapterModeCountEx(Adapter,pFilter);
	};
	STDMETHOD(EnumAdapterModesEx)(THIS_ UINT Adapter,CONST D3DDISPLAYMODEFILTER* pFilter,UINT Mode,D3DDISPLAYMODEEX* pMode){
		return	m_pIDirect3D9Ex->EnumAdapterModesEx(Adapter,pFilter,Mode,pMode);
	};
	STDMETHOD(GetAdapterDisplayModeEx)(THIS_ UINT Adapter,D3DDISPLAYMODEEX* pMode,D3DDISPLAYROTATION* pRotation){
		return	m_pIDirect3D9Ex->GetAdapterDisplayModeEx(Adapter,pMode,pRotation);
	}
	STDMETHOD(CreateDeviceEx)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,D3DDISPLAYMODEEX* pFullscreenDisplayMode,IDirect3DDevice9Ex** ppReturnedDeviceInterface);
	STDMETHOD(GetAdapterLUID)(THIS_ UINT Adapter,LUID * pLUID){
		return	m_pIDirect3D9Ex->GetAdapterLUID(Adapter,pLUID);
	};
public:
	MT_IDirect3D9Ex(IDirect3D9Ex* pIDirect3D9Ex);
public:
	::IDirect3D9Ex*	m_pIDirect3D9Ex;
};



class MT_IDirect3DDevice9 :	public	MT_IUnknown,public	MT_RenderThread
{
public:
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj){
		return	m_pIDirect3DDevice9->QueryInterface(riid,ppvObj);
	};

	/*** IDirect3DDevice9 methods ***/
	STDMETHOD(TestCooperativeLevel)(THIS){
		return	m_pIDirect3DDevice9->TestCooperativeLevel();
	};
	STDMETHOD_(UINT, GetAvailableTextureMem)(THIS){
		return	m_pIDirect3DDevice9->GetAvailableTextureMem();
	};
	STDMETHOD(EvictManagedResources)(THIS){
		return	m_pIDirect3DDevice9->EvictManagedResources();
	};
	STDMETHOD(GetDirect3D)(THIS_ MT_IDirect3D9** ppD3D9){
		*ppD3D9	=	m_pMT_IDirect3D9;
		m_pMT_IDirect3D9->AddRef();
		return	S_OK;
	};
	STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS9* pCaps){
		return	m_pIDirect3DDevice9->GetDeviceCaps(pCaps);
	};
	STDMETHOD(GetDisplayMode)(THIS_ UINT iSwapChain,D3DDISPLAYMODE* pMode){
		return	m_pIDirect3DDevice9->GetDisplayMode(iSwapChain,pMode);
	};
	STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters){
		return	m_pIDirect3DDevice9->GetCreationParameters(pParameters);
	};
	STDMETHOD(SetCursorProperties)(THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap){
		return	m_pIDirect3DDevice9->SetCursorProperties(XHotSpot,YHotSpot,pCursorBitmap);
	};
	STDMETHOD_(void, SetCursorPosition)(THIS_ int X,int Y,DWORD Flags){
		return	m_pIDirect3DDevice9->SetCursorPosition(X,Y,Flags);
	};
	STDMETHOD_(BOOL, ShowCursor)(THIS_ BOOL bShow){
		return	m_pIDirect3DDevice9->ShowCursor(bShow);
	};
	STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,MT_IDirect3DSwapChain9** pSwapChain);
	STDMETHOD(GetSwapChain)(THIS_ UINT iSwapChain,MT_IDirect3DSwapChain9** pSwapChain);
	STDMETHOD_(UINT, GetNumberOfSwapChains)(THIS);
	STDMETHOD(Reset)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters);
	STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
	STDMETHOD(GetBackBuffer)(THIS_ UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,MT_IDirect3DSurface9** ppBackBuffer);
	STDMETHOD(GetRasterStatus)(THIS_ UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus);
	STDMETHOD(SetDialogBoxMode)(THIS_ BOOL bEnableDialogs);
	STDMETHOD_(void, SetGammaRamp)(THIS_ UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp);
	STDMETHOD_(void, GetGammaRamp)(THIS_ UINT iSwapChain,D3DGAMMARAMP* pRamp);
	STDMETHOD(CreateTexture)(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle);
	STDMETHOD(CreateVolumeTexture)(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle);
	STDMETHOD(CreateCubeTexture)(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle);
	STDMETHOD(CreateVertexBuffer)(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,MT_IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle);
	STDMETHOD(CreateIndexBuffer)(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle);
	STDMETHOD(CreateRenderTarget)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,MT_IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
	STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,MT_IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
	STDMETHOD(UpdateSurface)(THIS_ MT_IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,MT_IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint);
	STDMETHOD(UpdateTexture)(THIS_ MT_IDirect3DBaseTexture9* pSourceTexture,MT_IDirect3DBaseTexture9* pDestinationTexture);
	STDMETHOD(GetRenderTargetData)(THIS_ MT_IDirect3DSurface9* pRenderTarget,MT_IDirect3DSurface9* pDestSurface);
	STDMETHOD(GetFrontBufferData)(THIS_ UINT iSwapChain,MT_IDirect3DSurface9* pDestSurface);
	STDMETHOD(StretchRect)(THIS_ MT_IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,MT_IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter);
	STDMETHOD(ColorFill)(THIS_ MT_IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color);
	STDMETHOD(CreateOffscreenPlainSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,MT_IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
	STDMETHOD(SetRenderTarget)(THIS_ DWORD RenderTargetIndex,MT_IDirect3DSurface9* pRenderTarget);
	STDMETHOD(GetRenderTarget)(THIS_ DWORD RenderTargetIndex,MT_IDirect3DSurface9** ppRenderTarget);
	STDMETHOD(SetDepthStencilSurface)(THIS_ MT_IDirect3DSurface9* pNewZStencil);
	STDMETHOD(GetDepthStencilSurface)(THIS_ MT_IDirect3DSurface9** ppZStencilSurface);
	STDMETHOD(BeginScene)(THIS);
	STDMETHOD(EndScene)(THIS);
	STDMETHOD(Clear)(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil);
	STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix);
	STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix);
	STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*);
	STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT9* pViewport);
	STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT9* pViewport);
	STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL9* pMaterial);
	STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL9* pMaterial);
	STDMETHOD(SetLight)(THIS_ DWORD Index,CONST D3DLIGHT9*);
	STDMETHOD(GetLight)(THIS_ DWORD Index,D3DLIGHT9*);
	STDMETHOD(LightEnable)(THIS_ DWORD Index,BOOL Enable);
	STDMETHOD(GetLightEnable)(THIS_ DWORD Index,BOOL* pEnable);
	STDMETHOD(SetClipPlane)(THIS_ DWORD Index,CONST float* pPlane);
	STDMETHOD(GetClipPlane)(THIS_ DWORD Index,float* pPlane);
	STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD Value);
	STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue);
	STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type,MT_IDirect3DStateBlock9** ppSB);
	STDMETHOD(BeginStateBlock)(THIS);
	STDMETHOD(EndStateBlock)(THIS_ MT_IDirect3DStateBlock9** ppSB);
	STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS9* pClipStatus);
	STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS9* pClipStatus);
	STDMETHOD(GetTexture)(THIS_ DWORD Stage,MT_IDirect3DBaseTexture9** ppTexture);
	STDMETHOD(SetTexture)(THIS_ DWORD Stage,MT_IDirect3DBaseTexture9* pTexture);
	STDMETHOD(GetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue);
	STDMETHOD(SetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value);
	STDMETHOD(GetSamplerState)(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue);
	STDMETHOD(SetSamplerState)(THIS_ DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value);
	STDMETHOD(ValidateDevice)(THIS_ DWORD* pNumPasses);
	STDMETHOD(SetPaletteEntries)(THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries);
	STDMETHOD(GetPaletteEntries)(THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries);
	STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT PaletteNumber);
	STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber);
	STDMETHOD(SetScissorRect)(THIS_ CONST RECT* pRect);
	STDMETHOD(GetScissorRect)(THIS_ RECT* pRect);
	STDMETHOD(SetSoftwareVertexProcessing)(THIS_ BOOL bSoftware);
	STDMETHOD_(BOOL, GetSoftwareVertexProcessing)(THIS);
	STDMETHOD(SetNPatchMode)(THIS_ float nSegments);
	STDMETHOD_(float, GetNPatchMode)(THIS);
	STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount);
	STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
	STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
	STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride);
	STDMETHOD(ProcessVertices)(THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,MT_IDirect3DVertexBuffer9* pDestBuffer,MT_IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags);
	STDMETHOD(CreateVertexDeclaration)(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,MT_IDirect3DVertexDeclaration9** ppDecl);
	STDMETHOD(SetVertexDeclaration)(THIS_ MT_IDirect3DVertexDeclaration9* pDecl);
	STDMETHOD(GetVertexDeclaration)(THIS_ MT_IDirect3DVertexDeclaration9** ppDecl);
	STDMETHOD(SetFVF)(THIS_ DWORD FVF);
	STDMETHOD(GetFVF)(THIS_ DWORD* pFVF);
	STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pFunction,MT_IDirect3DVertexShader9** ppShader);
	STDMETHOD(SetVertexShader)(THIS_ MT_IDirect3DVertexShader9* pShader);
	STDMETHOD(GetVertexShader)(THIS_ MT_IDirect3DVertexShader9** ppShader);
	STDMETHOD(SetVertexShaderConstantF)(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
	STDMETHOD(GetVertexShaderConstantF)(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount);
	STDMETHOD(SetVertexShaderConstantI)(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
	STDMETHOD(GetVertexShaderConstantI)(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount);
	STDMETHOD(SetVertexShaderConstantB)(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
	STDMETHOD(GetVertexShaderConstantB)(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount);
	STDMETHOD(SetStreamSource)(THIS_ UINT StreamNumber,MT_IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride);
	STDMETHOD(GetStreamSource)(THIS_ UINT StreamNumber,MT_IDirect3DVertexBuffer9** ppStreamData,UINT* pOffsetInBytes,UINT* pStride);
	STDMETHOD(SetStreamSourceFreq)(THIS_ UINT StreamNumber,UINT Setting);
	STDMETHOD(GetStreamSourceFreq)(THIS_ UINT StreamNumber,UINT* pSetting);
	STDMETHOD(SetIndices)(THIS_ MT_IDirect3DIndexBuffer9* pIndexData);
	STDMETHOD(GetIndices)(THIS_ MT_IDirect3DIndexBuffer9** ppIndexData);
	STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD* pFunction,MT_IDirect3DPixelShader9** ppShader);
	STDMETHOD(SetPixelShader)(THIS_ MT_IDirect3DPixelShader9* pShader);
	STDMETHOD(GetPixelShader)(THIS_ MT_IDirect3DPixelShader9** ppShader);
	STDMETHOD(SetPixelShaderConstantF)(THIS_ UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount);
	STDMETHOD(GetPixelShaderConstantF)(THIS_ UINT StartRegister,float* pConstantData,UINT Vector4fCount);
	STDMETHOD(SetPixelShaderConstantI)(THIS_ UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount);
	STDMETHOD(GetPixelShaderConstantI)(THIS_ UINT StartRegister,int* pConstantData,UINT Vector4iCount);
	STDMETHOD(SetPixelShaderConstantB)(THIS_ UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount);
	STDMETHOD(GetPixelShaderConstantB)(THIS_ UINT StartRegister,BOOL* pConstantData,UINT BoolCount);
	STDMETHOD(DrawRectPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo);
	STDMETHOD(DrawTriPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo);
	STDMETHOD(DeletePatch)(THIS_ UINT Handle);
	STDMETHOD(CreateQuery)(THIS_ D3DQUERYTYPE Type,MT_IDirect3DQuery9** ppQuery);

public:
	HRESULT	SwapChain_Present(IDirect3DSwapChain9*	pSwapChain,THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags);
	HRESULT	Surface_LockRect(IDirect3DSurface9*	pSurface,THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
	HRESULT	Surface_UnlockRect(IDirect3DSurface9*	pSurface);
	HRESULT Volume_LockBox(IDirect3DVolume9*	pVolume,THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
	HRESULT Volume_UnlockBox(IDirect3DVolume9*	pVolume);
	HRESULT	VertexBuffer_Lock(IDirect3DVertexBuffer9*	pVB,THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
	HRESULT	VertexBuffer_Unlock(IDirect3DVertexBuffer9*	pVB);
	HRESULT	IndexBuffer_Lock(IDirect3DIndexBuffer9*	pIB,THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
	HRESULT	IndexBuffer_Unlock(IDirect3DIndexBuffer9*	pIB);
	HRESULT	BaseTexture_SetAutoGenFilterType(IDirect3DBaseTexture9*	pTex,THIS_ D3DTEXTUREFILTERTYPE FilterType);
	HRESULT	BaseTexture_GenerateMipSubLevels(IDirect3DBaseTexture9*	pTex);
	HRESULT	Texture_LockRect(IDirect3DTexture9*	pTex,THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
	HRESULT	Texture_UnLockRect(IDirect3DTexture9*	pTex,THIS_ UINT Level);
	HRESULT	Texture_AddDirtyRect(IDirect3DTexture9*	pTex,THIS_ CONST RECT* pDirtyRect);
	HRESULT	CubeTexture_LockRect(IDirect3DCubeTexture9*	pTex,THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
	HRESULT	CubeTexture_UnlockRect(IDirect3DCubeTexture9*	pTex,THIS_ D3DCUBEMAP_FACES FaceType,UINT Level);
	HRESULT	CubeTexture_AddDirtyRect(IDirect3DCubeTexture9*	pTex,THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect);
	HRESULT	VolumeTexture_LockBox(IDirect3DVolumeTexture9*	pVolumeTex,THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
	HRESULT	VolumeTexture_UnlockBox(IDirect3DVolumeTexture9*	pVolumeTex,THIS_ UINT Level);
	HRESULT	VolumeTexture_AddDirtyBox(IDirect3DVolumeTexture9*	pVolumeTex,THIS_ CONST D3DBOX* pDirtyBox);
	HRESULT	StateBlock_Apply(IDirect3DStateBlock9* pStateBlock);
	HRESULT	StateBlock_Capture(IDirect3DStateBlock9* pStateBlock);
	

	int		PIX_D3DPERF_BeginEvent(D3DCOLOR col,LPCWSTR wszName);
	int		PIX_D3DPERF_EndEvent();
	void	PIX_D3DPERF_SetMarker(D3DCOLOR col,LPCWSTR wszName);
public: 
	HRESULT	Effect_SetValue(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes);
	HRESULT	Effect_SetBool(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, BOOL b);
	HRESULT	Effect_SetBoolArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count);
	HRESULT	Effect_SetInt(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, INT n);
	HRESULT	Effect_SetIntArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count);
	HRESULT	Effect_SetFloat(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, FLOAT f);
	HRESULT	Effect_SetFloatArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count);
	HRESULT	Effect_SetVector(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector);
	HRESULT	Effect_SetVectorArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count);
	HRESULT	Effect_SetMatrix(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
	HRESULT	Effect_SetMatrixArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
	HRESULT	Effect_SetMatrixPointerArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
	HRESULT	Effect_SetMatrixTranspose(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
	HRESULT	Effect_SetMatrixTransposeArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
	HRESULT	Effect_SetMatrixTransposePointerArray(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
	HRESULT	Effect_SetString(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPCSTR pString);
	HRESULT	Effect_SetTexture(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);

	HRESULT	Effect_SetTechnique(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hTechnique);
	HRESULT	Effect_Begin(ID3DXEffect* pID3DXEffect,THIS_ UINT *pPasses, DWORD Flags) ;
    HRESULT	Effect_BeginPass(ID3DXEffect* pID3DXEffect,THIS_ UINT Pass) ;
    HRESULT	Effect_CommitChanges(ID3DXEffect* pID3DXEffect) ;
    HRESULT	Effect_EndPass(ID3DXEffect* pID3DXEffect) ;
    HRESULT	Effect_End(ID3DXEffect* pID3DXEffect) ;
	HRESULT	Effect_SetStateManager(ID3DXEffect* pID3DXEffect,THIS_ LPD3DXEFFECTSTATEMANAGER pManager);
	HRESULT	Effect_SetRawValue(ID3DXEffect* pID3DXEffect,THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes);
public:
	MT_IDirect3DDevice9(MT_IDirect3D9*	pD3D9,IDirect3DDevice9* pIDirect3DDevice9);
	virtual	~MT_IDirect3DDevice9();

public:
	IDirect3DDevice9*		m_pIDirect3DDevice9;
	MT_IDirect3D9*			m_pMT_IDirect3D9;
	bool					m_bDeviceLost;
	int						m_iMainThreadId;
};

#endif // RENDERDEVICE_HEAD_FILE