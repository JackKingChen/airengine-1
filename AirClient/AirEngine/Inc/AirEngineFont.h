#ifndef ENGINEFONT_HEAD_FILE
#define ENGINEFONT_HEAD_FILE


#include "AirEngineHeader.h"

struct FT_LibraryRec_;		///<	FT2	Library
struct FT_FaceRec_;			///<	FT2	Face
namespace Air{
	
	
	namespace Engine{
		namespace	Render{
			class	ITexture;
		}
	
		/**	\brief	������
		*
		*	������
		*
		***/
		class	ENGINE_EXPORT	Font	:
			public	IProduct{
		public:
			static AString	ProductTypeName;
			/**	\brief	������Ϣ
			*
			*	������Ϣ
			*
			***/
			struct	Info{
				Info(){
					uiSize		=	25;
					bBorder		=	false;
					bItalic		=	false;
					uiTexSize	=	2048;
				}
				UInt	uiSize;		///<	�����С
				U1		bBorder;	///<	�Ӵ�
				U1		bItalic;	///<	б��
				UInt	uiTexSize;	///<	����ͼƬ�����С
			};
	
			typedef	std::map<WCHAR,Float4>		CharMap;
			typedef	CharMap::iterator			CharMapItr;
			typedef	CharMap::value_type			CharMapPair;
	
	
		public:
			Font(AString	strName,Info*	pInfo);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Font
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		Font
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	
			/**	\brief	�������
			*   
			*	@remarks 	�������
			*	@see		Font
			*	@return   	Client::Float4
			*	@param		WChar c
			*	@note
			*
			**/
			virtual	Float4			AddChar(WChar	c);
			/**	\brief	����ַ���
			*   
			*	@remarks 	����ַ���
			*	@see		Font
			*	@return   	Client::VectorArray
			*	@param		WString s
			*	@note
			*
			**/
			virtual	VectorArray		AddString(WString	s);
	
			/**	\brief	��ȡ����
			*   
			*	@remarks 	��ȡ����
			*	@see		Font
			*	@return   	Texture*
			*	@note
			*
			**/
			virtual	Texture*	GetTexture();
		protected:
			/**	\brief	����������ͼ
			*   
			*	@remarks 	����������ͼ
			*	@see		Font
			*	@return   	U1
			*	@param		WChar c
			*	@param		Float4 & vPosSize
			*	@param		U8 * * pBuff
			*	@note
			*
			**/
			U1	CreateCharBitmap(WChar	c,Float4& vPosSize,U8**	pBuff);
			/**	\brief	��ȡ������ͼƬ�е�λ�úʹ�С
			*   
			*	@remarks 	��ȡ������ͼƬ�е�λ�úʹ�С
			*	@see		Font
			*	@return   	U1
			*	@param		WChar c
			*	@param		Float4 & vPosSize
			*	@note
			*
			**/
			U1	GetCharPosSize(WChar c,Float4& vPosSize);
			/**	\brief	�ϲ����ֵ�������
			*   
			*	@remarks 	�ϲ����ֵ�������
			*	@see		Font
			*	@return   	U1
			*	@param		U8 * pBuff
			*	@param		SInt w
			*	@param		SInt h
			*	@param		Float4 & vPosSize
			*	@param		U1	bEng
			*	@note
			*
			**/
			U1	Combine2Texture(U8*	pBuff,SInt	w,SInt h,Float4& vPosSize,U1	bEng);
		protected:
			Info				m_Info;				///<	��Ϣ
			FT_LibraryRec_*		m_pLibrary;			///<	FT2	��ָ�� void* 
			FT_FaceRec_*		m_pFace;			///<	FT2	����ָ��
			CharMap				m_mapChar;			///<	�ַ����洢�Ѿ����ɵ����֣�
			Texture*			m_pCharTexture;		///<	�������ֵ�ͼƬ
			Float2				m_vLastPosition;	///<	�ϴ�д���ļ���λ��
			static	UInt		m_uiCharSize;		///<	���ִ�С(���ٸ�����)
		};
	
		/**	\brief	���幤��
		*
		*	���幤��
		*
		***/
		class	FontFactory	:
			public	IFactory{
		public:
			FontFactory();
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		FontFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString&	strName,IFactoryParamList* lstParam = NULL);
		};
	};
};
#endif // ENGINEFONT_HEAD_FILE