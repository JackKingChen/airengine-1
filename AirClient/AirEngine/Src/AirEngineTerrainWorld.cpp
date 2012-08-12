#include "AirEngineTerrainWorld.h"
#include "AirCommonFile.h"
#include "AirCommonIniFile.h"
#include "AirCommonConverter.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"

namespace Air{
	
	
	namespace Client{
	
		
			namespace	Terrain{
	
	
	
				World::World(){
					m_bIsLoad		= false;
					//��������
// 					IndexBuff::Info indexInfo(64*64*12);
// 					m_Info.pIndexBuff		=	Client::Render::System::GetSingleton()->Create<IndexBuff*>(AString("TerrainIndex","IndexBuff",&indexInfo);
// 					UpdataIndex();
// 					//������������
// 					VertexDeclare::Info vertexdecInfo;
// 					m_Info.pVertexDeclare	=	Client::Render::System::GetSingleton()->Create<VertexDeclare*>("XYZ|NOR|TEX1","VertexDeclare",&vertexdecInfo);
// 					//����ˮ����
// 					m_Info.pWaterMaterial	=	Client::Render::System::GetSingleton()->Create<Material*>("TerrainWater.Material","Material");
// 	
	
	
				}
	
				World::~World(){
					if(m_Info.pIndexBuff!=NULL){
						Render::System::GetSingleton()->DestroyProduct(m_Info.pIndexBuff);
						m_Info.pIndexBuff=NULL;
					}
					if(m_Info.pVertexDeclare!=NULL){
						Render::System::GetSingleton()->DestroyProduct(m_Info.pVertexDeclare);
						m_Info.pVertexDeclare=NULL;
					}
					if(m_Info.pWaterMaterial!=NULL){
						Render::System::GetSingleton()->DestroyProduct(m_Info.pWaterMaterial);
						m_Info.pWaterMaterial=NULL;
					}
				}
	
				U1 World::Load( AChar* strName ){
					if(strName==NULL){
						return false;
					}else{
						UnLoad();
						LoadInfo(strName);
						Float3	pos	= GetGlobalSetting().m_ShaderParam.m_vCurrentPosition;
						ID id = GetTitleIDByPosition(pos.x,pos.y);
						m_bIsLoad = ChangeTitle(id);
						//LoadTitle(index);
						return m_bIsLoad;
					}
					return true;
				}
	
				U1 World::ReLoad(){
					if(m_bIsLoad){
						UnLoad();
					}
					AChar	strName[MAX_NAME];
					strcpy_s(strName,MAX_NAME,m_Info.strName);
					return Load(strName);
				}
	
				U1 World::New(){
					return false;
				}
	
				U1 World::UnLoad(){
					if(!m_bIsLoad)
						return true;
					m_TitleArray.clear();
					m_lstLoadedTitle.clear();
					TitleMapItr	itr	=	m_mapLoadedTitle.begin();
					for(;itr!=m_mapLoadedTitle.end();itr++){
	// 					Title* pTitle	=	itr->second;
	// 					SAF_I(pTitle,UnLoad());
	// 					SAF_D(pTitle);
					}
					m_mapLoadedTitle.clear();
					m_bIsLoad	= false;
					return true;
				}
	
				U1 World::Save(){
					return false;
				}
	
				void World::Updata( ){
	
					Float3	pos	=	GetGlobalSetting().m_ShaderParam.m_vCurrentPosition;
					ID index	=	GetTitleIDByPosition(pos.x,pos.z);
					if(index.index != m_Info.CurrentTitleID.index){
						ChangeTitle(index);
					}
	
	
					
	
					UpdataTitle();
				}
	
				void World::Render( ){
					RenderSky();
					RenderTerrain();
					RenderGrass();
					RenderWater();
					RenderAlphaObject();
	
				}
	
				U1 World::LoadTitle( ID titleID){
					return	false;
					
				}
	
				U1 World::UnLoadTitle( ID  titleID){
	
	
					return false;
				}
	
				U1 World::LoadInfo(AChar* strName){
					strcpy_s(m_Info.strName,MAX_NAME,strName);
	
					AChar	strCfgName[MAX_NAME];
					sprintf_s(strCfgName,MAX_NAME,"%s/Config.cfg",m_Info.strName);
	
					File file(strCfgName);
					file.Open();
					IniFile cfgFile;
	
					cfgFile.LoadFileFromMemory(file.GetData());
					AString	strTitleSize	=	cfgFile.Get("Map","TitleSize");
					AString	strPageSize		=	cfgFile.Get("Map","PageSize");
					AString	strWidth		=	cfgFile.Get("Map","Width");
					AString	strHeight		=	cfgFile.Get("Map","Height");
					AString	strRenderType	=	cfgFile.Get("Map","RenderType");
					AString	strCacheTitle	=	cfgFile.Get("Map","CacheTitle");
	
					Title::Size					=	Converter::ToS32(strTitleSize);
					Page::Size					=	Converter::ToS32(strPageSize);
					m_Info.WorldSize.width		=	Converter::ToS32(strWidth);
					m_Info.WorldSize.height		=	Converter::ToS32(strHeight);
					m_Info.iRenderType			=	Converter::ToS32(strRenderType);
					m_Info.iCacheTitle			=	Converter::ToS32(strCacheTitle);
					
					m_TitleArray.resize(m_Info.WorldSize.width*m_Info.WorldSize.height);
					memset(&m_TitleArray[0],0,sizeof(UInt)*m_TitleArray.size());
	
	// 				m_pTitleArray	= new Title[m_Info.WorldSize.width*m_Info.WorldSize.height];
	// 
	// 				for(SInt j	= 0;j<m_Info.WorldSize.height;j++){
	// 					for(SInt i	= 0;i<m_Info.WorldSize.width;i++){
	// 						Title& pTitle	= m_pTitleArray[m_Info.WorldSize.width*j + i];
	// 						pTitle.SetInfo(&m_Info,i,j);
	// 					}
	// 				}
					return true;
				}
	
				U1 World::ChangePosition( Real x,Real y  ){
					if(m_bIsLoad){
						ID	index	=	GetTitleIDByPosition(x,y);
						if(index.index !=m_Info.CurrentTitleID.index)
							return ChangeTitle(index);
					}
					return false;
				}
	
				U1 World::RenderSky( ){
	
					return false;
				}
	
				U1 World::RenderTerrain( ){
					UInt	titleCacheSize	=	m_Info.iCacheTitle*2 + 1;
					for(UInt j	= 0;j<titleCacheSize;j++){
						for(UInt i	= 0;i<titleCacheSize;i++){
							Title*	pTitle	= m_TitleArray[j*titleCacheSize + i];
							if(pTitle==NULL)
								continue;
	// 						if(pTitle->IsInView()){
	// 							pTitle->Render();
	// 						}
						}
					}
					return true;
				}
	
				U1 World::RenderObject( ){
	
					return false;
				}
	
				U1 World::RenderGrass( ){
	
					return false;
				}
	
				U1 World::RenderWater( ){
	
					return false;
				}
	
				U1 World::RenderAlphaObject( ){
	
					return false;
				}
	
				bool World::GetHeight( Real x,Real y, Real* z /*= NULL*/ ){
					ID	index	=	GetTitleIDByPosition(x,y);
	
					if(	index.width		>= m_Info.WorldSize.width	||
						index.width		< 0							||
						index.height	>=	m_Info.WorldSize.height	||
						index.height	< 0){
							return false;
					}
					//���Ѽ��صĵ��ο��� ��ѯ�Ƿ��иõ��ο�
					TitleMapItr	itr	=	m_mapLoadedTitle.find(index.index);
					if(itr==m_mapLoadedTitle.end())
						return false;
	
					Title* pTitle	= itr->second;
	 				if(pTitle==NULL)
	 					return false;
					return pTitle->GetHeight(	x - (Real)(index.width*Title::Size*Page::Size),
												y - (Real)(index.height*Title::Size*Page::Size),
												z);
				}
	
				U1 World::ChangeTitle( ID currentTitleID ){
	
					m_Info.CurrentTitleID	=	currentTitleID;
	
					UInt	uiTitleEdgeSize	=	2*m_Info.iCacheTitle+1;
	
					TitleMapItr	itr;
	
					SInt uiIndexTitle	=	0;
	
					for(SInt	j	=	m_Info.CurrentTitleID.height	- m_Info.iCacheTitle;
						j			<	m_Info.CurrentTitleID.height	+ m_Info.iCacheTitle + 1;
						j++){
							for(SInt i	=m_Info.CurrentTitleID.width	-	m_Info.iCacheTitle;
								i		<m_Info.CurrentTitleID.width	+	m_Info.iCacheTitle + 1;
								i++){
									//�����߽粻����
									if(	i	>=	m_Info.WorldSize.width	||
										j	>=	m_Info.WorldSize.height	||
										i	<	0						||
										j	<	0){
											uiIndexTitle++;
											m_TitleArray[uiIndexTitle]	=	NULL;
											continue;
									}
									Title*	pTitle	=	NULL;
									ID	index(i,j);
									//�ж��Ƿ�������Ѽ����б���	����ת����Ⱦ�б���
									itr	=	m_mapLoadedTitle.find(index.index);
									if(itr!=m_mapLoadedTitle.end()){
										pTitle	=	itr->second;
										//m_mapLoadedTitle.erase(itr);
										//���Ϊ�� ��Newһ��
										if(pTitle==NULL){
											pTitle	=	new	Title();
											//pTitle->SetInfo(&m_Info,index);
											m_TitleArray[uiIndexTitle]	=	pTitle;
										}									
										//���õ��ο����β��
										m_lstLoadedTitle.remove(pTitle);
										m_lstLoadedTitle.push_back(pTitle);
									}else{
										//����������������б�	�½�һ��
										pTitle	=	new	Title();
										//pTitle->SetInfo(&m_Info,index);
										m_TitleArray[uiIndexTitle]	=	pTitle;
	
										//���������б���
										m_mapLoadedTitle.insert(TitleMapPair(index.index,pTitle));
										m_lstLoadedTitle.push_back(pTitle);
									}
								uiIndexTitle++;
	
							}
					}
					//�л���ǰ���ο�ID
					m_Info.CurrentTitleID	=	currentTitleID;
					return true;
				}
	
				U1 World::UpdataTitle(){
					
					UInt	titleCacheSize	=	m_Info.iCacheTitle*2 + 1;
	
					//�ȸ��µ�ǰ���ο�
					//��Ϊ��Ҫ���µ�ǰ����ҳ��ID
					Title*	pCurrentTitle	=	m_TitleArray[titleCacheSize*m_Info.iCacheTitle +m_Info.iCacheTitle];
					SAF_I(pCurrentTitle,Updata());
	
					//�ٸ���������
					for(UInt j	= 0;j<titleCacheSize;j++){
						for(UInt i	= 0;i<titleCacheSize;i++){
							Title*	pTitle	= m_TitleArray[j*titleCacheSize + i];
							if(pCurrentTitle!=pTitle && pTitle!=NULL)
								pTitle->Updata();
						}
					}
					return true;
				}
	
				U1 World::UpdataIndex(){
					
					UInt	uiMaxEdge	=	64;
					UInt	uiIndex[]	=	{	uiMaxEdge*uiMaxEdge*12,
												uiMaxEdge*uiMaxEdge*12/4,
												uiMaxEdge*uiMaxEdge*12/16,
												uiMaxEdge*uiMaxEdge*12/64
					};
	
					WORD* pIndex	=	NULL;
					
// 					Client::Render::LockOption option(0,uiIndex[0] /*+ uiIndex[1] + uiIndex[2] + uiIndex[3]*/ ,(void**)&pIndex);
// 					m_Info.pIndexBuff->Lock(option);
// 					//��߾�������
// 					for(UInt j=0;j<uiMaxEdge;j++){
// 						for(UInt i=0;i<uiMaxEdge;i++){
// 							*pIndex++	=	j		*	(uiMaxEdge+1)	+	i;
// 							*pIndex++	=	j		*	(uiMaxEdge+1)	+	i	+	1;
// 							*pIndex++	=	(j+1)	*	(uiMaxEdge+1)	+	i;
// 	
// 							*pIndex++	=	j		*	(uiMaxEdge+1)	+	i	+	1;
// 							*pIndex++	=	(j+1)	*	(uiMaxEdge+1)	+	i	+	1;
// 							*pIndex++	=	(j+1)	*	(uiMaxEdge+1)	+	i;
// 						}
// 					}
	
	// 				//�и߾�������
	// 				for(UInt j=0;j<uiMaxEdge;j+=2){
	// 					for(UInt i=0;i<uiMaxEdge;i+=2){
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i;
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i	+	2;
	// 						*pIndex++	=	j	*	(uiMaxEdge+2)	+	i;
	// 
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i	+	2;
	// 						*pIndex++	=	j	*	(uiMaxEdge+2)	+	i	+	2;
	// 						*pIndex++	=	j	*	(uiMaxEdge+2)	+	i;
	// 					}
	// 				}
	// 
	// 				//�о�������
	// 				for(UInt j=0;j<uiMaxEdge;j+=4){
	// 					for(UInt i=0;i<uiMaxEdge;i+=4){
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i;
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i	+	4;
	// 						*pIndex++	=	j	*	(uiMaxEdge+4)	+	i;
	// 
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i	+	4;
	// 						*pIndex++	=	j	*	(uiMaxEdge+4)	+	i	+	4;
	// 						*pIndex++	=	j	*	(uiMaxEdge+4)	+	i;
	// 					}
	// 				}
	// 				//�;�������
	// 				for(UInt j=0;j<uiMaxEdge;j+=8){
	// 					for(UInt i=0;i<uiMaxEdge;i+=8){
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i;
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i	+	8;
	// 						*pIndex++	=	j	*	(uiMaxEdge+8)	+	i;
	// 
	// 						*pIndex++	=	j	*	uiMaxEdge		+	i	+	8;
	// 						*pIndex++	=	j	*	(uiMaxEdge+8)	+	i	+	8;
	// 						*pIndex++	=	j	*	(uiMaxEdge+8)	+	i;
	// 					}
	// 				}
//					m_Info.pIndexBuff->Unlock();
	
					return true;
				}
			}
	}
};