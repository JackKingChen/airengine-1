#include "AirEngineCharacterResource.h"
#include "..\..\AirCharacter\cal3d.h"
#include "AirCommonFile.h"
#include "AirCommonIniFile.h"
#include "AirSlkReader.h"
#include "AirRenderSystem.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceResourceSystem.h"
namespace Air{
	
	namespace	Client{
		namespace	Character{
	
	
			Resource::Resource( AString strName,AString	strSkeleton ):IProduct(strName){
				m_strSkeleton	=	strSkeleton;
			}
	
			Resource::~Resource(){
			}
	
			SInt Resource::LoadMesh( AString strName ,MeshHDBuffer*	pOutMeshBuff){
				if(IsNull())
					return -1;
				AString strFullName	=	m_strProductName	+	strName;
				CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
				//���������б�
				InfoMapItr	i	=	m_mapMeshInfo.find(strFullName.c_str());
				if(i!=m_mapMeshInfo.end()){
					Info&	oldInfo	=	i->second;
					//�ж��Ƿ�Ϊ�� ��Ϊ�����������ü���Ȼ�󷵻�
					if(!oldInfo.IsNull()){
						oldInfo.uiRefCount++;
					}else{
						Data*	pData	=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(m_strProductName + strName);
						if(pData==NULL)
							return	-1;
						//��������б��� ���½�����
						//oldInfo.uiID	=	pCoreMesh->loadCoreMesh(m_strProductName + strName,strName);
						oldInfo.uiID	=	pCoreMesh->loadCoreMesh(pData->GetBuff(),strName);
						//�������ɹ� ���������ü���
						if(oldInfo.uiID != -1){
							oldInfo.uiRefCount++;
						}
					}
					return oldInfo.uiID;
				}
				Data*	pData	=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(m_strProductName + strName);
				if(pData==NULL)
					return	-1;
				//��������б��� ���½�����
				//SInt	uiID	=	pCoreMesh->loadCoreMesh(m_strProductName + strName,strName);
				SInt	uiID	=	pCoreMesh->loadCoreMesh(pData->GetBuff(),strName);
				//ʧ���򷵻�-1
				if(uiID<0){
					return -1;
				}
				
				MeshHDBuffer*	pMeshBuff	=	NULL;
	
				CalCoreMesh*	pTempMesh	=	pCoreMesh->getCoreMesh(uiID);
				pMeshBuff	=	new	MeshHDBuffer;
				//����Ӳ������
				CreateHardwareBuff(pMeshBuff,pTempMesh);
	
				if(pOutMeshBuff!=NULL){
					*pOutMeshBuff	=	*pMeshBuff;
				}
	
				//�½�һ�� �������ü���
				Info	info(strFullName,uiID);
				info.uiRefCount++;
				info.pUserData	=	pMeshBuff;
				//�����б���
				m_mapMeshInfo.insert(InfoMapPair(strFullName.c_str(),info));
				//����
				return uiID;
			}
	
			U1 Resource::UnLoadMesh( AString strName ){
				//�ж��Ƿ�Ϊ�� ����ֱ�ӷ���ʧ��
				if(IsNull()	||	strName.empty())
					return false;
				AString strFullName	=	m_strProductName	+	strName;
				//���б��в���
				InfoMapItr	i	=	m_mapMeshInfo.find(strFullName.c_str());
				//���û���ҵ� ����
				if(i==m_mapMeshInfo.end()){
					return true;
				}
				Info& info	=	i->second;
				//�ҵ�֮�� �ж��Ƿ�Ϊ��
				if(info.IsNull()){
					m_mapMeshInfo.erase(i);
					return true;
				}
				//��������
				info.uiRefCount--;
				//����Ƿ�û�������ô���Դ 
				if(info.uiRefCount<=0){
					//ж��
					CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
					pCoreMesh->unloadCoreMesh(info.uiID);
					info.uiID	=	-1;
	
						MeshHDBuffer*	pMeshBuff	=	(MeshHDBuffer*)info.pUserData;
						//�ݻ�Ӳ������
						DestroyHardwareBuff(pMeshBuff);
				}
				m_mapMeshInfo.erase(i);
				return true;
			}
	
			SInt Resource::LoadAnimation( AString strName ){
				if(IsNull())
					return -1;
				CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
				//���������б�
				InfoMapItr	i	=	m_mapAnimationInfo.find(strName.c_str());
				if(i!=m_mapAnimationInfo.end()){
					Info&	oldInfo	=	i->second;
					//�ж��Ƿ�Ϊ�� ��Ϊ�����������ü���Ȼ�󷵻�
					if(!oldInfo.IsNull()){
						oldInfo.uiRefCount++;
					}else{
						//���Ϊ�� ������ 
						oldInfo.uiID	=	pCoreMesh->loadCoreAnimation(m_strProductName+strName,strName);
						//�������ɹ� ���������ü���
						if(oldInfo.uiID != -1){
							oldInfo.uiRefCount++;
						}
					}
					return oldInfo.uiID;
				}
				Data*	pData	=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(m_strProductName + strName);
				if(pData==NULL)
					return	-1;
				//��������б��� ���½�����
				//SInt	uiID	=	pCoreMesh->loadCoreAnimation(m_strProductName + strName,strName);
				SInt	uiID	=	pCoreMesh->loadCoreAnimation(pData->GetBuff(),strName);
				//ʧ���򷵻�-1
				if(uiID<0){
					return -1;
				}
				//�½�һ�� �������ü���
				Info	info(strName,uiID);
				info.uiRefCount++;
				//�����б���
				m_mapAnimationInfo.insert(InfoMapPair(strName.c_str(),info));
				//����
				return uiID;
			}
	
			U1 Resource::UnLoadAnimation( AString strName ){
				if(IsNull())
					return false;
				InfoMapItr	i	=	m_mapAnimationInfo.find(strName.c_str());
				if(i==m_mapAnimationInfo.end()){
					return true;
				}
				Info& info	=	i->second;
				if(info.IsNull()){
					return true;
				}
				info.uiRefCount--;
				if(info.uiRefCount<=0){
					CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
					pCoreMesh->unloadCoreAnimation(info.uiID);
					info.uiID	=	-1;
				}
				return true;
			}
	
			U1 Resource::Create(){
				AString	strConfigFileName	=	m_strProductName + "Animation.slk";
	
				if(!ParseConfig(strConfigFileName)){
					return false;
				}
				return true;
			}
	
			U1 Resource::Destroy(){
				m_mapAnimationInfo.clear();
				m_mapMeshInfo.clear();
				CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
				SAF_D(pCoreMesh);
				m_pObject	=	NULL;
				return true;
			}
	
			U1 Resource::ParseConfig(AString	strConfig){
	
	
				CoreMesh*	pCoreMesh	=	new	CoreMesh(m_strProductName.c_str());
				m_pObject				=	(UInt*)pCoreMesh;
	
				Data*	pData		=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(m_strProductName + m_strSkeleton);
				if(pData==NULL)
					return	false;
	
				if(!pCoreMesh->loadCoreSkeleton(pData->GetBuff())){
					SAF_D(pCoreMesh);
					return false;
				}
	
				StringVector	lstAnimation;
	
				CSlkReader r;
				pData		=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(strConfig);
				if(pData==NULL)
					return	false;
	
				if( !r.ReadFromString((char*)pData->GetBuff(),pData->GetSize() ) ){
					assert(false);
					return FALSE;
				}
	
				int nLine = 2;
				int iRet;
	
				while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
				{
					if( CSlkReader::ret_nothisline == iRet )
						continue;
	
					CSlkReader::SField* field;
		
					field = r.GetFieldOfLine( 5 );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					AString	strAnimationName	=	field->data.szValue;
	
	
					lstAnimation.push_back(strAnimationName);
				}	
	
				if(lstAnimation.empty()){
					SAF_D(pCoreMesh);
					return false;
				}
	
				for(UInt	i=0;i<lstAnimation.size();i++){
					AString	strAnimation	=	lstAnimation[i];
					LoadAnimation(strAnimation);
				}
	
				
				return true;
			}
	
			SInt Resource::GetAnimationID( AString strName ){
				InfoMapItr	i	=	m_mapAnimationInfo.find(strName.c_str());
				if(i==m_mapAnimationInfo.end()){
					return -1;
				}
				Info& info	=	i->second;
				return info.uiID;
			}
	
			U1 Resource::CreateHardwareBuff( MeshHDBuffer* pOutBuff,CalCoreMesh* pInMesh ){
				std::vector<ABuff>	vertexData;
				std::vector<UInt>								indexData;
	
				SInt	iMeshCount	=	pInMesh->getCoreSubmeshCount();
				SInt	iVertexCount	=	0;
				SInt	iIndexCount		=	0;
				//���ȼ��㶥���� �� ������
				for(SInt i=0;i<iMeshCount;i++){
					CalCoreSubmesh*	pSubMesh	=	pInMesh->getCoreSubmesh(i);
					iVertexCount	+=	pSubMesh->getVectorVertex().size();
					iIndexCount		+=	pSubMesh->getFaceCount()*3;
				}
				if(	iVertexCount	==	0	||
					iIndexCount		==	0)
				{
					return	false;
				}
				//����ռ�
				vertexData.resize(iVertexCount);
				indexData.resize(iIndexCount);
	
				SInt	iV	=	0;
				SInt	iI	=	0;
	
				
				for(SInt i=0;i<iMeshCount;i++){
					CalCoreSubmesh*	pSubMesh							=	pInMesh->getCoreSubmesh(i);
					//��������
					pSubMesh->enableTangents(0,true);
	
					std::vector<CalCoreSubmesh::Vertex>&							lstVector	=	pSubMesh->getVectorVertex();
					std::vector<std::vector<CalCoreSubmesh::TangentSpace> >&		lstTangent	=	pSubMesh->getVectorVectorTangentSpace();
					std::vector<std::vector<CalCoreSubmesh::TextureCoordinate> >&	lstTexcoord	=	pSubMesh->getVectorVectorTextureCoordinate();
					std::vector<CalCoreSubmesh::Face>&								lstFace		=	pSubMesh->getVectorFace();
					
					SInt iFaceCount	=	lstFace.size();
					//��������
					for(SInt	j=0;j<iFaceCount;j++){
						indexData[iI]	=	lstFace[j].vertexId[0]	+	iV;
						indexData[iI+1]	=	lstFace[j].vertexId[1]	+	iV;
						indexData[iI+2]	=	lstFace[j].vertexId[2]	+	iV;
						iI	+=	3;
					}
					
					//���㻺������
					for(SInt j=0;j<iVertexCount;j++){
						CalCoreSubmesh::Vertex&				ver		=	lstVector[j];
						CalCoreSubmesh::TangentSpace		tang	=	lstTangent[0][j];
						CalCoreSubmesh::TextureCoordinate	uv		=	lstTexcoord[0][j];
		
						//λ��
						vertexData[iV].Position		=	Float3(ver.position.x,ver.position.y,ver.position.z);
						//��������Ϣ
						vertexData[iV].BoneWeight	=	Float4(0,0,0,0);
						vertexData[iV].BoneIndex	=	Float4(0,0,0,0);
	// 					AChar	str[128];
	// 					sprintf_s(str,"Vertex[%d] ",j);
	// 					OutputDebugStringA(str);
						SInt	iBoneCount	=	ver.vectorInfluence.size();
						for(SInt	k=0;k<iBoneCount;k++){
// 							vertexData[iV].BoneWeight[k]	=	ver.vectorInfluence[k].weight;
// 							vertexData[iV].BoneIndex[k]	=	ver.vectorInfluence[k].boneId;
							
	// 						sprintf_s(str,128,"<%d>%f,%f",k,vertexData[iV].BoneWeight[k],vertexData[iV].BoneIndex[k]);
	// 						OutputDebugStringA(str);
						}
	//					OutputDebugStringA("\n");
						//����
						vertexData[iV].Normal		=	Float3(ver.normal.x,ver.normal.y,ver.normal.z);
						//UV
						vertexData[iV].UV.x		=	uv.u;
						vertexData[iV].UV.y		=	uv.v;
						//����
						vertexData[iV].Tangent.x		=	tang.tangent.x;
						vertexData[iV].Tangent.y		=	tang.tangent.y;
						vertexData[iV].Tangent.z		=	tang.tangent.z;
	
	
	
						iV++;
					}
					AString	strName	=	m_strProductName	+	pInMesh->getName();
					Render::Vertex::IDeclare::Info	dInfo;
					dInfo.SetPNTT_Animation();
// 					pOutBuff->pVertexDeclare	=	Render::System::GetSingleton()->Create<Render::Vertex::IDeclare*>(AString("PNTTANIM"),AString("VertexDeclare"),&dInfo);
// 					Render::Vertex::IBuff::Info		vInfo(76,iVertexCount);
// 					vInfo.InitData				=	&vertexData[0];
// 					pOutBuff->pVertexBuff		=	Render::System::GetSingleton()->Create<Render::Vertex::IBuff*>(strName,AString("VertexBuff"),&vInfo);
// 					Render::Index::IBuff::Info		iInfo(iIndexCount);
// 					iInfo.InitData				=	&indexData[0];
// 					pOutBuff->pIndexBuff		=	Render::System::GetSingleton()->Create<Render::Index::IBuff*>(strName,AString("IndexBuff"),&iInfo);
// 	
				}
				return	true;
			}
	
			U1 Resource::DestroyHardwareBuff( MeshHDBuffer* pInBuff ){
				Render::System*	pSys	=	Render::System::GetSingleton();
				if(pSys==NULL)
					return	false;
				if(pInBuff->pVertexDeclare!=NULL){
					pSys->DestroyProduct(pInBuff->pVertexDeclare);
					pInBuff->pVertexDeclare	=	NULL;
				}
				if(pInBuff->pVertexBuff!=NULL){
					pSys->DestroyProduct(pInBuff->pVertexBuff);
					pInBuff->pVertexBuff	=	NULL;
				}
				if(pInBuff->pIndexBuff!=NULL){
					pSys->DestroyProduct(pInBuff->pIndexBuff);
					pInBuff->pIndexBuff	=	NULL;
				}
				return	true;
			}
			ResourceFactory::ResourceFactory(){
				m_strTypeName	=	"CharacterResource";
			}
	
			IProduct* ResourceFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
				if( lstParam==NULL)
					return NULL;
				AString*	pStrSkeleton	=	(AString*)lstParam;
				Resource*	pBuff	=	new	Resource(strName,*pStrSkeleton);
	
				//Insert(pBuff);
				return pBuff;
			}
		}
	}
};