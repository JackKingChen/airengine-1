/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InterfalHell	Xinhe
 \date      2011/04/23
 \version   ver 0.6.0.0
 \filepath  f:\EngineSource\Air\AirClient\AirEnginePlugin\AirResource
 \filename  ResourceFolderPackage.h
 \note     
       
 \attention:
			
 \remarks    created by InterfalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef RESOURCEFOLDERPACKAGE_HEAD_FILE
#define RESOURCEFOLDERPACKAGE_HEAD_FILE

#include "AirResourceHeader.h"

namespace	Air{
	namespace Client{
	
		namespace	Resource{
			/**	\brief	�ļ���
			*
			*	�ļ���
			*
			***/
			class	FolderPackage	:
				public	IPackage,
				public	File::TraversalCallBack{
			public:
				FolderPackage(CAString&	strName);

				virtual	U1	Create();
				virtual	U1	Destroy(){return	true;};

				/**	\brief	�����ļ�
				*	
				*	@remarks 	�����ļ�
				*	@see		ZipPackage
				*	@return   	Data*
				*	@param		AString & filename
				*	@note
				*
				**/
				virtual	U32			Find(CAString&	strName,Data&	data);
				U32					FindWithFullPath(CAString& filename,Data&	data);
				/**	\brief	���Һ�׺���ļ�
				*   
				*	@remarks 	���Һ�׺���ļ�
				*	@see		ISystem
				*	@return   	void
				*	@param		AString& strPostfix
				*	@param		IFindFileListener * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener);
				/**	\brief	�����ҵ��ļ�֮��
				*   
				*	@remarks 	�����ҵ��ļ�֮��
				*	@see		TraversalCallBack
				*	@return   	Air::U1
				*	@param		AString & strName
				*	@note
				*
				**/
				virtual	U1		OnFindFile(CAString&	strName);
				/**	\brief	�����ҵ��ļ���֮��
				*   
				*	@remarks 	�����ҵ��ļ���֮��
				*	@see		TraversalCallBack
				*	@return   	Air::U1
				*	@param		AString & strName
				*	@note
				*
				**/
				virtual	U1		OnFindDirectory(CAString&	strName);

			protected:
				AString				m_strTempPostfix;
				AString				m_strRealPath;
				IFindFileListener*	m_pTempListener;
			};
			/**	\brief	�ļ��й���
			*
			*	�ļ��й���
			*
			***/
			class	FolderPackageFactory	:
				public	IFactory{
			public:
				FolderPackageFactory(){
					m_strTypeName	=	"Folder";
				}
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */){
					return	new	FolderPackage(strName);
				};
			};
		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // RESOURCEFOLDERPACKAGE_HEAD_FILE