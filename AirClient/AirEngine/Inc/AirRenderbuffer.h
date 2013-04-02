#ifndef AIRRENDERBUFFER_HEAD_FILE
#define AIRRENDERBUFFER_HEAD_FILE

#include "AirRenderCommon.h"

namespace Air{
	
	namespace Engine{
	
		namespace	Render{

			struct	CBFrame{
				//IntVec4	vScreen;
				Float4	vTime;			///<	x=totaltime t=sin(x) z=cos(x) w= frac(time/(3600*24))
				Float4	vAmbient;
				Float4	vSunDir;		///<	xyz	=	direction	w	=	lighttype(0,1)
				Float4	vSunDiffuse;
				Float4	vMainCamPos;
				enum{
					enRegister	=	0
				};
			};
			struct	CBCamera{
				Float44	mViewProj;
				Float4	vCameraPosition;
				Float4	vCameraDir;
				Float4	vCameraUp;
				Float4	vVP_NearFar;
				enum{
					enRegister	=	6
				};
			};
			struct	CBObject{
				Float44	mWorld;
				enum{
					enRegister	=	15
				};
			};
			struct	CBMaterial{
				Float4	vEmissive;		///<	xyz	=	Emissivs
				Float4	vAmbient;		///<	xyz	=	Ambient		w	=	sss
				Float4	vDiffuse;		///<	xyz	=	Diffuse		w	=	alphaValue	
				Float4	vSpec_Power;	///<	xyz =	Specular	w	=	power
				Float4	vFresnel;		///<	xyz	=	������ϵ��
				enum{
					enRegister	=	19
				};
			};

			struct	PNTT_ANIM{
				Float3	Position;
				U8		BoneWeight[4];
				U8		BoneIndex[4];
				Float3	Normal;
				Float2	UV;
				Float3	Tangent;
			};

			struct	PNTT{
				Float3	Position;
				Float3	Normal;
				Float2	UV;
				Float3	Tangent;
			};
			struct PNT 
			{
				Float3	Position;
				Float3	Normal;
				Float2	UV;
			};
			struct P
			{
				Float3	Position;
			};
			struct	PT
			{
				Float3	Position;
				Float2	UV;
			};



			class	Buffer;
			class	BufferCallback{
			public:
				virtual	U1					IsLoad(Buffer*	pCaller){return	false;};
				virtual	enumBufferFillState	OnFill(void*	pData,U32	uiSize,IProduct*	pCaller)	=	NULL;
			};

			/**	\brief	������������
			*
			*	������������
			*
			***/
			class ENGINE_EXPORT	Buffer
				:	public	IProduct{
			public:
				/**	\brief	������Ϣ
				*
				*	������Ϣ
				*
				***/
				struct Info{
					Info(enumUsage	dwUsage	=	enUSAGE_MANAGED){
						pCB				=	NULL;
						uiElementSize	=	0;
						uiElementSize	=	0;
						InitData		=	NULL;
						usage			=	dwUsage;
						type			=	enBT_CB;
						Flag			=	0;
						cbType			=	enCBT_Material;
					};

					void	SetVertexBuffer(U32	uiCount,U32	uiSize,BufferCallback*	pCallback	=	NULL){
						uiElementSize	=	uiSize;
						uiElementCount	=	uiCount;
						pCB				=	pCallback;
						type			=	enBT_VB;
					};

					void	SetIndexBuffer16(U32	uiCount,BufferCallback*	pCallback	=	NULL){
						uiElementCount	=	uiCount;
						uiElementSize	=	2;
						pCB				=	pCallback;
						type			=	enBT_IB;
					};
					void	SetIndexBuffer32(U32	uiCount,BufferCallback*	pCallback	=	NULL){
						uiElementCount	=	uiCount;
						uiElementSize	=	4;
						pCB				=	pCallback;
						type			=	enBT_IB;
					};
					void	SetConstantBuffer(U32	uiSize,enumConstantBufferType	cbufferType	=	enCBT_Material){
						uiElementCount	=	1;
						uiElementSize	=	uiSize;
						type			=	enBT_CB;
						cbType			=	cbufferType;
					};
					void	SetStructureBuffer(U32	uiCount,U32	uiSize,BufferCallback*	pCallback	=	NULL){
						uiElementSize	=	uiSize;
						uiElementCount	=	uiCount;
						pCB				=	pCallback;
						type			=	enBT_SB;
					}
					void	SetByteAddressBuffer(U32	uiCount,U32	uiSize,BufferCallback*	pCallback	=	NULL){
						uiElementSize	=	uiSize;
						uiElementCount	=	uiCount;
						pCB				=	pCallback;
						type			=	enBT_BAB;
					};
					void	SetViewFlag(U32	flag){
						Flag	=	flag;
						//Only StructBuffer Surport Counter
						if(type!=enBT_SB){
							Flag &= ~enVF_Counter;
						}
					};
					

					void*					InitData;		///<	��ʶ����
					U32						uiElementSize;	///<	����Ԫ�صĴ�С
					U32						uiElementCount;
					BufferCallback*			pCB;
					enumUsage				usage;
					enumBufferType			type;
					enumConstantBufferType	cbType;
					U32						Flag;
				};
	
			public:
				Buffer(CAString&	strName,Info*	pInfo);
				virtual	~Buffer();
				virtual	U1		Create();
				virtual	U1		Destroy();
				/**	\brief	������������
				*   
				*	@remarks 	������������
				*	@see		IBuff
				*	@return   	U1
				*	@param		void * pData
				*	@note
				*
				**/
				virtual	U1		UpdateData(void*	pData);
				/**	\brief	��ȡָ��
				*   
				*	@remarks 	��ȡָ��
				*	@see		Buffer
				*	@return   	void*
				*	@note
				*
				**/
				virtual	void*	GetBuffer(){return	NULL;};
				/**	\brief	�豸��ʧ�ص�
				*   
				*	@remarks 	�豸��ʧ�ص�
				*	@see		Buffer
				*	@return   	void
				*	@note
				*
				**/
				void			OnLostDevice();
				/**	\brief	�豸���ûص�
				*   
				*	@remarks 	�豸���ûص�
				*	@see		Buffer
				*	@return   	void
				*	@note
				*
				**/
				void			OnResetDevice();
				/**	\brief	�����Ƿ���Ҫ�������
				*   
				*	@remarks 	�����Ƿ���Ҫ�������
				*	@see		Buffer
				*	@return   	void
				*	@note
				*
				**/
				U1				IsDirty();
				/**	\brief	֪ͨ��Ҫ�������
				*   
				*	@remarks 	֪ͨ��Ҫ�������
				*	@see		Buffer
				*	@return   	void
				*	@note
				*
				**/
				void			NotifyDirty();

				inline	U32		GetElementSize(){
					return	m_Info.uiElementSize;
				};
				inline	U32		GetElementCount(){
					return	m_Info.uiElementCount;
				};
				inline	U32		GetBufferSize(){
					return	m_Info.uiElementSize*m_Info.uiElementCount;
				};

				virtual	void*	GetSRV(){return	NULL;};
				virtual	void*	GetUAV(){return	NULL;};

				virtual	void	CopyBufferTo(Buffer*	pDest)=NULL;
				virtual	U1		Write(U32	uiOffset,U32	uiSize,const void*	pSourceData)=NULL;
			protected:
				Info			m_Info;				///<	������Ϣ
				U1				m_bDirty;			///<	�Ƿ��Ѿ��ı�
			};
		}

		typedef	Render::PNTT_ANIM	ABuff;	///<	������
		typedef	Render::PNTT		SBuff;	///<	��̬ģ��
		typedef	Render::P			PBuff;	///<	����
		typedef	U16					IBuff;
	};
};
#endif // INTERFACERENDERINDEXBUFF_HEAD_FILE