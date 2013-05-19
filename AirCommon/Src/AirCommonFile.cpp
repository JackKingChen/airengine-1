#include "AirCommonFile.h"
#include "AirCommonPackage.h"
namespace Air{
	
	namespace	Common{
	
		static SInt	g_FileCount	=	0;
	
		File::File(){
			m_uiLength	= 0;
			g_FileCount++;
			//AChar c[128];
			//sprintf(c,"File Ref Count ==%d !\n",g_FileCount);
			//OutputDebugStringA(c);
		}
	
		File::File( CAString& strName ){
			m_strName	= strName;
			m_uiLength	= 0;
			g_FileCount++;
			//AChar c[128];
			//sprintf(c,"File Ref Count ==%d !\n",g_FileCount);
			//OutputDebugStringA(c);
		}
	
		File::~File(){
			Clear();
			g_FileCount--;
			//AChar c[128];
			//sprintf(c,"File Ref Count ==%d !\n",g_FileCount);
			//OutputDebugStringA(c);
		}
	
		U1 File::Open(Package*	pPackage,enFileType	iType){
			//�ж��ļ����Ƿ�Ϊ��
			if(m_strName.empty())
				return	false;
	
			//���Դ���Դ����
			if(pPackage!=NULL	&&	OpenFromPackage(pPackage))
				return true;
	
			//���ļ�(�Զ�ȡ �� ������ ��ʽ)
			FILE*	f	=	NULL;
			AString	strOption;
			switch(iType){
				case	enBinary:{
					strOption	=	"rb";
					break;}
				case	enASCII:{
					strOption	=	"r";
					break;}
				default:{
					strOption	=	"rb";
					break;}
			}
			fopen_s(&f,m_strName.c_str(),strOption.c_str());
			if(f==NULL)
				return	false;
			//���ļ�ָ�� �ƶ����ļ�β
			fseek(f,0,SEEK_END);
			//��ȡ��ǰ�ļ�ָ���λ��
			U32	uiLength	=	ftell(f);
			//���ļ�ָ�� �ƶ����ļ�ͷ
			fseek(f,0,SEEK_SET);
			//�ж��ļ����ݳ���
			if(uiLength	== 0)
				return false;
			Data*	pData		=	new	Data;
			//�����ڴ�ռ�
			U8*	pBuff	=	pData->ReSize(uiLength);
			//��ȡ�ļ�����
			fread(pBuff,uiLength,1,f);
			//�ر��ļ�ָ��
			fclose(f);
			//��������
			PushData(pData);
	
			//SAF_D(pData);
			
			return	true;
		}
	
		U1 File::Save(Package*	pPackage){
			//�ж��ļ����Ƿ�Ϊ��
			if(m_strName.empty())
				return	false;
	
			//��ȡ����
			Data*	pData	= GetData();
			if(pData->IsNull())
				return false;
	
			//���ļ�(��д�� �� ������ ��ʽ)
			FILE*	f	=	NULL;
			fopen_s(&f,m_strName.c_str(),"wb");
			if(f==NULL)
				return	false;
	
			//���ļ�д������
			fwrite(pData->GetBuff(),pData->GetSize(),1,f);
			fclose(f);
			return	true;
		}
	
		U1 File::Save( CAString& strName,U8* pData,U32 uiSize ){
			if(strName.empty()	||	pData==NULL	||	uiSize	==	0)
				return	false;
			FILE*	pFile	=	fopen(strName.c_str(),"wb");
			if(pFile==NULL)
				return	false;
			fwrite(pData,uiSize,1,pFile);
			fclose(pFile);
			return	true;
		}
	
		U1 File::Save( CAString& strName,AString& strContent ){
			if(strName.empty()	||	strContent.empty())
				return	false;
			FILE*	pFile	=	fopen(strName.c_str(),"w");
			if(pFile==NULL)
				return	false;
			fwrite(strContent.c_str(),strContent.size(),1,pFile);
			fclose(pFile);
			return	true;
		}
		U1 File::PushData( Data* pData ){
			if(pData==NULL)
				return false;
			m_lstData.push_back(pData);
			m_uiLength	+=	pData->GetSize();
			return true;
		}
	
		U1 File::Clear(){
			DataListItr	i	= m_lstData.begin();
			for(;i!=m_lstData.end();i++){
				Data* pData	= (Data*)(*i);
				SAF_D(pData);
			}
			m_lstData.clear();
			m_uiLength	= NULL;
			return true;
		}
	
		Data* File::GetData(){
			if(m_uiLength==0)
				return	NULL;
			if(m_lstData.size()==1){
				DataListItr	itr	=	m_lstData.begin();
				return (Data*)(*itr);
			}
			Data*	pData	= new Data;
			//����ռ�
			U8*	pBuff	= pData->ReSize(m_uiLength);
			//��¼���ݿ� ��д�����ݵĽ���λ��
			U32	uiBuffPos	= 0;
	
			//���������б�
			DataListItr	i	= m_lstData.begin();
			for(;i!=m_lstData.end();i++){
				Data*	pTempData	= (Data*)(*i);
				if(pTempData==NULL)
					continue;
				if(pTempData->IsNull())
					continue;
				//������������
				memcpy(&pBuff[uiBuffPos],pTempData->GetBuff(),pTempData->GetSize());
				//�������ݻ���������λ��
				uiBuffPos	= pTempData->GetSize();
				SAF_D(pTempData);
				//�������ÿ�
				*i	=	NULL;
			}
			//��������б�
			m_lstData.clear();
			//�����µ����������ݿ�
			m_lstData.push_back(pData);
			return	pData;
		}
	
		U1 File::SaveAs( CAString& strAnotherName ){
			if(strAnotherName.empty())
				return false;
			ReName(strAnotherName);
			return	Save();
		}
	
		U1 File::OpenFromPackage( Package* pPackage ){
			if(m_strName.empty())
				return false;
			if(pPackage==NULL)
				return false;
			Data*	pData	= pPackage->GetFileData((S8*)m_strName.c_str());
			if(pData==NULL)
				return false;
			m_lstData.push_back(pData);
			m_uiLength	+= pData->GetSize();
			return	true;
		}
	
		U1 File::SaveToPackage( Package* pPackage ){
			if(!IsValid())
				return false;
			if(pPackage==NULL)
				return false;
	
			Data*	pData	= GetData();
			return	pPackage->AddFileFromMemery((S8*)m_strName.c_str(),pData->GetBuff(),pData->GetSize());
		}
	
		U1 File::Load( CAString& strName,Data& data ){
			if(strName.empty())
				return	false;
			FILE*	f	=	fopen(strName.c_str(),"rb");
			if(f==NULL)
				return	false;
			//���ļ�ָ�� �ƶ����ļ�β
			fseek(f,0,SEEK_END);
			//��ȡ��ǰ�ļ�ָ���λ��
			U32 uiSize	=	ftell(f);
			//���ļ�ָ�� �ƶ����ļ�ͷ
			fseek(f,0,SEEK_SET);
			//�ж��ļ����ݳ���
			if(uiSize	== 0)
				return false;

			data.ReSize(uiSize);
	
			fread(data.buff,uiSize,1,f);
			fclose(f);
	
			return	true;
		}

		Air::U1 File::FolderTraversal( CAString& strPath,TraversalCallBack* pCB ){

			//find(char * lpPath)
			{
				AChar szFind[MAX_PATH];
				WIN32_FIND_DATAA FindFileData;

				strcpy(szFind,strPath.c_str());
				strcat(szFind,"*.*");

				HANDLE hFind=::FindFirstFileA(szFind,&FindFileData);
				if(INVALID_HANDLE_VALUE == hFind)
					return	false;

				while(TRUE)
				{
					if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if(strcmp(FindFileData.cFileName,".")!=0&&strcmp(FindFileData.cFileName,"..")!=0&&strcmp(FindFileData.cFileName,".svn")!=0)
						{
							AChar szFile[MAX_PATH];
							strcpy(szFile,strPath.c_str());
							strcat(szFile,FindFileData.cFileName);
							strcat(szFile,"/");
							if(pCB!=NULL){
								pCB->OnFindDirectory(szFile);
							}
							FolderTraversal(szFile,pCB);
						}
					}
					else
					{
						if(pCB!=NULL){
							pCB->OnFindFile(strPath+FindFileData.cFileName);
						}
					}
					if(!FindNextFileA(hFind,&FindFileData))
						break;
				}
				FindClose(hFind);
			}

			return	true;
		}
	}
};