#ifndef RENDERSHADER_HEAD_FILE
#define RENDERSHADER_HEAD_FILE

#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"
namespace Air{
	
	namespace Client{
	
		namespace	Render{
			typedef	std::map<AString,DxVertexShader*>	VertexShaderMap;
			typedef	std::map<AString,DxPixelShader*>	PixelShaderMap;
			/**	\brief	������ɫ����
			*
			*	������ɫ����
			*
			***/
			class	Shader9	:
				public	IShader{
			public:
				Shader9(CAString&	strName,Info*	pInfo);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Shader
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
	
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Shader
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	��ȡ������ɫָ��
				*   
				*	@remarks 	��ȡ������ɫָ��
				*	@see		Shader
				*	@return   	IDirect3DVertexShader9*
				*	@note
				*
				**/
				IDirect3DVertexShader9*	GetVS();
				/**	\brief	��ȡ������ɫָ��
				*   
				*	@remarks 	��ȡ������ɫָ��
				*	@see		Shader
				*	@return   	IDirect3DPixelShader9*
				*	@note
				*
				**/
				IDirect3DPixelShader9*	GetPS();

				virtual	void*			GetShader();
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		IShader
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Reload();
			protected:
				/**	\brief	��ȡ������ɫ
				*   
				*	@remarks 	��ȡ������ɫ
				*	@see		Shader
				*	@return   	DxVertexShader*
				*	@param		Resource::IStream*	pData
				*	@param		CAString & strName
				*	@param		AString strVersion
				*	@note
				*
				**/
				DxVertexShader*	CreateVS(Resource::IStream*	pData,CAString&	strName,CAString&	strVersion	=	"vs_3_0");
				/**	\brief	��ȡ������ɫ
				*   
				*	@remarks 	��ȡ������ɫ
				*	@see		Shader
				*	@return   	DxPixelShader*
				*	@param		Data*	pData
				*	@param		AString & strName
				*	@param		AString strVersion
				*	@note
				*
				**/
				DxPixelShader*	CreatePS(Resource::IStream*	pData,CAString&	strName,CAString&	strVersion	=	"ps_3_0");
	
				//union{
					IDirect3DVertexShader9*	m_pVertexShader;
					IDirect3DPixelShader9*	m_pPixelShader;
				Resource::IStream*			m_pStream;
			};
	
			/**	\brief	��ɫ���Թ���
			*
			*	��ɫ���Թ���
			*
			***/
			class	Shader9Factory	:
				public	Factory{
			public:
				Shader9Factory(){
					m_strTypeName	=	"Shader";
				}
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		ShaderFactory
				*	@return   	IProduct*
				*	@param		AString& strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
			};
		}
	
	};
};
#endif // RENDERVERTEXSHADER_HEAD_FILE