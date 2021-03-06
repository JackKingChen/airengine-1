#include "AirManualMeshEntity.h"
#include "AirEngineMaterial.h"
#include "AirRenderSystem.h"

namespace	Air{
	namespace	Engine{

		AString	ManualMeshEntity::ProductTypeName	=	"ManualMeshEntity";
		ManualMeshEntity::ManualMeshEntity( CAString& strName,Info* pInfo ):MovableObject(strName)
		{
			if(pInfo!=NULL){
				m_Info	=	*pInfo;
			}

			SetNeedWorldMatrix(true);

			AddFlag(enMOF_DEFAULT			);
			AddFlag(enMOF_REFLECT			);
			AddFlag(enMOF_CASTSHADOW		);
			AddFlag(enMOF_VISIABLE			);
			AddFlag(enMOF_DYNAMIC			);
			AddFlag(enMOF_UPDATE			);
			AddFlag(enMOF_NEED_FRUSTUM_CULL	);
		}

		Air::U1 ManualMeshEntity::Create()
		{
			if(m_Info.uiVertexCount>0){
				Render::Buffer::Info	vbinfo;
				vbinfo.usage	=	Render::enUSAGE_DYNAMIC;
				vbinfo.SetVertexBuffer(m_Info.uiVertexCount,m_Info.uiVertexSize);
				m_DrawBuff.m_pVertexBuffer[0]	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer>(m_strProductName+"_VB",&vbinfo);
				m_DrawBuff.m_DrawOption.m_uiVertexCount	=	m_Info.uiVertexCount;

			}



			if(m_Info.uiIndexCount>0){
				Render::Buffer::Info	ibinfo;
				ibinfo.SetIndexBuffer32(m_Info.uiIndexCount);
				ibinfo.usage	=	Render::enUSAGE_DYNAMIC;
				m_DrawBuff.m_pIndexBuff	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer>(m_strProductName+"_IB",&ibinfo);
				m_DrawBuff.m_DrawOption.m_uiIndexCount	=	m_Info.uiIndexCount;
				m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP;

			}else{
				m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DP;
			}

			m_DrawBuff.m_pVertexDeclare	=	RenderSystem::GetSingleton()->CreateProduct<VertexDeclare>(m_strProductName+"_VD",&m_Info.vdInfo);

			
			m_DrawBuff.m_DrawOption.m_DrawType		=	m_Info.enDrawType;//Render::Draw::enPT_TRIANGLELIST;
			

			if(!m_Info.strMaterial.empty())
				SetMaterialName(m_Info.strMaterial);

			m_BoundingBox.vMin	=	Float3(-1,-1,-1);
			m_BoundingBox.vMax	=	Float3(1,1,1);
			return	true;
		}

		Air::U1 ManualMeshEntity::Destroy()
		{
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexBuffer[0]);
			SAFE_RELEASE_REF(m_DrawBuff.m_pIndexBuff);
			SAFE_RELEASE_REF(m_DrawBuff.m_pVertexDeclare);
			return	true;
		}

		void ManualMeshEntity::ProcessRenderObject( U32 uiPhaseFlag )
		{
			for(U32	i=0;i<32;i++){
				if(m_pMaterial[i]!=NULL	&&	(uiPhaseFlag&1<<i)){
					m_pMaterial[i]->AddRenderObject(this);
				}
			}
		}

		Matrix* ManualMeshEntity::GetWorldMatrix()
		{
			return	&m_WorldMatrix;
		}

		void ManualMeshEntity::UpdateVB( const void* pVB,U32 uiVertexCount )
		{
			if(m_DrawBuff.m_pVertexBuffer[0]!=NULL	&&	m_Info.uiVertexCount	>=	uiVertexCount){
				m_DrawBuff.m_pVertexBuffer[0]->Write(0,m_Info.uiVertexSize*uiVertexCount,(void*)pVB);
				m_DrawBuff.m_DrawOption.m_uiVertexCount	=	uiVertexCount;

				U32	uiPositionOffset	=	0;
				U32	uiVDElementCount	=	m_Info.vdInfo.m_vectorElement.size();
				for(U32	i=0;i<uiVDElementCount;i++){
					if(m_Info.vdInfo.m_vectorElement[i].SemanticName	==	enDU_POSITION){
						uiPositionOffset	=	m_Info.vdInfo.m_vectorElement[i].AlignedByteOffset;
						break;
					}
				}
				U8* pVB0	=	((U8*)pVB)+uiPositionOffset;
				Float3	vFirstPos	=	*(Float3*)pVB0;
				m_BoundingBox.vMin	=	vFirstPos;
				m_BoundingBox.vMax	=	vFirstPos;
				for(U32	i=1;i<uiVertexCount;i++){
					pVB0+=m_Info.uiVertexSize;
					Float3*	p	=	(Float3*)pVB0;
					m_BoundingBox.Add(*p);
				}
			}
		}

		void ManualMeshEntity::UpdateIB( const void* pIB,U32 uiIndexCount )
		{
			if(m_DrawBuff.m_pIndexBuff!=NULL	&&	m_Info.uiIndexCount	>=	uiIndexCount){
				m_DrawBuff.m_pIndexBuff->Write(0,sizeof(U32)*uiIndexCount,(void*)pIB);
				m_DrawBuff.m_DrawOption.m_uiIndexCount	=	uiIndexCount;
			}
		}

		void ManualMeshEntity::SetPrimitiveType( Render::Draw::enumPrimitiveType t )
		{
			m_DrawBuff.m_DrawOption.m_DrawType	=	t;
		}

		void ManualMeshEntity::SetIndexCount( U32 uiCount )
		{
			m_Info.uiIndexCount	=	uiCount;
			m_DrawBuff.m_DrawOption.m_uiIndexCount	=	uiCount;
		}

	}
}