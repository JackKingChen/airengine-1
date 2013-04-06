#include "AirPipelineVoxelGen.h"
#include "AirEngineSystem.h"
#include "AirEngineCamera.h"
#include "AirEngineMaterial.h"
#include "AirMeshEntity.h"

namespace	Air{
	namespace	Engine{
		struct Voxel{
			Voxel(){
				uiMask		=	0;
				uiOffset	=	0;
				uiColor		=	0;
			};
			U32 uiMask:8;
			U32	uiOffset:24;
			U32	uiColor;
		};


		struct VoxelTree{
			VoxelTree(){
				vecVoxel.resize(1);
			};
			U32	Add(const Float3& vPos,U32	uiColor,Voxel* pVoxle	=	NULL,BoundingBox*	pBoundingBox=NULL,int iLevel	=	0){

				if(iLevel	==	0){
					pVoxle	=	&vecVoxel[0];
				}
				if(iLevel>15){
					if(pVoxle->uiColor==0)
						pVoxle->uiColor	=	uiColor;
					return iLevel;
				}
				if(pBoundingBox==NULL)
					pBoundingBox	=	&m_Bound;
				Float3 vSize	=	pBoundingBox->GetHalfSize();
				Float3 vCenter	=	pBoundingBox->GetCenter();
				int x	=	vPos.x > vCenter.x;
				int y	=	vPos.y > vCenter.y;
				int z	=	vPos.z > vCenter.z;
				int idx	=	(x<<2) | (y <<1) | z;

				if(pVoxle->uiMask==0){
					pVoxle->uiOffset	=	vecVoxel.size();
					pVoxle->uiMask|=idx;
					int Offset	=	pVoxle->uiOffset;
					pVoxle=NULL;
					vecVoxel.resize(Offset + 8);
					pVoxle	=	&vecVoxel[Offset+idx];
				}else{
					pVoxle->uiMask|=idx;
					int Offset	=	pVoxle->uiOffset;
					pVoxle	=	&vecVoxel[Offset+idx];
				}

				Float3 vHalfSize	=	vSize*0.5f;
				Float3 vMin			=	(vCenter-vSize)+vSize*Float3(x,y,z);

				BoundingBox box(vMin,vMin+vSize);
				Add(vPos,uiColor,pVoxle,&box,iLevel+1);

			};
			std::vector<Voxel>	vecVoxel;;
			BoundingBox			m_Bound;
		};

		VoxelGenerator::VoxelGenerator()
		{
			m_pVoxel			=	NULL;
			m_pNodeTree			=	NULL;
			m_pGenVoxelTree		=	NULL;
			m_pMipVoxelTree		=	NULL;
			m_pRT				=	NULL;
		}

		Air::U1 VoxelGenerator::Initialize( Render::Window* pMainWindow )
		{
			RenderTarget::Info rtinfo;
			rtinfo.SetSingleTarget(256,256,enTFMT_R8G8B8A8_UNORM);

			m_pRT		=	RenderSystem::GetSingleton()->CreateProduct<Render::Target*>("SVO_Test","Target",&rtinfo);

			Render::Buffer::Info info;
			info.SetStructureBuffer(1048576,sizeof(U32));
			info.SetViewFlag(enVF_SRV|enVF_UAV|enVF_Counter);
			m_pVoxel	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer*>("SVO_Counter","Buffer",&info);
			
			info.SetByteAddressBuffer(1048576,sizeof(U32));
			info.SetViewFlag(enVF_SRV|enVF_UAV);
			m_pNodeTree	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer*>("SVO_Octree","Buffer",&info);
			
			m_pCamera	=	EngineSystem::GetSingleton()->CreateProduct<Camera*>("SVO_Camera","Camera");
			m_pCamera->SetDir(0,0,1);
			m_pCamera->SetWidth(256);
			m_pCamera->SetHeight(256);
			m_pCamera->SetOrtho(true);
			m_pCamera->SetPosition(0,0,-128);

			m_pGenVoxelTree	=	EngineSystem::GetSingleton()->CreateProduct<Material*>("SVO_Build_NoSkin","Material");	//"SVO_Test"

			m_pRT->AddCamera(m_pCamera);
			return true;
		}

		Air::U1 VoxelGenerator::Release()
		{
			SAFE_RELEASE_REF(m_pVoxel);
			SAFE_RELEASE_REF(m_pNodeTree);
			SAFE_RELEASE_REF(m_pCamera);
			SAFE_RELEASE_REF(m_pGenVoxelTree);
			SAFE_RELEASE_REF(m_pRT);
			return true;
		}

		void VoxelGenerator::Update( Renderable* pRenderable )
		{
			static MeshEntity*	pEnt = NULL;
			if(pEnt==NULL){
				MeshEntity::Info	info;
				info.strMaterial	=	"SVO_Test";
				info.strMeshName	=	"AirMesh/TEAPOT.AME";
				pEnt	=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity*>(info.strMeshName,"MeshEntity",&info);;
				pEnt->GetWorldMatrix()->m00	=	2.0f;
				pEnt->GetWorldMatrix()->m11	=	2.0f;;
				pEnt->GetWorldMatrix()->m22	=	2.0f;;

			}
#if 1
			Render::Device* pDevice	=	RenderSystem::GetSingleton()->GetDevice();
			
			pDevice->SetVP(0,0,256,256);

			m_pCamera->Render2D(256,256);
			m_pRT->SetClearFlag(true,true,true);
			if(m_pRT->BeforeUpdate()){

				void* pRTV[1]={m_pRT->GetRTV()};
				void* pDSV=NULL;
				void* pUAV[2]={m_pVoxel->GetUAV(),m_pNodeTree->GetUAV()};
				U32	clearValue[4]={0};
				pDevice->ClearUAV(pUAV[1],clearValue);
				pDevice->SetRTV_DSV_UAV(1,pRTV,pDSV,1,2,pUAV,0);


				if(m_pGenVoxelTree)
					m_pGenVoxelTree->RenderOneObject(pEnt);
				m_pRT->AfterUpdate();
			}
#else


			m_pRT->SetClearFlag(true,true,true);
			if(m_pRT->BeforeUpdate()){
				m_pCamera->Render2D(256,256);

				m_pGenVoxelTree->RenderOneObject(pEnt);

				m_pRT->AfterUpdate();
			}

#endif
		}

	}
}