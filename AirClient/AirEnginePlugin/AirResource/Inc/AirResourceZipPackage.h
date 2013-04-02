#ifndef RESOURCEZIPPACKAGE_HEAD_FILE
#define RESOURCEZIPPACKAGE_HEAD_FILE

#include "AirResourceHeader.h"

// Forward declaration for zziplib to avoid header file dependency.
typedef struct zzip_dir		ZZIP_DIR;
typedef struct zzip_file	ZZIP_FILE;
namespace Air{
	
	namespace Engine{
	
	
	
	
		namespace Resource {
	
			/**	\brief	ZIP��Դ��
			*
			*	ZIP��Դ��
			*
			***/
			class ZipPackage :
				public	IPackage 
			{
			protected:
				ZZIP_DIR* mZzipDir;		///<	ZIP��Դ��ָ��
	
				/**	\brief	���ZIP����
				*   
				*	@remarks 	���ZIP����
				*	@see		ZipPackage
				*	@return   	void
				*	@param		int zzipError
				*	@param		const AString & operation
				*	@note
				*
				**/
				void checkZzipError(int zzipError, const AString& operation) const;
			public:
				ZipPackage(CAString& name);
	
				/**	\brief	������Դ��
				*   
				*	@remarks 	������Դ��
				*	@see		ZipPackage
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Create();
	
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		ZipPackage
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Destroy();
	
				/**	\brief	�����ļ�
				*	
				*	@remarks 	�����ļ�
				*	@see		ZipPackage
				*	@return   	Data*
				*	@param		CAString & filename
				*	@note
				*
				**/
				virtual	U32		Find(CAString& filename,Data&	data);
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
			};
	
			/**	\brief	ZIP��Դ������
			*
			*	ZIP��Դ������
			*
			***/
			
			class ZipPackageFactory	: 
				public IFactory
			{
			public:
				ZipPackageFactory(){
					m_strTypeName	=	"zip";
				};
	
				/**	\brief	������Դ��
				*   
				*	@remarks 	������Դ��
				*	@see		ZipPackageFactory
				*	@return   	IProduct*
				*	@param		AString strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */){
					if(strName.empty())
						return	NULL;
					return	new	ZipPackage(strName);
				};
			};
		}
	};
};

#endif // RESOURCEZIPPACKAGE_HEAD_FILE
