#include "AirEngineScene.h"
#include "AirRenderSystem.h"
#include "AirRenderTarget.h"


#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"

#include "AirEngineCamera.h"
#include "AirEngineMesh.h"
#include "AirEngineMaterial.h"
#include "AirEngineSubEntity.h"
#include "AirEngineLight.h"
#include "AirEngineScreenEntity.h"
#include "AirEnginePostComposer.h"
#include "AirInterfaceParticle.h"

#include "AirEngineEntity.h"
#include "AirEngineEntityCloth.h"
#include "AirStaticMesh.h"

#include "AirEngineCharacterAnimationModel.h"
#include "AirMeshEntity.h"





namespace Air{
	
	namespace	Engine{
		SceneNode* pMNode=NULL;
		AString Scene::ProductTypeName="Scene";
		Character::Animation::Model*	pModel=NULL;
		Scene::Scene( CAString& strName ):IProduct(strName){
			m_pMainCamera				=	NULL;
			m_bShadowEnable				=	true;
			m_pSceneTarget				=	NULL;
			m_pAlphaSceneTarget			=	NULL;
			//m_pScreenMaterial			=	NULL;
			m_bRenderWithoutComposer	=	false;
			m_pScreenEntity				=	NULL;
			m_bDeferredRender			=	true;
			m_bRenderAlphaObject		=	false;
	
			//m_pDefferedMaterial			=	NULL;
			m_pDefferedResult			=	NULL;
	
			//m_pRenderQueue				=	NULL;
			
		}
	
		U1 Scene::Create(){
	
			//AddFactory(new	EntityFactory());
			//AddFactory(new	EntityClothFactory());
			

			


			MeshEntity::Info	info;
			info.strMaterial	=	"NoMaterial";
			info.strMeshName	=	"AirMesh/Teapot.AME";
 			MeshEntity*	pMesh	=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity>(info.strMeshName,&info);;
			//pMesh->SetMaterialName("OIT_TEST");

			// 			pMesh->Create();
// 			//Material*	pMaterial	=	CreateProduct<Material*>("Test2","Material");
// 			pMesh->SetMaterialName("Test2");
 			SceneNode* pNode	=	m_pRootNode.CreateChildSceneNode();
			pNode->attachObject(pMesh);
			pNode->SetScale(Float3(0.5,0.5,0.5));
			//pNode->SetPosition(Float3(-8,6.5,0));

			m_Loader.SetNode(&m_StaticNode);
			//"..\\Data\\AirMesh\\jianxia3\\jianxia3.ame.Scene"
			m_Loader.Load("AirMesh/strom/strom.ame.Scene");

			//m_pRootNode.SetScale(Float3(0.1,0.1,0.1));
			//AString	strSkele	=	"Mage.CSF";
			//Character::Resource*	pRes	=	EngineSystem::GetSingleton()->CreateProduct<Character::Resource*>("Character/Mage/","Character",&strSkele);
			Character::Animation::Model::Info cinfo;
			cinfo.strTemplate	=	"机枪兵";
			pMNode = m_pRootNode.CreateChildSceneNode();;//
			//pMNode->SetScale(Float3(10,1,10));
			//AString str[]={
			//	"walk.CAF",
			//	"stand.CAF",
			//	"stand1.CAF",
			//	"attack1.CAF",
			//	"attack2.CAF",
			//	"attack3.CAF",
			//	"dance.CAF",
			//	"fidget.CAF",
			//	"standleft.CAF",
			//	"standright.CAF"
			//};
			//for(S32 i=0;i<1;i++){
				AString strName ="1";//Common::Converter::ToString(i);
				pModel	=	EngineSystem::GetSingleton()->CreateProduct<Character::Animation::Model>(strName,&cinfo);
				pModel->SetActionState("run.CAF");//,"shootup.CAF",0.5,0);
				SceneNode*	pTemp	=	pMNode->CreateChildSceneNode();
				//pTemp->SetPosition(Float3(i%10,0,i/10)*10);
				pTemp->SetQuat(Float4(Float3(-1,0,0),1.57));
				pTemp->SetScale(Float3(10,10,10));
				pTemp->attachObject(pModel);
			//}
			
			
			
			
			//Texture*	pTex	=	Render::System::GetSingleton()->CreateProduct<Texture*>("AirMesh/agrm/ORCHANGINGTARP.dds","Texture");
			//std::vector<DWORD>	vecData;
			//vecData.resize(256*256);
			//RECT r={0,0,256,256};
			//pTex->Write(&vecData[0],1024,&r);
			//pTex->ReleaseRef();

			return	true;
		}
	
		U1 Scene::Destroy(){
			//释放渲染队列
			//SAF_D(m_pRenderQueue);
			//if()

			//m_Loader.Unload();



			m_pMainCamera=NULL;
			

			m_pRootNode.RemoveAllChild(true);
			m_DynamicNode.RemoveAllChild(true);
			m_StaticNode.RemoveAllChild(true);
			m_ParticleNode.RemoveAllChild(true);
			m_TerrainNode.RemoveAllChild(true);

			return true;
		}
	
		void Scene::Update(const FrameTime& fFrameTime){
			//判断是否需要更新渲染队列
// 			if(m_pRenderQueue->Begin()){
// 				//更新一次矩阵
// 				//m_pRootNode.Update(m_pRenderQueue);
// 				//m_pRenderQueue->End();
// 			}else{
// 				m_pRootNode.Update(NULL);
// 			}
		}
	
	
		SceneNode* Scene::GetRootNode(){
			return &m_pRootNode;
		}
	
	
		void Scene::SetMainCamera( Camera* pCamera ){
			m_pMainCamera	=	pCamera;
		}
	
		Camera* Scene::GetMainCamera(){
			return	m_pMainCamera;
		}
	
		Light* Scene::CreateLight( AString strName,Light::enumType type,U1	bCastShadow ){
			Light::Info	info;
			//if(type	!=	Light::enPoint)
			//	info.SetDirection(Float3::NEGATIVE_UNIT_Y);
			info.type	=	type;
			info.vDiff	=	Float4(1,1,1,1);
			info.vPosition	=	Float4(0,0,0,1);
			info.bCastShadow	=	bCastShadow;
			Light*	pLight	=	EngineSystem::GetSingleton()->CreateProduct<Light>(strName,&info);
			
			if(pLight!=NULL){
				m_lstLight.push_back(pLight);
				//pLight->SetScene(this);
			}
			return pLight;
		}
	
		void Scene::DestroyLight( Light* pLight ){
			if(pLight!=NULL){
				m_lstLight.remove(pLight);
				pLight->ReleaseRef();
			}
		}

	
		Camera* Scene::CreateCamera(CAString&	strName){
			Camera*	pCamera	=	EngineSystem::GetSingleton()->CreateProduct<Camera>(strName);

			return pCamera;
		}
	
		void Scene::DestroyCamera(Camera*	pCamera){
			pCamera->ReleaseRef();
		}
	


	
		void Scene::PlayParticle( AString strName,Float3 vPosition,Float3 vNormal ){
			IParticle::Info info;
			info.strParticleFile	=	strName;
			info.vVelocity			=	vNormal;
			info.vPosition			=	vPosition;
			IParticle*	pParticle	=	EngineSystem::GetSingleton()->CreateProduct<IParticle>(Number::Increase(""),&info);
			if(pParticle!=NULL)
				m_pRootNode.attachObject(pParticle);
		}
	
		void Scene::SaveTargetToFile(){
			if(m_pSceneTarget!=NULL){
// 				m_pSceneTarget->GetTexture()->SaveToFile("1");
// 				m_pAlphaSceneTarget->GetTexture()->SaveToFile("2");
			}
		}

		void Scene::FindMovableObject( Camera* pCamera ){
			m_pRootNode.FindMovableObject(pCamera);

			m_DynamicNode.FindMovableObject(pCamera);
			m_StaticNode.FindMovableObject(pCamera);
			m_ParticleNode.FindMovableObject(pCamera);
			m_TerrainNode.FindMovableObject(pCamera);
		}

		void Scene::UpdateSceneTree(const FrameTime& frameTime){
			static	Matrix	matWorld(	1,0,0,0,
										0,1,0,0,
										0,0,1,0,
										0,0,0,1);
			static	Float4	quat(0,0,0,1);
			static	Float3	scale(1,1,1);

			m_pRootNode.Update(matWorld,quat,scale,false);
			m_DynamicNode.Update(matWorld,quat,scale,false);
			//m_StaticNode.Update(true)
			m_ParticleNode.Update(matWorld,quat,scale,false);

			
		}

		SceneNode* Scene::GetDynamicSceneNode(){
			return	&m_DynamicNode;
		}

		SceneNode* Scene::GetStaticSceneNode(){
			return	&m_StaticNode;
		}

		SceneNode* Scene::GetParticleSceneNode(){
			return	&m_ParticleNode;
		}

		SceneNode* Scene::GetTerrainSceneNode(){

			return	&m_TerrainNode;
		}
	}
};