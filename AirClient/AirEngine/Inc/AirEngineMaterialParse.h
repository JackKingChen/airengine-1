#ifndef ENGINEMATERIALPARSE_HEAD_FILE
#define ENGINEMATERIALPARSE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMaterialCommon.h"
#include "AirInterfaceResourceSystem.h"
#include "AirEngineMaterial.h"
namespace Air{
	
	namespace Engine{
	
		//namespace	Render{



			typedef	std::map<AString,U32>						MaterialParamMap;			///<	���ʲ���	�ַ���תö����
			typedef	std::map<AString,MaterialTemplateInfo*>		MaterialTemplateInfoMap;	///<	������Ϣ��
			typedef	std::map<AString,Material::Info*>			MaterialInfoMap;
			typedef	std::map<AString,PassStateInfo*>			PassStateMap;				///<	ͨ��״̬��Ϣ��
			typedef	std::vector<enumParamBindType>				ParamBindTypeMap;
			typedef	std::map<AString,enumPhaseIndex>			PhaseIndexMap;
			/**	\brief	 ���ʽ���
			*
			*	���ʽ���
			*
			***/
			class	ENGINE_EXPORT	MaterialParse	:
				public	MemoryObject,
				public	Singleton<MaterialParse>{
			public:
				MaterialParse();
				virtual	~MaterialParse();
				/**	\brief	������ʽű�ģ��
				*   
				*	@remarks 	������ʽű�ģ��
				*	@see		MaterialParse
				*	@return   	void
				*	@param		Data * pData
				*	@note
				*
				**/
				void		CompileMaterialTemplate(U8*	pData,U32	uiSize);
	
				/**	\brief	����״̬
				*   
				*	@remarks 	����״̬
				*	@see		MaterialParse
				*	@return   	void
				*	@param		Data * pData
				*	@note
				*
				**/
				void		CompileState(U8*	pData,U32	uiSize);
				void		CompileMaterial(U8*	pData,U32	uiSize);
				void		CompileMaterialSet(U8*	pData,U32	uiSize);
				void		CompileMaterialParameterTable(U8*	pData,U32	uiSize);
				Material::Info*		GetMaterialInfo(CAString&	strName);
				/**	\brief	��ȡ������Ϣ
				*   
				*	@remarks 	��ȡ������Ϣ
				*	@see		MaterialParse
				*	@return   	MaterialTemplateInfo*
				*	@param		CAString& strName
				*	@note
				*
				**/
				MaterialTemplateInfo*	GetMaterialTemplateInfo(CAString&		strName);
	
				/**	\brief	��ȡ����ͨ��״̬��Ϣ
				*   
				*	@remarks 	��ȡ����ͨ��״̬��Ϣ
				*	@see		MaterialParse
				*	@return   	PassStateInfo*
				*	@param		AString strName
				*	@note
				*
				**/
				PassStateInfo*			GetPassStateInfo(CAString&	strName);

				MaterialSetInfo*		GetMaterialSetInfo(CAString&	strName);

				void					AddInfo(CAString&		strName,MaterialTemplateInfo*	pInfo);
			protected:
				/**	\brief	�������ʲ���
				*   
				*	@remarks 	�������ʲ���
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		MaterialInfo * pInfo
				*	@note
				*
				**/
				U1	ParseMaterialTemplate(StringVector&	vecWord,U32&	i,MaterialTemplateInfo*	pInfo);
				U1	ParseMaterial(StringVector&	vecWord,U32&	i,Material::Info*	pInfo);
				/**	\brief	������������
				*   
				*	@remarks 	������������
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		TechniqueInfo * pInfo
				*	@note
				*
				**/
				//U1	ParseTechnique(StringVector&	vecWord,U32&	i,TechniqueInfo*	pInfo);
				/**	\brief	����ͨ������
				*   
				*	@remarks 	����ͨ������
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		PassInfo * pInfo
				*	@note
				*
				**/
				U1	ParsePass(StringVector&	vecWord,U32&	i,PassInfo*	pInfo);
				/**	\brief	�������ʲ�������
				*   
				*	@remarks 	�������ʲ�������
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		ShaderParamInfo * pInfo
				*	@note
				*
				**/
				U1	ParseShaderParam(StringVector&	vecWord,U32&	i,ShaderParamInfo*	pInfo);
				/**	\brief	����������
				*   
				*	@remarks 	����������
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		TextureUnitInfo * pInfo
				*	@note
				*
				**/
				U1	ParseTexture(StringVector&	vecWord,U32&	i,TextureUnitInfo*	pInfo);
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		ParamBindInfo * pInfo
				*	@note
				*
				**/
				U1	ParseParam(StringVector&	vecWord,U32&	i,ParamBindInfo*	pInfo);
	
				/**	\brief	
				*   
				*	@remarks 	
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		PassStateInfo * pInfo
				*	@note
				*
				**/
				U1	ParseState(StringVector&	vecWord,U32&	i,PassStateInfo*	pInfo);
				/**	\brief	����ת��
				*   
				*	@remarks 	����ת��
				*	@see		
				*	@return   	Air::U1
				*	@param		ParamBindInfo & info
				*	@note
				*
				**/
				U1	ParamType2BindType(Render::enumParamType type,ParamBindInfo& info);
			
				MaterialParamMap	m_mapParam;
				MaterialParamMap	m_mapStencileOP;
				MaterialParamMap	m_mapBlendOP;
				MaterialParamMap	m_mapBlend;
				MaterialParamMap	m_mapTextureAddress;
				MaterialParamMap	m_mapTextureFilter;
				MaterialParamMap	m_mapDepthWriteMask;
				MaterialParamMap	m_mapFillMode;
				MaterialParamMap	m_mapCullMode;
				MaterialParamMap	m_mapFog;
				MaterialParamMap	m_mapCompare;
				MaterialParamMap	m_mapParamBindType;
				MaterialParamMap	m_mapParamBindPos;
				ParamBindTypeMap	m_vecParamBindType;
				MaterialParamMap	m_mapMaterialParamType;
	
				MaterialParamMap	m_mapRS;
			protected:
				PassStateMap				m_mapPassState;					///<	ͨ��״̬��Ϣ
				MaterialTemplateInfoMap		m_mapMaterialTemplateInfo;		///<	������Ϣ �����ҪԤ����
				MaterialInfoMap				m_mapMaterialInfo;
				PhaseIndexMap				m_mapPhaseIndex;
				MaterialSetInfoMap			m_mapMaterialSetInfo;
			};
		//}
	
	};
};
#endif // INTERFACERENDERMATERIALPARSE_HEAD_FILE