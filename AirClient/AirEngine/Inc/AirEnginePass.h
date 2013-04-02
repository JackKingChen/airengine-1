/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/08
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EnginePass.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINEPASS_HEAD_FILE
#define ENGINEPASS_HEAD_FILE

#include "AirEngineShaderProgram.h"
#include "AirEngineMaterialCommon.h"

namespace	Air{
	namespace Engine{
		struct PassInfo;
		/**	\brief	ͨ��
		*
		*	ͨ��
		*
		***/
		class	ENGINE_EXPORT	Pass	:	
			public	Common::IObject{
		public:
			Pass(PassInfo*	pInfo);
			virtual	~Pass();

			/**	\brief	����PASS
			*   
			*	@remarks 	�ݻ�PASS
			*	@see		Pass
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	�ݻ�PASS
			*   
			*	@remarks 	�ݻ�PASS
			*	@see		Pass
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Destroy();

			
			/**	\brief	����Shader
			*   
			*	@remarks 	����Shader ������Ϣ�Ͳ�����Ϣ ��ShaderProgram����
			*	@see		Pass
			*	@return   	ShaderProgram*
			*	@param		ShaderParamInfo * pShaderInfo
			*	@param		Render::enumShaderType type
			*	@note
			*
			**/
			virtual	ShaderProgram*	CreateShaderProgram(ShaderParamInfo*	pShaderInfo,enumShaderType	type);
			/**	\brief	�ݻ�Shader
			*   
			*	@remarks 	�ݻ�Shader
			*	@see		Pass
			*	@return   	Air::U1
			*	@param		ShaderProgram * pShader
			*	@note
			*
			**/
			virtual	U1				DestroyShaderProgram(ShaderProgram*	pShader);
			/**	\brief	�ݻ�Shader
			*   
			*	@remarks 	�ݻ�Shader
			*	@see		Pass
			*	@return   	Air::U1
			*	@param		enumShaderType type
			*	@note
			*
			**/
			virtual	U1				DestroyShaderProgram(enumShaderType	type);

			virtual	void			UpdateTextureArray(TextureArray&	vecTexture);
			void					Begin();
			void					End();

			inline	PassHash		GetHash(){
				return	m_Hash;
			};
		protected:
			PassInfo*					m_pInfo;				///<	pass��Ϣ
			ShaderProgram*				m_pShaderArray[6];		///<	��ɫ����
			PassHash					m_Hash;

			Render::IRasterizerState*	m_pRasterizerState;		///<	��դ��״̬
			Render::IBlendState*		m_pBlendState;			///<	���״̬
			Render::IDepthStencilState*	m_pDepthStencilState;	///<	���״̬
		};


		typedef	std::vector<Pass*>		PassVector;
	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINEPASS_HEAD_FILE