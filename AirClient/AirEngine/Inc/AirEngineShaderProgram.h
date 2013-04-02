/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/08
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EngineShader.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINESHADERPROGRAM_HEAD_FILE
#define ENGINESHADERPROGRAM_HEAD_FILE

#include "AirRenderState.h"
#include "AirRenderShader.h"


namespace	Air{
	namespace Engine{
		struct ShaderParamInfo;
		/**	\brief	PASS��ɫ����
		*
		*	PASS��ɫ����
		*
		***/
		class	ENGINE_EXPORT	ShaderProgram	:
			public	Common::IObject{
		public:
			ShaderProgram(ShaderParamInfo*	pInfo,enumShaderType	type);

			
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Shader
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		Shader
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
			void		UpdateShader_SamplerState();
			void		UpdateTextureArray(TextureArray&	vecTexture);

			/**	\brief	��ȡShader������
			*   
			*	@remarks 	��ȡShader������
			*	@see		Shader
			*	@return   	Render::enumShaderType
			*	@note
			*
			**/
			inline	enumShaderType	GetShaderType(){
				return	m_Type;
			};
			inline	Shader*					GetShader(){
				return	m_pShader;
			};
		protected:

			ShaderParamInfo*			m_pInfo;
			Shader*						m_pShader;
			enumShaderType				m_Type;
			SamplerStateVector			m_vecSamplerState;
		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINESHADER_HEAD_FILE