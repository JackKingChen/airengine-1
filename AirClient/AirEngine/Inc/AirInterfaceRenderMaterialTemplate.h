#ifndef INTERFACERENDERMATERIALTEMPLATE_HEAD_FILE
#define INTERFACERENDERMATERIALTEMPLATE_HEAD_FILE

#include "AirInterfaceRenderCommon.h"

namespace Air{
	
	namespace Client{
	
		namespace	Render{
			class		ITexture;
			class		IShader;
			typedef		std::vector<ITexture*>	TextureVector;
	
	
			/**	\brief	�µĲ���ϵͳ
			*
			*	�µĲ���ϵͳ
			*
			***/
			class	IMaterialTemplate{
			public:
				/**	\brief	����
				*
				*	����
				*
				***/
				class	ITechnique{
				public:
					/**	\brief	ͨ��
					*
					*	ͨ��
					*
					***/
					class	IPass{
					public:
						IPass(){
							m_pInfo		=	NULL;
						};
						
						PassInfo*	m_pInfo;
					};
					
					ITechnique(){
						m_pInfo		=	NULL;
						m_pShader	=	NULL;
					};
	
					virtual	void	Render()	=	NULL;
	
					IShader*		m_pShader;
					TechniqueInfo*	m_pInfo;
				};
	
				IMaterialTemplate(){
					m_pInfo	=	NULL;
				};
	
				MaterialTemplateInfo*	m_pInfo;	///<	������Ϣ
			};
		}
	};
};
#endif // INTERFACERENDERMATERIAL2_HEAD_FILE