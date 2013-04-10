#include "AirEngineFont.h"
#include "AirRenderTexture.h"
#include "AirRenderTarget.h"
#include "AirRenderSystem.h"
#include "AirGlobalSetting.h"

#include <ft2build.h>
#include FT_FREETYPE_H


namespace Air{
	
	
	namespace	Engine{
	
		AString	Font::ProductTypeName="Font";
		Font::Font( AString strName,Info* pInfo ):IProduct(strName){
			m_Info			=	*pInfo;
			m_pLibrary		=	NULL;
			m_pFace			=	NULL;
			m_pCharTexture	=	NULL;
			m_vLastPosition	=	Float2(0,0);
		}
	
		U1 Font::Create(){
			//0��ʾû�д���
			SInt	error	=	0;
			//��ʼ��Freetype
			error	=	FT_Init_FreeType( &m_pLibrary );
			//��������
			error	=	FT_New_Face( m_pLibrary,m_strProductName.c_str(),0,&m_pFace );
	
			if(error!=0){
				EngineLogError((AChar*)m_strProductName.c_str(),"Create	Font Failed!");
				return false;
			}
	
			//���������С
			error	=	FT_Set_Char_Size(
				m_pFace,    /* handle to face object           */
				0,       /* char_width in 1/64th of points  */
				16*64,   /* char_height in 1/64th of points */
				300,     /* horizontal device resolution    */
				300 );   /* vertical device resolution      */
			//�����������ش�С
			error = FT_Set_Pixel_Sizes(
				m_pFace,   /* handle to face object */
				0,      /* pixel_width           */
				24 );   /* pixel_height          */
	
			AString	strFontName;
			GlobalSetting::ParsePath(m_strProductName,NULL,&strFontName,NULL);
	
			Texture::Info	texInfo;
			texInfo.SetManageTexture(m_Info.uiTexSize,m_Info.uiTexSize,enTFMT_R8G8_UNORM);

			
			m_pCharTexture	=	Render::System::GetSingleton()->CreateProduct<Texture>(("..\\Data\\Font.dds"),&texInfo);
	
			if(m_pCharTexture==NULL){
				Destroy();
				return false;
			}
			m_pObject	=	(UInt*)m_pCharTexture;
			return	true;
		}
	
		U1 Font::Destroy(){
			if(m_pCharTexture!=NULL){
				m_pCharTexture->ReleaseRef();
				m_pCharTexture	=	NULL;
			}
			if(m_pFace!=NULL){
				FT_Done_Face(m_pFace);
				m_pFace	=	NULL;
			}
			if(m_pLibrary!=NULL){
				FT_Done_FreeType(m_pLibrary);
				m_pLibrary	=	NULL;
			}
	
			m_pObject	=	NULL;
			return	true;
		}
	
		Float4 Font::AddChar( WChar c ){
			Float4	v	=	Float4(0,0,0,0);
			//�жϸ��ַ��Ƿ��Ѿ�����
			if(GetCharPosSize(c,v))
				return	v;
			else{
				U1	bEnglish	=	false;
				if(c	<=	255){
					bEnglish	=	true;
				}
				//û��������������ͼ
				U8*	pBuff	=	NULL;
				CreateCharBitmap(c,v,&pBuff);
				//Ȼ���ٺϲ������������У������ظ��ַ���ͼƬ��λ�úʹ�С
				Combine2Texture(pBuff,v.x,v.y,v,bEnglish);
				//�����б���
				m_mapChar.insert(CharMapPair(c,v));
				return v;
			}
		}
	
		VectorArray Font::AddString( WString s ){
			UInt	uiNumChar	=	s.size();
			VectorArray	vArray;
			vArray.resize(uiNumChar);
	
			for(UInt i=0;i<uiNumChar;i++){
				vArray[i]	=	AddChar(s[i]);
			}
			//test���Դ���
			//m_pCharTexture->SaveToFile("..\\Data\\Font");
			return	vArray;
		}
	
		U1 Font::CreateCharBitmap( WChar c,Float4& vPosSize,U8** pBuff ){
			SInt error	=	0;
			FT_GlyphSlot    glyph	=	NULL;
	
			FT_Load_Glyph(m_pFace, FT_Get_Char_Index(m_pFace,  c ), FT_LOAD_DEFAULT);
			error  =  FT_Render_Glyph(m_pFace->glyph,  FT_RENDER_MODE_NORMAL);
			if ( ! error)
			{
				//  convert glyph to bitmap with 256 gray 
				glyph		=	m_pFace->glyph;//->
				FT_Bitmap&     bitmap  =  glyph->bitmap;
				*pBuff		=	bitmap.buffer;
				vPosSize.x	=	bitmap.width;
				vPosSize.y	=	bitmap.rows;
	
			}
			return true;
		}
	
		U1 Font::GetCharPosSize( WChar c,Float4& vPosSize ){
			CharMapItr	i	=	m_mapChar.find(c);
			if(i!=m_mapChar.end()){
				vPosSize	=	i->second;
				return true;
			}
			return	false;
		}
	
		U1 Font::Combine2Texture( U8* pBuff,SInt w,SInt h,Float4& vPosSize,U1	bEng ){
			if(m_pCharTexture==NULL)
				return	false;
			//Render::ITexture*		pTexture	=	m_pCharTexture->GetTexture();
			const Texture::Info&	texInfo		=	m_pCharTexture->GetInfo();
	
			//SInt	halfWidth	=	w/2;
			//SInt	halfHeight	=	h/2;
			
	
			if(m_vLastPosition.x	+	m_uiCharSize	>	texInfo.width){
				m_vLastPosition.x	=	0;
				m_vLastPosition.y	+=	m_uiCharSize;
			}
	
			if(m_vLastPosition.y	>	texInfo.height){
				EngineLogError((AChar*)(m_strProductName.c_str()),"�����������������С");
				return	false;
			}
			//Ӣ���ַ���ȼ��� ����֮�������ַ���0.5�ȽϺ���
			if(bEng){
				vPosSize.x	=	(Real)(m_Info.uiSize)/(Real)m_Info.uiTexSize*0.6f;
			}else{
				vPosSize.x	=	(Real)(m_Info.uiSize)/(Real)m_Info.uiTexSize;
			}
			
			vPosSize.y	=	(Real)(m_Info.uiSize-2)/(Real)m_Info.uiTexSize;
			vPosSize.z	=	(Real)(m_vLastPosition.x)/(Real)m_Info.uiTexSize;
			vPosSize.w	=	(Real)(m_vLastPosition.y)/(Real)m_Info.uiTexSize;
	
	// 		AChar	str[128];15927748449
	// 		sprintf_s(str,128,"%f,%f\n",m_vLastPosition.x,m_vLastPosition.y);
	// 		::OutputDebugStringA(str);
	
	
			
			SInt	jDst	=	0;
			if(bEng){
				//Ӣ��Ҫ�Եױ߶���
				jDst	=	m_vLastPosition.y	+ (m_uiCharSize-h-2);
			}else{
				//����Ҫ���ж���
				jDst	=	m_vLastPosition.y;
			}
			
			SInt	jSrc	=	0;
	
// 			Render::ITexture::LockRectOption	option;
// 			m_pCharTexture->Lock(&option,LOCK_NO_DIRTY_UPDATE);
// 			U8*	p	=	(U8*)option.pData;
// 	
// 			for(;jSrc<h;jSrc++,jDst++){
// 				SInt	iSrc	=	0;
// 				SInt	iDst	=	m_vLastPosition.x;
// 				for(;iSrc<w;iSrc++,iDst++){
// 					p[jDst*texInfo.width+iDst]	=	pBuff[jSrc*w+iSrc];
// 				}
// 			}
// 			m_pCharTexture->UnLock();
	
			m_vLastPosition.x	+=	m_uiCharSize;
	
			return true;
		}
	
		Texture* Font::GetTexture(){
			return	m_pCharTexture;
		}
		UInt	Font::m_uiCharSize	=	25;
	
	}
};