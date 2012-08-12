#ifndef INTERFACERENDERMATERIAL_HEAD_FILE
#define INTERFACERENDERMATERIAL_HEAD_FILE


//#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirInterfaceRenderCommon.h"
#include "AirCommonIniFile.h"
#include "AirInterfaceRenderEffect.h"
namespace Air{
	
	namespace Client{
	
		namespace	Render{
	
	
			/**	\brief	������Ӱ
			*
			*	������Ӱ
			*
			***/
			class	IReceiveShadowable{
			public:
				IReceiveShadowable():m_bRecevieShadow(false){};
				virtual	~IReceiveShadowable(){};
				/**	\brief	�����Ƿ������Ӱ
				*   
				*	@remarks 	�����Ƿ������Ӱ
				*	@see		ICastShadowable
				*	@return   	void
				*	@param		U1 bCastShadow
				*	@note
				*
				**/
				inline	void			SetReceiveShadow(U1	bReceiveShadow){m_bRecevieShadow	= bReceiveShadow;};
				/**	\brief	�Ƿ������Ӱ
				*   
				*	@remarks 	�Ƿ������Ӱ
				*	@see		ICastShadowable
				*	@return   	U1
				*	@note
				*
				**/
				inline	U1				IsReceiveShadow(){return m_bRecevieShadow;};
			protected:
	
				U1						m_bRecevieShadow;			///<	�Ƿ�Ͷ����Ӱ
			};
	
	
	
	
	
			/**	\brief	���ʽӿ�
			*
			*	���ʽӿ�
			*
			***/
			class	IMaterial	:	public	IReceiveShadowable{
			public:
				/**	\brief	��Ⱦ��������
				*
				*	��Ⱦ��������
				*
				***/
				enum	enumTechinqueType{
					enTECH_VERYHIGH,		///<	���Ч��
					enTECH_HIGH,			///<	�ϸ�Ч��
					enTECH_NORMAL,			///<	��ͨЧ��
					enTECH_LOW,				///<	���Ч��
					enTECH_CASTSHADOW,		///<	Ͷ����Ӱ
					enTECH_DEFEREDSHADE,	///<	�ӳ���ɫ
					enTECH_MAX				///<	max
				};
	
	
				typedef		SortMap			TechniqueInfo;
				typedef		StringVector	TechniqueParamList;
	
				typedef	stdext::hash_map<AString,enumParamType>	ParamTypeMap;
				typedef	ParamTypeMap::iterator					ParamTypeMapItr;
				typedef	ParamTypeMap::value_type				ParamTypeMapPair;
	
				/**	\brief	����
				*
				*	����
				*
				***/
				class	ENGINE_EXPORT	Technique{
				public:
					/**	\brief	����
					*
					*	����
					*
					***/
					struct	Param{
						AString					strName;			///<	������
						IEffect::ParamHandle	pHandle;			///<	�������
						enumParamType			uiType;				///<	��������
						union{
							void*					pValue;			///<	ָ������
							U1						bValue;			///<	��������
							SInt					iValue;			///<	����
							Real					fValue;			///<	����
						};
					};
					typedef	std::vector<Param>			ParamArray;		///<	��������
					typedef	ParamArray::iterator		ParamArrayItr;	///<	����������
	
					typedef	std::map<AString,Param*>		ParamMap;
					typedef	ParamMap::iterator				ParamMapItr;
					typedef	ParamMap::value_type			ParamMapPair;
	
					/**	\brief	������Ϣ
					*
					*	������Ϣ
					*
					***/
					struct	Info{
						IEffect*				pEffect;				///<	Ĭ��Ч��
						TechniqueInfo*			strConfigInfo;			///<	�����ļ��е�������Ϣ
					};
	
				public:
					Technique(AString	strName,Info*	pInfo);
	
					/**	\brief	����
					*   
					*	@remarks 	����
					*	@see		Technique
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1		Create();
					/**	\brief	�ݻ�
					*   
					*	@remarks 	�ݻ�
					*	@see		Technique
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1		Destroy();
	
					/**	\brief	���ò�������
					*   
					*	@remarks 	���ò�������
					*	@see		Technique
					*	@return   	U1
					*	@param		ParamHandle pParam
					*	@param		U1 bValue
					*	@note
					*
					**/
					virtual U1			SetParam(AString	strName,	U1		bValue);
					/**	\brief	�������β���
					*   
					*	@remarks 	�������β���
					*	@see		Technique
					*	@return   	U1
					*	@param		ParamHandle pParam
					*	@param		SInt iValue
					*	@note
					*
					**/
					virtual U1			SetParam(AString	strName,	SInt	iValue);
					/**	\brief	���ø������
					*   
					*	@remarks 	���ø������
					*	@see		Technique
					*	@return   	U1
					*	@param		ParamHandle pParam
					*	@param		Real fValue
					*	@note
					*
					**/
					virtual U1			SetParam(AString	strName,	Real	fValue);
					/**	\brief	���ò���
					*   
					*	@remarks 	���ò�����������
					*	@see		Technique
					*	@return   	U1
					*	@param		ParamHandle pParam
					*	@param		Float4 * pVector
					*	@note
					*
					**/
					virtual U1			SetParam(AString	strName,	void*	pVector,UInt uiSize);
	
					/**	\brief	������ά����
					*   
					*	@remarks 	������ά����
					*	@see		Technique
					*	@return   	U1
					*	@param		AString strName
					*	@param		Float4 v
					*	@note
					*
					**/
					virtual	U1			SetParam(AString strName,		Float4& v);
	
					/**	\brief	���þ���
					*   
					*	@remarks 	���þ���
					*	@see		Technique
					*	@return   	U1
					*	@param		AString strName
					*	@param		Float44 & pMatrix
					*	@note
					*
					**/
					virtual	U1			SetParam(AString strName,		Float44& pMatrix);
					/**	\brief	��������
					*
					*
					*	@remarks 	���ò���������
					*	@see		Technique
					*	@param		ParamHandle pParam
					*	@param		ITexture* pTexture
					*
					***/
					virtual	U1			SetParam(AString	strName,	ITexture*	pTexture);
	
					/**	\brief	��ȡ����
					*   
					*	@remarks 	��ȡ����
					*	@see		Technique
					*	@return   	void*
					*	@note
					*
					**/
					virtual	void*		GetParam(AString	strName);
	
	
					/**	\brief	��ʼ���������ͱ�
					*   
					*	@remarks 	��ʼ���������ͱ�
					*	@see		Technique
					*	@return   	void
					*	@note
					*
					**/
					static	void	InitParamTypeMap();
					/**	\brief	��ȡ��������
					*   
					*	@remarks 	��ȡ��������
					*	@see		Technique
					*	@return   	UInt
					*	@param		AString strName
					*	@note
					*
					**/
					static	enumParamType	GetParamTypeByName(AString strName);
	
					static	ParamTypeMap					m_mapParamType;
	
					/**	\brief	ʹ�øü�������Ⱦ
					*   
					*	@remarks 	ʹ�øü�������Ⱦ
					*	@see		Technique
					*	@return   	void
					*	@param		Draw::Buff drawBuff
					*	@note
					*
					**/
					void	Render(Draw::Buff drawBuff);
				protected:
					/**	\brief	��ȡ������ֵ
					*   
					*	@remarks 	��ȡ������ֵ
					*	@see		Technique
					*	@return   	U1
					*	@param		Param & p
					*	@param		AChar * strValue
					*	@note
					*
					**/
					U1	GetParamValue(Param&	p,AChar*	strValue);
	
					/**	\brief	��������б�
					*   
					*	@remarks 	��������б�
					*	@see		Technique
					*	@return   	U1
					*	@note
					*
					**/
					U1	ClearParamArray();
	
					/**	\brief	���ò���
					*   
					*	@remarks 	���ò���
					*	@see		Technique
					*	@return   	U1
					*	@param		Param & param
					*	@note
					*
					**/
					U1	SetFXParam( Param& param );
	
	
				protected:
					Info					m_Info;			///<	������Ϣ
					AString					m_strName;		///<	������
					ParamArray				m_ParamArray;	///<	�����б�
					IEffect::ParamHandle	m_pHandle;		///<	����ָ��
					ParamMap				m_mapParam;		///<	��������
	// 				U8*						pIAInputSignature;
	// 				UInt					IAInputSignatureSize;
	
				};
			public:
				virtual ~IMaterial(){};
	
				/**	\brief	��Ⱦ
				*   
				*	@remarks 	��Ⱦ
				*	@see		IMaterial
				*	@return   	void
				*	@param		Draw::Buff buff
				*	@note
				*
				**/
				virtual	void	Render(Draw::Buff	buff)		=	NULL;
	
				/**	\brief	��ȡһ������
				*   
				*	@remarks 	��ȡһ������
				*	@see		IMaterial
				*	@return   	Technique*
				*	@param		UInt uiIndex
				*	@note
				*
				**/
				virtual Technique*	GetTechnique(enumTechinqueType type 	=	enTECH_VERYHIGH)	=	NULL;
				/**	\brief	����һ������
				*   
				*	@remarks 	����һ������
				*	@see		IMaterial
				*	@return   	void
				*	@param		UInt uiIndex
				*	@note
				*
				**/
				virtual void		SetTechnique(enumTechinqueType type 	=	enTECH_VERYHIGH)	=	NULL;
				/**	\brief	��ȡ��ǰ����
				*   
				*	@remarks 	��ȡ��ǰ����
				*	@see		IMaterial
				*	@return   	Technique*
				*	@note
				*
				**/
				virtual	Technique*	GetCurrentTechnique()	=	NULL;
	
				/**	\brief	�Ƿ�ʹ��Aplha���
				*   
				*	@remarks 	�Ƿ�ʹ��Alpha���
				*	@see		IMaterial
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			IsAlphaBlend()			=	NULL;
			};
	
			typedef	Common::RefPtr<IMaterial*>	IMaterialPtr;
	
		}
	
	};
};
#endif // INTERFACERENDERMATERIAL_HEAD_FILE