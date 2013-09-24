#ifndef RENDERSHADER_HEAD_FILE
#define RENDERSHADER_HEAD_FILE

#include "AirRenderHeader11.h"
#include "AirRenderShader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Render{
			typedef	std::map<AString,DxVertexShader*>	VertexShaderMap;
			typedef	std::map<AString,DxPixelShader*>	PixelShaderMap;
			/**	\brief	������ɫ����
			*
			*	������ɫ����
			*
			***/
			class	Shader11	:	public	Shader{
			public:
				Shader11(CAString&	strName);
	
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
	

				virtual	U1				IsFileUpdate();
				virtual	void*			GetShader();
				virtual	void			GetBinaryCode(void*&	pOut,U32&	uiSize);
				virtual	enumShaderType	GetType();

			private:
				void*					m_pDxShader;
				Resource::Stream*		m_pStream;
				enumShaderType			m_ShaderType;
				enumSystemVersion		m_ShaderVersion;
				ID3DBlob*				m_pBinaryCode;
				SYSTEMTIME				m_CompileTime;
			};
		}
	
	};
};
#endif // RENDERVERTEXSHADER_HEAD_FILE