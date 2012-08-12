#ifndef COMMONPLUGINMANAGER_HEAD_FILE
#define COMMONPLUGINMANAGER_HEAD_FILE
#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
namespace Air{
	
	namespace Common{
		typedef		U1(*Func)(void*);
	
		/**	\brief	��������ӿ���
		*
		*	��������ӿ���
		*
		***/
		class	IPlugin{
		public:
			virtual	~IPlugin(){};
			/**	\brief	��ʼ��
			*   
			*	@remarks 	��ʼ��
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Initialization(){return	true;};
			/**	\brief	��ʼ
			*   
			*	@remarks 	��ʼ
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Start(){return	true;};
			/**	\brief	ֹͣ
			*   
			*	@remarks 	ֹͣ
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Stop(){return	true;};
			/**	\brief	�ͷ�
			*   
			*	@remarks 	�ͷ�
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Release(){return	true;};
		};
		/**	\brief	�������
		*
		*	�������
		*
		***/
		class	COMMON_EXPORT	Plugin	:	public	IProduct{
		public:
			/**	\brief	�����������
			*
			*	�����������
			*
			***/
			enum	enumFuncType{
				enInit,
				enStart,
				enStop,
				enRelease,
				enMax
			};
		public:
			Plugin(CAString& strName,void*	pParam);
			virtual ~Plugin();
	
			/**	\brief	�������
			*   
			*	@remarks 	�������
			*	@see		Plugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Create();
	
			/**	\brief	�ݻٲ��
			*   
			*	@remarks 	�ݻٲ��
			*	@see		Plugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Destroy();
	
			/**	\brief	ִ�в������
			*   
			*	@remarks 	ִ�к���
			*	@see		Plugin
			*	@return   	U1
			*	@param		enumFuncType funcType
			*	@note
			*
			**/
			virtual	U1	Excute(enumFuncType	funcType);
	
			/**	\brief	��ȡ����
			*   
			*	@remarks 	��ȡ����
			*	@see		Plugin
			*	@return   	Common::Func
			*	@param		AString strName
			*	@note
			*
			**/
			virtual	Func	GetFunction(AString	strName);
		public:
			void*		m_pParam;
			Func		m_Func[enMax];
		};
		class	COMMON_EXPORT	PluginFactory	:
			public	IFactory{
		public:
			PluginFactory();
	
			/**	\brief	�������
			*   
			*	@remarks 	�������
			*	@see		PluginFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam = NULL);
	
		};
		
	
	};
};
#endif // COMMONPLUGINMANAGER_HEAD_FILE