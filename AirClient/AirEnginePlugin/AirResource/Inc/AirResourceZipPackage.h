#ifndef RESOURCEZIPPACKAGE_HEAD_FILE
#define RESOURCEZIPPACKAGE_HEAD_FILE

#include "AirResourceHeader.h"

// Forward declaration for zziplib to avoid header file dependency.
typedef struct zzip_dir		ZZIP_DIR;
typedef struct zzip_file	ZZIP_FILE;
namespace Air{
	
	namespace Engine{
	
	
	
	
		namespace Resource {
	
			/**	\brief	ZIP资源包
			*
			*	ZIP资源包
			*
			***/
			class ZipPackage :
				public	Package 
			{
			protected:
				ZZIP_DIR* mZzipDir;		///<	ZIP资源包指针
	
				/**	\brief	检查ZIP错误
				*   
				*	@remarks 	检查ZIP错误
				*	@see		ZipPackage
				*	@return   	void
				*	@param		int zzipError
				*	@param		const AString & operation
				*	@note
				*
				**/
				void checkZzipError(int zzipError, const AString& operation) const;
			public:
				static AString ProductTypeName;
				ZipPackage(CAString& name);
	
				/**	\brief	创建资源包
				*   
				*	@remarks 	创建资源包
				*	@see		ZipPackage
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Create();
	
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		ZipPackage
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Destroy();
	
				/**	\brief	查找文件
				*	
				*	@remarks 	查找文件
				*	@see		ZipPackage
				*	@return   	Data*
				*	@param		CAString & filename
				*	@note
				*
				**/
				virtual	U32		Find(CAString& filename,Data&	data);
				/**	\brief	查找后缀名文件
				*   
				*	@remarks 	查找后缀名文件
				*	@see		ISystem
				*	@return   	void
				*	@param		CAString& strPostfix
				*	@param		FindFileCallback * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,FindFileCallback*	pListener);
			};
		}
	};
};

#endif // RESOURCEZIPPACKAGE_HEAD_FILE
