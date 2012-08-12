#include "AirResourceRarPackage.h"
#include "dll.hpp"

#include "AirResourceSystem.h"

namespace Air{
	
	
	
	namespace	Client{
	
		namespace	Resource{
	
			Data*	g_TempData	=	NULL;
			U32		g_TempPos	=	0;
	
			SInt PASCAL ReceivedFunction(U8*	pData,SInt iSize){
				//��������
				memcpy(&g_TempData->buff[g_TempPos],pData,iSize);
				g_TempPos+=iSize;
				return 1;
			};
	
			RarPackage::RarPackage( CAString& strName ):IPackage(strName){
				//m_Handle	=	NULL;
	#ifndef	_DEBUG
				OutputDebugStringA(strName.c_str());
				OutputDebugStringA("\n");
	#endif
			}
	
			U1 RarPackage::Create(){
				if(m_strProductName.empty())
					return	false;
	
				RAROpenArchiveData	data;
				data.ArcName	=	(char*)m_strProductName.c_str();
				data.CmtBuf		=	NULL;
				data.CmtBufSize	=	0;
				data.CmtSize	=	0;
				data.CmtState	=	0;
				data.OpenMode	=	RAR_OM_LIST;
				data.OpenResult	=	0;
	
				//����Դ��
				HANDLE	h	=	RAROpenArchive(&data);
	
	#ifndef	_DEBUG
				//RARSetPassword(h,"InfernalHell");
	#endif
	
				RARHeaderData	DataHeader;
	
				SInt	ret	=	-1;
				//ѭ�������б� �����ļ�
				while   ((ret=RARReadHeader(h,&DataHeader))==0){
					AString	str	=	DataHeader.FileName;
					//ת��ΪСд
					Converter::ToLowerCase(str);
					FileInfo info;
					info.uncompressedSize	=	DataHeader.UnpSize;
					info.compressedSize		=	DataHeader.PackSize;
					m_mapFileInfo[str.c_str()]	=	info;
					ret	=	RARProcessFile(h,RAR_SKIP,NULL,NULL);
				}
	
				if(h!=NULL){
					int r		=	RARCloseArchive(h);
					h	=	NULL;
				}
	
	
				return	true;
			}
	
			U1 RarPackage::Destroy(){
				m_mapFileInfo.clear();
				return	true;
			}
	
			U32	RarPackage::Find( CAString& strName ,Data&	data){

				U32	uiSize	=	IsExist(strName);
				if(uiSize	==	0)
					return	0;
				data.ReSize(uiSize);
				g_TempData	=	&data;
				g_TempPos	=	0;

				RAROpenArchiveData	arc;
				arc.ArcName	=	(char*)m_strProductName.c_str();
				arc.CmtBuf		=	NULL;
				arc.CmtBufSize	=	0;
				arc.CmtSize		=	0;
				arc.CmtState	=	0;
				arc.OpenMode	=	RAR_OM_EXTRACT;
				arc.OpenResult	=	0;
	
				//����Դ��
				HANDLE	h	=	RAROpenArchive(&arc);
				RARSetProcessDataProc(h,ReceivedFunction);
	
	#ifndef	_DEBUG
				//RARSetPassword(h,"InfernalHell");
	#endif
	
				RARHeaderData	DataHeader;
	
				SInt	ret	=	-1;
				//ѭ�������б� �����ļ�
				while   ((ret=RARReadHeader(h,&DataHeader))==0)   
				{   
					AString	str	=	DataHeader.FileName;
					//ת��ΪСд
					Converter::ToLowerCase(str);
					//����������ж��ļ����Ƿ���ȷ
					if(str	!=	strName){
						//���������Ҫ���ҵ��ļ� ������������һ���ļ�
						ret	=	RARProcessFile(h,RAR_SKIP,NULL,NULL);
					}else{
						//��һ������ ����Դ�����
						//�����ĸ�����Ϊ��ѹ·�� ��ǰ���ǵڶ�������ΪRAR_EXTRACT Ȼ���ѹ(�����Ҫ��ѹ���� �������ļ�·��) NULLΪ��ѹ������Ŀ��
						//�ڶ������� ���ֻ��Ҫ��ѹ���ڴ��� ����RAR_TEST
						ret	=	RARProcessFile(h,RAR_TEST,NULL,NULL);
						if(h!=NULL){
							int r		=	RARCloseArchive(h);
							h	=	NULL;
						}
						return	data.size;//CombineData();
					}
				}
	
				if(h!=NULL){
					int r		=	RARCloseArchive(h);
					h	=	NULL;
				}
				return	NULL;
			}
	
	
			void RarPackage::FindWithPostfix( CAString& strPostfix,IFindFileListener* pListener ){

				g_TempData	=	new	Data;
				g_TempPos	=	0;

				RAROpenArchiveData	data;
				data.ArcName	=	(char*)m_strProductName.c_str();
				data.CmtBuf		=	NULL;
				data.CmtBufSize	=	0;
				data.CmtSize	=	0;
				data.CmtState	=	0;
				data.OpenMode	=	RAR_OM_EXTRACT;
				data.OpenResult	=	0;
	
				//����Դ��
				HANDLE	h	=	RAROpenArchive(&data);
				RARSetProcessDataProc(h,ReceivedFunction);
	
	#ifndef	_DEBUG
				//RARSetPassword(h,"InfernalHell");
	#endif
	
				RARHeaderData	DataHeader;
	
				SInt	ret	=	-1;
				//ѭ�������б� �����ļ�
				while   ((ret=RARReadHeader(h,&DataHeader))==0)   
				{   
					AString	strPost;
					AString	strName	=	DataHeader.FileName;
					GlobalSetting::ParsePath(DataHeader.FileName,&strPost);
					//ת��ΪСд
					Converter::ToLowerCase(strPost);
	
					//����������ж��ļ����Ƿ���ȷ
					if(strPost	!=	strPostfix){
						//���������Ҫ���ҵ��ļ� ������������һ���ļ�
						ret	=	RARProcessFile(h,RAR_SKIP,NULL,NULL);
					}else{
						g_TempData->ReSize(DataHeader.UnpSize);
						//��һ������ ����Դ�����
						//�����ĸ�����Ϊ��ѹ·�� ��ǰ���ǵڶ�������ΪRAR_EXTRACT Ȼ���ѹ(�����Ҫ��ѹ���� �������ļ�·��) NULLΪ��ѹ������Ŀ��
						//�ڶ������� ���ֻ��Ҫ��ѹ���ڴ��� ����RAR_TEST
						ret	=	RARProcessFile(h,RAR_TEST,NULL,NULL);
						//�ص�
						pListener->OnFindFile(strName,g_TempData);

					}
				}

				delete	g_TempData;
				g_TempData	=	NULL;
				g_TempPos	=	0;
	
				if(h!=NULL){
					int r		=	RARCloseArchive(h);
					h	=	NULL;
				}	
			}
	
			Data* RarPackage::CombineData(){
// 				Data*	pData	=	NULL;
// 				if(g_lstTempData.size()	==	1){
// 					std::list<Data*>::iterator	i	=	g_lstTempData.begin();
// 					pData	=	(Data*)(*i);
// 					g_uiTempDataSize	=	0;
// 					g_lstTempData.clear();
// 					return	pData;
// 				}else{
// 					pData	=	new	Data();
// 					pData->ReSize(g_uiTempDataSize);
// 					UInt	uiPos			=	0;
// 					U8*	pDataPointer		=	pData->GetBuff();
// 					std::list<Data*>::iterator	i	=	g_lstTempData.begin();
// 					for(;i!=g_lstTempData.end();i++){
// 						Data*	p	=	(Data*)(*i);
// 						memcpy(&pDataPointer[uiPos],p->GetBuff(),p->GetSize());
// 						uiPos	+=	p->GetSize();
// 						SAF_D(p);
// 					}
// 					g_uiTempDataSize	=	0;
// 					g_lstTempData.clear();
// 					return	pData;
// 				}
				return NULL;
			}
		}
	}
};