#ifndef RENDERTEXTURE_HEAD_FILE
#define RENDERTEXTURE_HEAD_FILE

#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"
namespace Air{
	
	
	namespace Client{
	
		namespace	Render{
			/**	\brief	��������
			*
			*	��������
			*
			***/
			class	Texture9	:
				public	ITexture{
			public:
	
			public:
				Texture9(CAString&	strTextureName,Info*	pInfo);
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
				/**	\brief	��ȡ��������
				*   
				*	@remarks 	��ȡ��������
				*	@see		Texture
				*	@return   	SInt
				*	@note
				*
				**/
				inline	enumType	GetTextureType(){return	m_Info.type;};
	
				/**	\brief	���������ļ�
				*   
				*	@remarks 	���������ļ�
				*	@see		Texture
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				virtual U1	SaveToFile(AString	strName);
				/**	\brief	���������ڴ�
				*   
				*	@remarks 	���������ڴ�
				*	@see		Texture
				*	@return   	U1
				*	@param		MemoryData * * ppData
				*	@note
				*
				**/
				virtual U1	SaveToMemery(MemoryData**	ppData);

				/**	\brief	�ؽ�
				*   
				*	@remarks 	�ؽ�
				*	@see		Target
				*	@return   	void
				*	@param		Info & info
				*	@note
				*
				**/
				virtual	void		ReCreate(Info&	info);
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		ITexture
				*	@return   	U1
				*	@param		LockRect * rect
				*	@param		DWORD flag
				*	@note
				*
				**/
				virtual	U1	Lock(LockRectOption*	p,DWORD flag	=	LOCK_DISCARD );
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		ITexture
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	UnLock();
				
				/**	\brief	ʹ��HDC����
				*   
				*	@remarks 	ʹ��HDC����
				*	@see		Texture
				*	@return   	void
				*	@param		DrawDCCallback * pCallback
				*	@note
				*
				**/
				virtual	HDC	GetHDC();
				virtual	void*					GetTexture();
				virtual	void*					GetSurface(enumCubeFaceType	uiFaceType);

				virtual	void	OnLostDevice();
				virtual	void	OnResetDevice();

				IDirect3DTexture9*			m_pTexture2D;
				IDirect3DCubeTexture9*		m_pTextureCube;
				IDirect3DVolumeTexture9*	m_pTexture3D;
				IDirect3DSurface9*			m_pSurface;

				MemoryData*					m_pTextureData;

				Resource::IStream*			m_pStream;
			};
	
			class	Texture9Factory	:	public	Factory{
			public:
				Texture9Factory();
	
				/**	\brief	������Ʒ
				*   
				*	@remarks 	������Ʒ
				*	@see		TextureFactory
				*	@return   	IProduct*
				*	@param		AString strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam = NULL);
			};
	
		}
	};
};
#endif // RENDERTEXTURE_HEAD_FILE