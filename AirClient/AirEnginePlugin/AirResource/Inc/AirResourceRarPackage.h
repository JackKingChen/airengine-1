#ifndef RESOURCEPACKAGE_HEAD_FILE
#define RESOURCEPACKAGE_HEAD_FILE

#include "AirResourceHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Resource{
			/**	\brief	��Դ��
			*
			*	��Դ��
			*
			***/
			class	RarPackage	:
				public	IPackage{
			public:
				typedef	Data	FileData;
			public:
				RarPackage(CAString&	strName);
	
				/**	\brief	���ݰ�����
				*   
				*	@remarks 	���ݰ�����
				*	@see		Package
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Create();
	
				/**	\brief	���ݰ��ݻ�
				*   
				*	@remarks 	���ݰ��ݻ�
				*	@see		Package
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Destroy();
	
				/**	\brief	������Դ
				*   
				*	@remarks 	������Դ
				*	@see		Package
				*	@return   	Data*	
				*	@param		AString & strName
				*	@note
				*
				**/
				virtual	U32			Find(CAString&	strName,Data&	data);
	
				/**	\brief	���Һ�׺���ļ�
				*   
				*	@remarks 	���Һ�׺���ļ�
				*	@see		ISystem
				*	@return   	void
				*	@param		CAString& strPostfix
				*	@param		IFindFileListener * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener);
	
				/**	\brief	�ϲ�����
				*   
				*	@remarks 	�ϲ�����
				*	@see		RarPackage
				*	@return   	Data*
				*	@note
				*
				**/
				Data*			CombineData();
	
			public:
	
			};
			/**	\brief	RAR��Դ������
			*
			*	��Դ������
			*
			***/
			class	RarPackageFactory	:
				public	IFactory
			{
			public:
				RarPackageFactory(){
					m_strTypeName	=	"rar";
				};
	
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */){
					if(strName.empty())
						return	NULL;
					return	new	RarPackage(strName);
				};
			};
		}
	
	};
};
#endif // RESOURCEPACKAGE_HEAD_FILE