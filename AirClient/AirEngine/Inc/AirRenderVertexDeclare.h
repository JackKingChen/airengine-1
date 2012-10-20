#ifndef AIRRENDERVERTEXDECLARE_HEAD_FILE
#define AIRRENDERVERTEXDECLARE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderCommon.h"
namespace Air{
	
	
	namespace Client{
	
		namespace	Render{
			namespace	Vertex{

	
// 				const DWORD Usage = bIsDynamic ? (D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY) : 0;
// 				const D3DPOOL Pool = bIsDynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
	

				/**	\brief	��������
				*
				*	��������
				*
				***/
				class ENGINE_EXPORT	IDeclare
					:	public	IProduct{
				public:
					/*	��������ʾ��
	
					����D3D ���е�ö�ٶ����޸���D3D
	
					Element decl[] = 
					{
					{ 0, 0 ,  DECLTYPE_FLOAT3, DECLMETHOD_DEFAULT, DECLUSAGE_POSITION,		0 },
					{ 0, 12,  DECLTYPE_FLOAT4, DECLMETHOD_DEFAULT, DECLUSAGE_BLENDWEIGHT,	0 },
					{ 0, 28,  DECLTYPE_FLOAT4, DECLMETHOD_DEFAULT, DECLUSAGE_BLENDINDICES,	0 },
					{ 0, 44,  DECLTYPE_FLOAT3, DECLMETHOD_DEFAULT, DECLUSAGE_NORMAL,		0 },
					{ 0, 56,  DECLTYPE_FLOAT2, DECLMETHOD_DEFAULT, DECLUSAGE_TEXCOORD,		0 },
					DECL_END()
					};
	
					Element HardwareDecl[] =
					{
					{ 0, 0,     DECLTYPE_FLOAT3,     DECLMETHOD_DEFAULT,  DECLUSAGE_POSITION,  0 },
					{ 0, 3 * 4, DECLTYPE_FLOAT3,     DECLMETHOD_DEFAULT,  DECLUSAGE_NORMAL,    0 },
					{ 0, 6 * 4, DECLTYPE_FLOAT2,     DECLMETHOD_DEFAULT,  DECLUSAGE_TEXCOORD,  0 },
					{ 1, 0,     DECLTYPE_D3DCOLOR,   DECLMETHOD_DEFAULT,  DECLUSAGE_COLOR,     0 },
					{ 1, 4,     DECLTYPE_D3DCOLOR,   DECLMETHOD_DEFAULT,  DECLUSAGE_COLOR,     1 },
					DECL_END()
					};
	
					UInt	uiElementSize	=	sizeof(decl)/sizeof(Element);
	
					*/
	
					/**	\brief	������Ϣ
					*
					*	������Ϣ
					*
					***/
					struct Info{
						Info(){
						};
						Info(DeclareElement* pElement,U32	uiSize){
							if(pElement==NULL || uiSize == 0)
								return;
							m_vectorElement.resize(uiSize);
							memcpy(&m_vectorElement[0],pElement,uiSize*sizeof(DeclareElement));
						};
	
	
						void	CopyElement(DeclareElement* pElement,U32	uiSize){
							UInt	uiElementSize	=	uiSize;//sizeof(pElement)/sizeof(Element);
							m_vectorElement.resize(uiElementSize);
							memcpy(&m_vectorElement[0],pElement,uiElementSize*sizeof(DeclareElement));
						}
	
						/**	\brief	����Ϊ��������
						*   
						*	@remarks 	����Ϊ��������
						*	@see		Info
						*	@return   	void
						*	@note
						*
						**/
						void	SetDeclAnimation(){
							DeclareElement decl[] = 
							{
								{ enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,		0,0,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_BLENDWEIGHT,		0,  enTFMT_R32G32B32A32_FLOAT,	0,12,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_BLENDINDICES,	0,  enTFMT_R32G32B32A32_FLOAT,	0,28,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_NORMAL,			0,  enTFMT_R32G32B32_FLOAT,		0,44,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		0,  enTFMT_R32G32_FLOAT,		0,56,	enDT_PER_VERTEX_DATA,0 },
							};
							UInt	uiElementSize	=	sizeof(decl)/sizeof(DeclareElement);
							CopyElement(decl,uiElementSize);
						};
						void	SetDeclP1(){
							DeclareElement decl = { enDU_POSITION,		0,  enTFMT_R32_FLOAT,		0,0,	enDT_PER_VERTEX_DATA,0 };

							CopyElement(&decl,1);
						};
						void	SetDeclP2(){
							DeclareElement decl = { enDU_POSITION,		0,  enTFMT_R32G32_FLOAT,		0,0,	enDT_PER_VERTEX_DATA,0 };
							
							CopyElement(&decl,1);
						};
						void	SetDeclP3(){
							DeclareElement decl = { enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,		0,0,	enDT_PER_VERTEX_DATA,0 };

							CopyElement(&decl,1);
						};
						void	SetDeclP4(){
							DeclareElement decl = { enDU_POSITION,		0,  enTFMT_R32G32B32A32_FLOAT,		0,0,	enDT_PER_VERTEX_DATA,0 };

							CopyElement(&decl,1);
						};
						/**	\brief	����λ�÷���������������
						*   
						*	@remarks 	����λ�÷���������������
						*	@see		Info
						*	@return   	void
						*	@note
						*
						**/
						void	SetDeclPNT(){
							DeclareElement decl[] = 
							{
								{ enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,		0,0,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_NORMAL,			0,  enTFMT_R32G32B32_FLOAT,		0,12,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		0,  enTFMT_R32G32_FLOAT,		0,24,	enDT_PER_VERTEX_DATA,0 },
							};
							UInt	uiElementSize	=	sizeof(decl)/sizeof(DeclareElement);
							CopyElement(decl,uiElementSize);
						};
						/**	\brief	
						*   
						*	@remarks 	
						*	@see		Info
						*	@return   	void
						*	@note
						*
						**/
						void	SetDeclPNTT(){
							DeclareElement decl[] = 
							{
								{ enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,		0,0,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_NORMAL,			0,  enTFMT_R32G32B32_FLOAT,		0,12,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		0,  enTFMT_R32G32_FLOAT,		0,24,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TANGENT,			0,  enTFMT_R32G32B32_FLOAT,		0,32,	enDT_PER_VERTEX_DATA,0 },
							};
							UInt	uiElementSize	=	sizeof(decl)/sizeof(DeclareElement);
							CopyElement(decl,uiElementSize);
						};
	
						/**	\brief	����Instance����
						*   
						*	@remarks 	Instance
						*	@see		Info
						*	@return   	void
						*	@note
						*
						**/
						void	SetP_Instance(){
							DeclareElement decl[] = 
							{
								{ enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,			0,0,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		0,  enTFMT_R32G32B32A32_FLOAT,		1,0,	enDT_PER_INSTANCE_DATA,0 },
								{ enDU_TEXCOORD,		1,  enTFMT_R32G32B32A32_FLOAT,		1,16,	enDT_PER_INSTANCE_DATA,0 },
							};
							UInt	uiElementSize	=	sizeof(decl)/sizeof(DeclareElement);
							CopyElement(decl,uiElementSize);
						};
	
						/**	\brief	����λ�ú���ɫ��ת
						*   
						*	@remarks 	����Instance����
						*	@see		Info
						*	@return   	void
						*	@note
						*
						**/
						void	SetPT_Instance(){
							DeclareElement decl[] = 
							{
								{ enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,			0,0,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		0,  enTFMT_R32G32_FLOAT,			0,12,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		1,  enTFMT_R32G32B32A32_FLOAT,		1,0,	enDT_PER_INSTANCE_DATA,0 },
								{ enDU_TEXCOORD,		2,  enTFMT_R32G32B32A32_FLOAT,		1,16,	enDT_PER_INSTANCE_DATA,0 },
							};
							UInt	uiElementSize	=	sizeof(decl)/sizeof(DeclareElement);
							CopyElement(decl,uiElementSize);
						};
						void	SetPNT_Instance(){
							DeclareElement decl[] = 
							{
								{ enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,			0,0,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_NORMAL,			0,  enTFMT_R32G32B32_FLOAT,			0,12,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		0,  enTFMT_R32G32_FLOAT,			0,24,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		1,  enTFMT_R32G32B32A32_FLOAT,		1,0,	enDT_PER_INSTANCE_DATA,0 },
								{ enDU_TEXCOORD,		2,  enTFMT_R32G32B32A32_FLOAT,		1,16,	enDT_PER_INSTANCE_DATA,0 },
							};
							UInt	uiElementSize	=	sizeof(decl)/sizeof(DeclareElement);
							CopyElement(decl,uiElementSize);
						};
						void	SetPNTT_Instance(){
							DeclareElement decl[] = 
							{
								{ enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,			0,0,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_NORMAL,			0,  enTFMT_R32G32B32_FLOAT,			0,12,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		0,  enTFMT_R32G32_FLOAT,			0,24,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TANGENT,			0,  enTFMT_R32G32B32_FLOAT,			0,32,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		1,  enTFMT_R32G32B32A32_FLOAT,		1,0,	enDT_PER_INSTANCE_DATA,0 },
								{ enDU_TEXCOORD,		2,  enTFMT_R32G32B32A32_FLOAT,		1,16,	enDT_PER_INSTANCE_DATA,0 },

							};
							UInt	uiElementSize	=	sizeof(decl)/sizeof(DeclareElement);
							CopyElement(decl,uiElementSize);
						};
						/**	\brief	����Ϊ����ר��
						*   
						*	@remarks 	����Ϊ����ר��
						*	@see		Info
						*	@return   	void
						*	@note
						*
						**/
						void	SetPNTT_Animation(){
							DeclareElement decl[] = 
							{
								{ enDU_POSITION,		0,  enTFMT_R32G32B32_FLOAT,		0,0,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_BLENDWEIGHT,		0,  enTFMT_R8G8B8A8_UNORM,		0,12,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_BLENDINDICES,	0,  enTFMT_R8G8B8A8_UINT,		0,16,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_NORMAL,			0,  enTFMT_R32G32B32_FLOAT,		0,20,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TEXCOORD,		0,  enTFMT_R32G32_FLOAT,		0,32,	enDT_PER_VERTEX_DATA,0 },
								{ enDU_TANGENT,			0,  enTFMT_R32G32B32_FLOAT,		0,40,	enDT_PER_VERTEX_DATA,0 },
							};
							UInt	uiElementSize	=	sizeof(decl)/sizeof(DeclareElement);
							CopyElement(decl,uiElementSize);
						}
	
	

						DeclareElementVector	m_vectorElement;
					};
				
					IDeclare(CAString& strName,Info* pInfo)
						:IProduct(strName)
					{
						if(pInfo!=NULL)
							m_Info	=	*pInfo;
					};
					virtual	U1	Create();
					virtual	U1	Destroy();

					virtual	void*	GetDeclare();
					Info	m_Info;
				};
				
			}
		}

	};
};
#endif // INTERFACEVERTEXBUFF_HEAD_FILE