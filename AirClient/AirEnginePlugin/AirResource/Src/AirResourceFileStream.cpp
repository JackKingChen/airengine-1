// #include "AirResourceFileStream.h"
// #include "AirResourcePackageManager.h"
// 
// namespace	Air{
// 	namespace	Client{
// 		namespace	Resource{
// 
// 
// 			Air::U1 FileStream::Create(){
// 				//�����ļ�
// 				Data*	pData	=	PackageManager::GetSingleton()->Find(m_strProductName);
// 
// 				if(pData==NULL)
// 					return	false;
// 				
// 				if(pData->GetSize()	==	0){
// 					SAF_D(pData);
// 					return	false;
// 				}
// 				//����ռ�
// 				m_Data.ReSize(pData->GetSize());
// 
// 				//��������
// 				memcpy(m_Data.GetBuff(),pData->GetBuff(),pData->GetSize());
// 
// 				SAF_D(pData);
// 
// 				return	true;
// 			}
// 		}
// 	}
// }