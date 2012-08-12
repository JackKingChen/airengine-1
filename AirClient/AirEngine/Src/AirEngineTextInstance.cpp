#include "AirEngineTextInstance.h"
#include "AirRenderSystem.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirCommonConverter.h"
#include "AirEngineFont.h"
namespace Air{
	
	namespace	Client{
		//struct	
	
	
		TextInstance::TextInstance( CAString& strName ,Info*	pInfo):InstanceEntity(strName,pInfo->uiMaxInstance){
			m_pFont	=	NULL;
			m_strMaterialName	=	pInfo->strMaterialName;
			m_uiTextSize		=	pInfo->uiSize;
			m_Rect[0]			=	0;
			m_Rect[1]			=	0;
			m_Rect[2]			=	300;
			m_Rect[3]			=	300;
		}
	
		U1 TextInstance::CreateModelVertexBuff(){
// 			VertexBuff::Info vInfo(12,4);
// 			m_pModelVertexBuff	=	Render::System::GetSingleton()->Create<VertexBuff*>("TextVertexBuff","VertexBuff",&vInfo);
// 			if(m_pModelVertexBuff	==	NULL)
// 				return false;
	
// 	 		Float3*	p	=	NULL;
// 	 		m_pModelVertexBuff->Lock(LockOption(0,0,(void**)&p));
// 	 		p[0]	=	Float3(-1.0f,	1.0f,	1.0f);
// 	 		p[1]	=	Float3(1.0f,	1.0f,	1.0f);
// 	 		p[2]	=	Float3(-1.0f,	-1.0f,	1.0f);
// 	 		p[3]	=	Float3(1.0f,	-1.0f,	1.0f);
// 	 		m_pModelVertexBuff->Unlock();
	
			//���ö�����
// 			m_DrawBuff.m_DrawOption.m_uiVertexCount		=	4;
// 			//��������
// 			m_DrawBuff.m_DrawOption.m_uiFaceCount		=	2;
	
			return true;
		}
	
		U1 TextInstance::CreateInstanceVertexBuff(){
// 			VertexBuff::Info vInfo(sizeof(Render::Vertex::IBuff::InstanceData),1024);
// 			m_pInstanceVertexBuff	=	Render::System::GetSingleton()->Create<VertexBuff*>("TextInstance","VertexBuff",&vInfo);
// 			if(m_pInstanceVertexBuff	==	NULL)
// 				return false;
	// 		Float4		vDefault(0,0,0,0);
	// 		Float4*	v	=	NULL;
	// 		m_pInstanceVertexBuff->Lock(LockOption(0,0,(void**)v));
	// 		memset()
	// 		m_pInstanceVertexBuff->Unlock();
	
			//��������
			Font::Info	info;
			m_pFont	=	EngineSystem::GetSingleton()->CreateProduct<Font*>(AString("..\\Data\\STLITI.ttf"),AString("Font"),&info);
			
			return true;
		}
	
		U1 TextInstance::CreateDeclare(){
	
// 			VertexDeclare::Info info(0);
// 			info.SetP_Instance();
// 			VertexDeclare*	pDeclare	=	Render::System::GetSingleton()->Create<VertexDeclare*>(AString("TextInstance"),AString("VertexDeclare"),&info);
// 			if(pDeclare	==	NULL)
// 				return false;
// 			m_DrawBuff.m_pVertexDeclare	=	pDeclare;
			return true;
		}
	
		U1 TextInstance::CreateIndex(){
			//������������
			IndexBuffer::Info	IndexBuffInfo;
			IndexBuffInfo.SetIndexBuffer16(6);
			IndexBuffer*	pIndexBuff	=	Render::System::GetSingleton()->CreateProduct<IndexBuffer*>(AString("ScreenIndexBuff"),AString("IndexBuff"),&IndexBuffInfo);
			if(pIndexBuff==NULL){
				Render::System::GetSingleton()->DestroyProduct(pIndexBuff);
				return false;
			}
			//�������
			DWORD*	pIndex	=	NULL;
// 			pIndexBuff->Lock(LockOption(0,0,(void**)&pIndex));
// 			pIndex[0]	=	0;
// 			pIndex[1]	=	1;
// 			pIndex[2]	=	2;
// 			pIndex[3]	=	2;
// 			pIndex[4]	=	1;
// 			pIndex[5]	=	3;
// 	
// 			pIndexBuff->Unlock();
	
			//m_DrawBuff.m_pIndexBuff	=	pIndexBuff;
			return true;
		}
	
		void TextInstance::SetText( AString strText ){
			//��ACSII��ת��ΪUNICODE
			m_strText	=	Common::Converter::Acsi2WideByte(strText);
			if(m_pInstanceVertexBuff==NULL)
				return;
	
			//��������
			UInt	uiCharSize	=	m_strText.size();
	
			static	Real&	ScreenWidth	=	GetGlobalSetting().m_ShaderParam.m_iScreenWidth;
			SInt	iNumCharPerLine		=	(SInt)m_Rect[2]/(SInt)m_uiTextSize;
			//��ȡ�ַ����������е�UV
			VectorArray	vArray	=	m_pFont->AddString(m_strText);
			//ʵ������
//			VertexBuffer::InstanceData*	v	=	NULL;
			//��ǰ��
			UInt	iLine	=	0;
			//��ǰ����ƫ��
			UInt	iX		=	0;
			//��ǰ���ֵĴ�С
			UInt	iCharSize		=	m_uiTextSize;
			//��һ���ַ���С
			UInt	iLastCharSize	=	0;
			//��Ҫ��Ⱦ����������
			UInt	iNumNeedRenderChar	=	0;
	
// 			m_pInstanceVertexBuff->Lock(LockOption(0,0,(void**)&v));
// 			for(UInt i=0;i<uiCharSize;i++){
// 				WChar	c	=	m_strText[i];
// 				//�ж��Ƿ���Ӣ���ַ� ���ֻ����ַ�	����Ϊ�����ַ���һ��
// 				if(c	<=	255){
// 					iCharSize	=	m_uiTextSize/2;
// 				}else{
// 					iCharSize	=	m_uiTextSize;
// 				}
// 	
// 				//�ж��Ƿ�Ϊ���з�	�����ַ�����������ʾ��ı߽�   ����Ҫ����
// 				if(c	==	L'\n'	||	(iX	+	iLastCharSize/2 +	iCharSize)	>	m_Rect[2]){
// 					iLine++;
// 					iLastCharSize	=	0;
// 					iX				=	0;
// 					//����ǻ��з�  ����Ҫ��Ⱦ
// 					if(c	==	L'\n'){
// 						continue;
// 					}
// 				}
// 	
// 				//�������ı�����
// 				iX	+=	(iLastCharSize	+	iCharSize)/2;
// 				iLastCharSize	=	iCharSize;
// 	
// 				Real	x		=	m_Rect[0]	+	iX;
// 				Real	y		=	m_Rect[1]	+	m_uiTextSize/2	+	m_uiTextSize*iLine;
// 	
// 				//�ж������Ƿ񳬹��ױ�  ������� ��ֱ�Ӳ���Ⱦ���������
// 				if(y	>	m_Rect[3]){
// 					break;
// 				}
// 	
// 				//д����Ϣ
// 				v[iNumNeedRenderChar].Position	=	Float4(iCharSize,m_uiTextSize,x,y);
// 				v[iNumNeedRenderChar].Color		=	vArray[i];
// 	
// 				//����һ����Ҫ��ʾ������
// 				iNumNeedRenderChar++;
// 				//������Ϣ
// 	// 			AChar str[128];
// 	// 			AString	 strPos	=	Converter::toString(v[i].Position);
// 	// 			AString	 strUV	=	Converter::toString(v[i].Color);
// 	// 			sprintf_s(str,128,"λ��=%s UV=%s\n",strPos.c_str(),strUV.c_str());
// 	// 			OutputDebugStringA(str);
// 			}
// 			m_pInstanceVertexBuff->Unlock();
	
			SetInstanceCount(iNumNeedRenderChar);
		}
	
		AString TextInstance::GetText(){
			return	Common::Converter::WideByte2Acsi(m_strText);
		}
	
		void TextInstance::SetTextSize(UInt	uiSize){
			m_uiTextSize	=	uiSize;
			if(!m_strText.empty()){
				SetText(GetText());
			}
		}
	
		void TextInstance::SetTextRect( RECT rect ){
			m_Rect[0]	=	rect.left;
			m_Rect[1]	=	rect.top;
			m_Rect[2]	=	rect.right	-	rect.left;
			m_Rect[3]	=	rect.bottom	-	rect.top;
	
		}
	
		RECT TextInstance::GetTextRect(){
			RECT	rect;
			rect.left	=	m_Rect[0];
			rect.top	=	m_Rect[1];
			rect.right	=	m_Rect[0]	+	m_Rect[2];
			rect.bottom	=	m_Rect[1]	+	m_Rect[3];
			return	rect;
		}
		TextInstanceFactory::TextInstanceFactory(){
			m_strTypeName	=	"TextInstance";
		}
	
		IProduct* TextInstanceFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
			if(lstParam	==	NULL)
				return	false;
			TextInstance::Info*	pInfo	=	(TextInstance::Info*)lstParam;
			TextInstance*		pBuff	=	new	TextInstance(strName,pInfo);
	
			return	pBuff;
		}
	}
};