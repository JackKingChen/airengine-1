#ifndef RENDERTEXTURE_HEAD_FILE
#define RENDERTEXTURE_HEAD_FILE

#include "AirRenderHeader11.h"
#include "AirRenderTexture.h"
namespace Air{
	
	
	namespace Client{
	
		namespace	Render{
			/**	\brief	��������
			*
			*	��������
			*
			***/
			class	Texture11	:	public	Texture{
			public:
	
			public:
				Texture11(CAString&	strTextureName,Info*	pInfo);
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Texture
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create( );
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Texture
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy( );

				virtual	bool			Write(void* pData,U32	uiPitch,RECT* pRect=NULL);


				virtual	void*			GetBuffer();
				virtual	void*			GetRTV();
				virtual	void*			GetUAV();
				virtual	void*			GetSRV();
				virtual	void			CopyBufferTo(Texture*	pDest);
				virtual	void			GenMipMap();
				
				DxTexture*			m_pTexture2D;
				DxTexture*			m_pTextureCube;
				DxVolumeTexture*	m_pTexture3D;
				DxSurface*			m_pSurface;

				DxSRV*				m_pSRV;
				DxUAV*				m_pUAV;
				DxRTV*				m_pRTV;
				//DxDSV*				m_pDSV;

				//MemoryData*					m_pTextureData;

				Resource::IStream*			m_pStream;
			};
		}
	};
};
#endif // RENDERTEXTURE_HEAD_FILE