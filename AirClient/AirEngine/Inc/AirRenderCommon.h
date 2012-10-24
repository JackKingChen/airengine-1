#ifndef INTERFACERENDERCOMMON_HEAD_FILE
#define INTERFACERENDERCOMMON_HEAD_FILE

#include	"AirEngineHeader.h"
namespace Air{
	
	namespace Client{
		enum	enumSystemVersion{
			enRSV_UNKNOWN,
			enRSV_81,
			enRSV_9,
			enRSV_10,
			enRSV_10_1,
			enRSV_11,
			enRSV_GL,
			enRSV_GLES,
		};
		typedef	enumSystemVersion	enumHardwareVersion;
		enum	enumPhaseIndex{
			enPI_Reflect,
			enPI_Shadow,
			enPI_MRT,
			enPI_SSAO,
			enPI_GI,
			enPI_DeferredLight,
			enPI_Alpha,
			enPI_PostComposer,

			enPI_Helper,
			enPI_UI,
			enPI_Overlay,
			enPI_HardwareOcc,
			enPI_RayCast,

			enPI_MunaulRender	=	31,
			enPI_MAX			=	32
		};
		typedef	std::list<enumPhaseIndex>	PhaseIdxList;

		struct	PhaseOption{
			PhaseOption(){
				flag	=	0;
			};
			PhaseOption(const PhaseOption&	opt){
				flag	=	opt.flag;
				lstPI	=	opt.lstPI;
			};
			void	Clear(){
				flag	=	0;
				lstPI.clear();
			};
			void	AddIndex(enumPhaseIndex	index){
				flag	|=	1<<index;
				lstPI.push_back(index);
			};
			void	RemoveIndex(enumPhaseIndex	index){
				flag	&=	~(1<<index);
				lstPI.remove(index);
			}
			PhaseIdxList	lstPI;	
			U32				flag;
		};
		enum	enumTextureFormat{
			enTFMT_UNKNOWN                      = 0,
			enTFMT_R32G32B32A32_TYPELESS        = 1,
			enTFMT_R32G32B32A32_FLOAT           = 2,
			enTFMT_R32G32B32A32_UINT            = 3,
			enTFMT_R32G32B32A32_SINT            = 4,
			enTFMT_R32G32B32_TYPELESS           = 5,
			enTFMT_R32G32B32_FLOAT              = 6,
			enTFMT_R32G32B32_UINT               = 7,
			enTFMT_R32G32B32_SINT               = 8,
			enTFMT_R16G16B16A16_TYPELESS        = 9,
			enTFMT_R16G16B16A16_FLOAT           = 10,
			enTFMT_R16G16B16A16_UNORM           = 11,
			enTFMT_R16G16B16A16_UINT            = 12,
			enTFMT_R16G16B16A16_SNORM           = 13,
			enTFMT_R16G16B16A16_SINT            = 14,
			enTFMT_R32G32_TYPELESS              = 15,
			enTFMT_R32G32_FLOAT                 = 16,
			enTFMT_R32G32_UINT                  = 17,
			enTFMT_R32G32_SINT                  = 18,
			enTFMT_R32G8X24_TYPELESS            = 19,
			enTFMT_D32_FLOAT_S8X24_UINT         = 20,
			enTFMT_R32_FLOAT_X8X24_TYPELESS     = 21,
			enTFMT_X32_TYPELESS_G8X24_UINT      = 22,
			enTFMT_R10G10B10A2_TYPELESS         = 23,
			enTFMT_R10G10B10A2_UNORM            = 24,
			enTFMT_R10G10B10A2_UINT             = 25,
			enTFMT_R11G11B10_FLOAT              = 26,
			enTFMT_R8G8B8A8_TYPELESS            = 27,
			enTFMT_R8G8B8A8_UNORM               = 28,
			enTFMT_R8G8B8A8_UNORM_SRGB          = 29,
			enTFMT_R8G8B8A8_UINT                = 30,
			enTFMT_R8G8B8A8_SNORM               = 31,
			enTFMT_R8G8B8A8_SINT                = 32,
			enTFMT_R16G16_TYPELESS              = 33,
			enTFMT_R16G16_FLOAT                 = 34,
			enTFMT_R16G16_UNORM                 = 35,
			enTFMT_R16G16_UINT                  = 36,
			enTFMT_R16G16_SNORM                 = 37,
			enTFMT_R16G16_SINT                  = 38,
			enTFMT_R32_TYPELESS                 = 39,
			enTFMT_D32_FLOAT                    = 40,
			enTFMT_R32_FLOAT                    = 41,
			enTFMT_R32_UINT                     = 42,
			enTFMT_R32_SINT                     = 43,
			enTFMT_R24G8_TYPELESS               = 44,
			enTFMT_D24_UNORM_S8_UINT            = 45,
			enTFMT_R24_UNORM_X8_TYPELESS        = 46,
			enTFMT_X24_TYPELESS_G8_UINT         = 47,
			enTFMT_R8G8_TYPELESS                = 48,
			enTFMT_R8G8_UNORM                   = 49,
			enTFMT_R8G8_UINT                    = 50,
			enTFMT_R8G8_SNORM                   = 51,
			enTFMT_R8G8_SINT                    = 52,
			enTFMT_R16_TYPELESS                 = 53,
			enTFMT_R16_FLOAT                    = 54,
			enTFMT_D16_UNORM                    = 55,
			enTFMT_R16_UNORM                    = 56,
			enTFMT_R16_UINT                     = 57,
			enTFMT_R16_SNORM                    = 58,
			enTFMT_R16_SINT                     = 59,
			enTFMT_R8_TYPELESS                  = 60,
			enTFMT_R8_UNORM                     = 61,
			enTFMT_R8_UINT                      = 62,
			enTFMT_R8_SNORM                     = 63,
			enTFMT_R8_SINT                      = 64,
			enTFMT_A8_UNORM                     = 65,
			enTFMT_R1_UNORM                     = 66,
			enTFMT_R9G9B9E5_SHAREDEXP           = 67,
			enTFMT_R8G8_B8G8_UNORM              = 68,
			enTFMT_G8R8_G8B8_UNORM              = 69,
			enTFMT_BC1_TYPELESS                 = 70,
			enTFMT_BC1_UNORM                    = 71,
			enTFMT_BC1_UNORM_SRGB               = 72,
			enTFMT_BC2_TYPELESS                 = 73,
			enTFMT_BC2_UNORM                    = 74,
			enTFMT_BC2_UNORM_SRGB               = 75,
			enTFMT_BC3_TYPELESS                 = 76,
			enTFMT_BC3_UNORM                    = 77,
			enTFMT_BC3_UNORM_SRGB               = 78,
			enTFMT_BC4_TYPELESS                 = 79,
			enTFMT_BC4_UNORM                    = 80,
			enTFMT_BC4_SNORM                    = 81,
			enTFMT_BC5_TYPELESS                 = 82,
			enTFMT_BC5_UNORM                    = 83,
			enTFMT_BC5_SNORM                    = 84,
			enTFMT_B5G6R5_UNORM                 = 85,
			enTFMT_B5G5R5A1_UNORM               = 86,
			enTFMT_B8G8R8A8_UNORM               = 87,
			enTFMT_B8G8R8X8_UNORM               = 88,
			enTFMT_R10G10B10_XR_BIAS_A2_UNORM   = 89,
			enTFMT_B8G8R8A8_TYPELESS            = 90,
			enTFMT_B8G8R8A8_UNORM_SRGB          = 91,
			enTFMT_B8G8R8X8_TYPELESS            = 92,
			enTFMT_B8G8R8X8_UNORM_SRGB          = 93,
			enTFMT_BC6H_TYPELESS                = 94,
			enTFMT_BC6H_UF16                    = 95,
			enTFMT_BC6H_SF16                    = 96,
			enTFMT_BC7_TYPELESS                 = 97,
			enTFMT_BC7_UNORM                    = 98,
			enTFMT_BC7_UNORM_SRGB               = 99,
			enTFMT_FORCE_UINT                   = 0xffffffffUL 
		};
		enum	enumTextureType{
			enTT_Unknown,
			enTT_Texture1D,
			enTT_Texture2D,
			enTT_Texture3D,
			enTT_TextureCUBE,
			enTT_Texture1DArray,
			enTT_Texture2DArray,
			enTT_Texture3DArray,
			enTT_TextureCUBEArray,
			enTT_MAX
		};
		enum	enumViewFlag{
			enVF_SRV	=	1,	///<	Shader		Resource	View
			enVF_RTV	=	2,	///<	Render		Target		View
			enVF_DSV	=	4,	///<	Depth		Stencil		View
			enVF_UAV	=	8,	///<	Unordered	Access		View
		};
		enum	enumBufferType{
			enBT_VB,	///<	VertexBuffer
			enBT_IB,	///<	IndexBuffer
			enBT_CB,	///<	ConstantBuffer
			enBT_SB		///<	StructureBuffer	/ RAWBuffer
		};
		enum	enumConstantBufferType{
			enCBT_Frame,		///<	Frame,	
			enCBT_Camera,		///<	Camera,
			enCBT_Object,		///<	Object,
			enCBT_Material,		///<	Material
			enCBT_Bone			///<	Bone
		};

		enum enumDeclareUsage
		{
			enDU_POSITION = 0,
			enDU_BLENDWEIGHT,   // 1
			enDU_BLENDINDICES,  // 2
			enDU_NORMAL,        // 3
			enDU_PSIZE,         // 4
			enDU_TEXCOORD,      // 5
			enDU_TANGENT,       // 6
			enDU_BINORMAL,      // 7
			enDU_TESSFACTOR,    // 8
			enDU_POSITIONT,     // 9
			enDU_COLOR,         // 10
			enDU_FOG,           // 11
			enDU_DEPTH,         // 12
			enDU_SAMPLE,        // 13
			enDU_CUSTOM
		};
		enum	enumDeclareType{
			enDT_PER_VERTEX_DATA,
			enDT_PER_INSTANCE_DATA
		};
		struct DeclareElement{
			enumDeclareUsage	SemanticName;
			U32					SemanticIndex;
			enumTextureFormat	Format;
			U32					InputSlot;
			U32					AlignedByteOffset;
			enumDeclareType		InputSlotClass;
			U32					InstanceDataStepRate;
		};
		typedef	std::vector<DeclareElement>			DeclareElementVector;
		typedef	DeclareElementVector::iterator		DeclareElementVectorItr;
		/**	\brief	��ɫ��������
		*
		*	��ɫ��������
		*
		***/
		enum	enumShaderType{
			enVS,
			enGS,
			enPS,
			enCS,
			enHS,
			enDS
		};
		enum	enumShaderVersion{
			enSV_3_0,
			enSV_4_0,
			enSV_4_1,
			enSV_5_0
		};
		enum	enumRenderStateType{
			enRST_RS,
			enRST_DS,
			enRST_BS,
			enRST_SS
		};

		enum enumTextureFilter {
			enTF_MIN_MAG_MIP_POINT                            = 0,
			enTF_MIN_MAG_POINT_MIP_LINEAR                     = 0x1,
			enTF_MIN_POINT_MAG_LINEAR_MIP_POINT               = 0x4,
			enTF_MIN_POINT_MAG_MIP_LINEAR                     = 0x5,
			enTF_MIN_LINEAR_MAG_MIP_POINT                     = 0x10,
			enTF_MIN_LINEAR_MAG_POINT_MIP_LINEAR              = 0x11,
			enTF_MIN_MAG_LINEAR_MIP_POINT                     = 0x14,
			enTF_MIN_MAG_MIP_LINEAR                           = 0x15,
			enTF_ANISOTROPIC                                  = 0x55,
			enTF_COMPARISON_MIN_MAG_MIP_POINT                 = 0x80,
			enTF_COMPARISON_MIN_MAG_POINT_MIP_LINEAR          = 0x81,
			enTF_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT    = 0x84,
			enTF_COMPARISON_MIN_POINT_MAG_MIP_LINEAR          = 0x85,
			enTF_COMPARISON_MIN_LINEAR_MAG_MIP_POINT          = 0x90,
			enTF_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR   = 0x91,
			enTF_COMPARISON_MIN_MAG_LINEAR_MIP_POINT          = 0x94,
			enTF_COMPARISON_MIN_MAG_MIP_LINEAR                = 0x95,
			enTF_COMPARISON_ANISOTROPIC                       = 0xd5,
			enTF_TEXT_1BIT                                    = 0x80000000 
		};
		namespace	Render{
			


			typedef	std::list<enumPhaseIndex>	RenderOrderList;

			/**	\brief	Ԫ������
			*
			*	Ԫ������	�������������
			*
			***/
			enum	enumElementType{
				ET_VB_PNTT,				///<	��ͨ������Ϣ
				ET_VB_PNTT_A,			///<	������������Ϣ
				ET_VB_P,				///<	ֻ��λ�õĶ�����Ϣ
				ET_VB_Private,			///<	˽�ж��� �ᵥ������һ�����㻺����(����ʹ��Instanceʱ)
				ET_IB_16,				///<	16��������
				ET_IB_32,				///<	32��������
				ET_VB_CUSTOM,
				ET_Max
			};


			/**	\brief	���ʽű�ö��
			*
			*	���ʽű�ö��
			*
			***/
			enum	enumMaterial{
				enUnKnown,
				enMaterial,
					enVector,
					enMatrix,
					enVectorArray,
					enMatrixArray,
					enUseSkin,
				enMaterialTemplate,
					enPhase,
					enPriority,
						enPass,
							enVertexShader,
								enTexture,
								enTextureIndex,
								enSamplerState,
								enTextureFilter,
								enTextureAddress,
							enGeometryShader,
							enPixelShader,
							enHullShader,
							enComputeShader,
							enDomainShader,
	
							enRasterizerState,
								enFillMode,
								enCullMode,
								enDepthBias,
								enDepthBiasClamp,
								enSlopeScaledDepthBias,
								enDepthClipEnable,
								enScissorEnable,
								enMultisampleEnable,
								enAntialiasedLineEnable,
							enBlendState,
								enAlphaToCoverage,
								enIndependentBlend,
								enRenderTargetBlend,
									enBlendEnable,
									enSrcBlend,
									enDestBlend,
									enBlendOP,
									enSrcBlendAlpha,
									enDestBlendAlpha,
									enBlendOpAlpha,
									enRenderTargetWriteMask,
							enDepthState,
								enDepthEnable,
								enDepthWriteMask,
								enDepthFunc,
								enStencilEnable,
								enStencilReadMask,
								enStencilWriteMask,
								enFrontFace,
									enStencilFailOp,
									enStencilDepthFailOp,
									enStencilPassOp,
									enStencilFunc,
								enBackFace,
	
				enMaterialMax
			};
			enum	enumStencileOP{
				enSOP_KEEP       = 1,
				enSOP_ZERO       = 2,
				enSOP_REPLACE    = 3,
				enSOP_INCR_SAT   = 4,
				enSOP_DECR_SAT   = 5,
				enSOP_INVERT     = 6,
				enSOP_INCR       = 7,
				enSOP_DECR       = 8 
			};
	
			enum	enumBlendOP{
				enBOP_ADD            = 1,
				enBOP_SUBTRACT       = 2,
				enBOP_REV_SUBTRACT   = 3,
				enBOP_MIN            = 4,
				enBOP_MAX            = 5 
			};
	
			enum	enumBlend{
				enB_ZERO               = 1,
				enB_ONE                = 2,
				enB_SRC_COLOR          = 3,
				enB_INV_SRC_COLOR      = 4,
				enB_SRC_ALPHA          = 5,
				enB_INV_SRC_ALPHA      = 6,
				enB_DEST_ALPHA         = 7,
				enB_INV_DEST_ALPHA     = 8,
				enB_DEST_COLOR         = 9,
				enB_INV_DEST_COLOR     = 10,
				enB_SRC_ALPHA_SAT      = 11,
				enB_BLEND_FACTOR       = 14,
				enB_INV_BLEND_FACTOR   = 15,
				enB_SRC1_COLOR         = 16,
				enB_INV_SRC1_COLOR     = 17,
				enB_SRC1_ALPHA         = 18,
				enB_INV_SRC1_ALPHA     = 19 
			};
			enum	enumTextureAddress{
				enTA_WRAP		=	1,
				enTA_MIRROR,
				enTA_CLAMP,
				enTA_BORDER,
				enTA_MIRROR_ONCE,
				enTA_UNKNOWN
			};
			enum	enumDepthWriteMask{
				enDWM_ZERO,
				enDWM_ALL
			};
			enum	enumFillMode{
				enFM_POINT		=	1,
				enFM_WIREFRAME,
				enFM_SOILD
			};
			enum	enumCullMode{
				enCM_UNKNOWN,
				enCM_NONE,
				enCM_CW,
				enCM_CCW
			};
			enum	enumFog{
				enF_NONE,
				enF_EXP,
				enF_EXP2,
				enF_LINE
			};
			enum	enumCompare{
				enC_NEVER           = 1,
				enC_LESS            = 2,
				enC_EQUAL           = 3,
				enC_LESS_EQUAL      = 4,
				enC_GREATER         = 5,
				enC_NOT_EQUAL       = 6,
				enC_GREATER_EQUAL   = 7,
				enC_ALWAYS          = 8 
			};
	
			/**	\brief	���ʲ�������
			*
			*	���ʲ�������
			*
			***/
			enum	enumParamType{
				MATERIAL_PARAM_TECHNIQUE,					///<	��Ⱦ��������
				MATERIAL_PARAM_BOOL,						///<	��������
				MATERIAL_PARAM_INT,							///<	����
				MATERIAL_PARAM_FLOAT,						///<	������
				MATERIAL_PARAM_INT4,						///<	��ά��������
				MATERIAL_PARAM_INT4ARRAY,					///<	��ά������������
				MATERIAL_PARAM_VECTOR,						///<	4Ψ����
				MATERIAL_PARAM_VECTORARRAY,					///<	��������
				MATERIAL_PARAM_MATRIX,						///<	����
				MATERIAL_PARAM_MATRIXARRAY,					///<	��������
				MATERIAL_PARAM_TEXTURE,						///<	����
				MATERIAL_PARAM_TEXTURE_CUBE,				///<	����������
				MATERIAL_PARAM_TEXTURE_VOLUME,				///<	�������
				MATERIAL_PARAM_TEXTURE_SHADOW,				///<	��Ӱ����
				MATERIAL_PARAM_TEXTURE_SKY,					///<	�������
				MATERIAL_PARAM_TEXTURE_LASTPOSTCOMPOSER,	///<	�ϴκ���Ч������
				MATERIAL_PARAM_TEXTURE_BONE,				///<	�洢������������
				MATERIAL_PARAM_MATRIX_TEXTURE_SHADOW,		///<	��Ӱ�������
				MATERIAL_PARAM_MATRIX_WORLD,				///<	�������
				MATERIAL_PARAM_MATRIX_VIEWPROJ,				///<	��ҰͶӰ����
				MATERIAL_PARAM_MATRIX_VIEWPROJ_INV,			///<	��ҰͶӰ�����
				MATERIAL_PARAM_MATRIX_WORLDVIEWPROJ,		///<	������ҰͶӰ����
				MATERIAL_PARAM_MATRIX_WORLDVIEW,			///<	������Ұ
				MATERIAL_PARAM_MATRIX_BONEARRAY,			///<	����ת����������
				MATERIAL_PARAM_VECTOR_AMIBENT,				///<	������
				MATERIAL_PARAM_VECTOR_LIGHT_POS,			///<	���λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF,			///<	�����ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POS1,			///<	��1յ�ƹ�λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF1,			///<	��1յ�ƹ���ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POS2,			///<	��2յ�ƹ�λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF2,			///<	��2յ�ƹ���ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POS3,			///<	��3յ�ƹ�λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF3,			///<	��3յ�ƹ���ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POS4,			///<	��4յ�ƹ�λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF4,			///<	��4յ�ƹ���ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POS5,			///<	��5յ�ƹ�λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF5,			///<	��5յ�ƹ���ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POS6,			///<	��6յ�ƹ�λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF6,			///<	��6յ�ƹ���ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POS7,			///<	��7յ�ƹ�λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF7,			///<	��7յ�ƹ���ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POS8,			///<	��8յ�ƹ�λ��
				MATERIAL_PARAM_VECTOR_LIGHT_DIFF8,			///<	��8յ�ƹ���ɫ
				MATERIAL_PARAM_VECTOR_LIGHT_POSARRAY,		///<	�ƹ�λ������
				MATERIAL_PARAM_VECTOR_LIGHT_DIFFARRAY,		///<	�ƹ�����������
				MATERIAL_PARAM_VECTOR_CAMERA_POSITION,		///<	�����λ��
				MATERIAL_PARAM_VECTOR_CAMERA_DIRECTION,		///<	���������
				MATERIAL_PARAM_VECTOR_CAMERA_UPDIR,			///<	�����������
				MATERIAL_PARAM_VECTOR_CAMERA_RIGHTDIR,		///<	��������ַ���
				MATERIAL_PARAM_VECTOR_BOUND_MIN,			///<	��Χ����Сֵ
				MATERIAL_PARAM_VECTOR_BOUND_MAX,			///<	��Χ�����ֵ
				MATERIAL_PARAM_VECTOR_BOUND_SPHERE,			///<	��Χ��
				MATERIAL_PARAM_VECTOR_MOUSE_POSITION,
				MATERIAL_PARAM_VECTOR_MOUSE_MOVE,
				MATERIAL_PARAM_FLOAT_TIME_TOTAL,			///<	��ʱ��
				MATERIAL_PARAM_FLOAT_TIME_DELTA,			///<	����һ֡�ļ��ʱ��
				MATERIAL_PARAM_FLOAT_TIME_CREATE,			///<	����ʱ��
				MATERIAL_PARAM_FLOAT_SCREEN_WIDTH,			///<	��Ļ���
				MATERIAL_PARAM_FLOAT_SCREEN_HEIGHT,			///<	��Ļ�߶�
				MATERIAL_PARAM_MAX							///<	
			};
	
			/**	\brief	����ʽ
			*
			*	����ʽ
			*
			***/
			enum	enumPool{
				POOL_DEFAULT                 = 0,
				POOL_MANAGED                 = 1,
				POOL_SYSTEMMEM               = 2,
				POOL_SCRATCH                 = 3,
			};
			/**	\brief	��;
			*
			*	��;
			*
			***/
			enum	enumUsage{
				//Texture
				enUSAGE_DEFAULT,
				enUSAGE_RENDERTARGET,
				enUSAGE_DYNAMIC,
				enUSAGE_MANAGED,
				enUSAGE_SYSTEM_MEMORY
			};
			enum	enumLockType{
				enLK_DISCARD,
				enLK_READ,
				enLK_NO_OVER_WRITE,
			};
			enum	enumCubeFaceType{
				enCFT_POSITIVE_X    = 0,
				enCFT_NEGATIVE_X    = 1,
				enCFT_POSITIVE_Y    = 2,
				enCFT_NEGATIVE_Y    = 3,
				enCFT_POSITIVE_Z    = 4,
				enCFT_NEGATIVE_Z    = 5,
			};
			namespace	Vertex{
				class IBuff;
				class IDeclare;
			};
			namespace	Index{
				class IBuff;
			};
			class IMaterial;
			class IXObject;
	#define LOCK_READONLY           0x00000010L
	#define LOCK_DISCARD            0x00002000L
	#define LOCK_NOOVERWRITE        0x00001000L
	#define LOCK_NOSYSLOCK          0x00000800L
	#define LOCK_DONOTWAIT          0x00004000L  
	
	#define LOCK_NO_DIRTY_UPDATE     0x00008000L
			struct LockOption{
				LockOption(UInt pos,UInt size,void** pLockBuff,UInt flag	=	LOCK_DISCARD){
					Size			=	size;
					StartPosition	=	pos;
					LockBuff		=	pLockBuff;
					Flag			=	flag;
				};
				UInt	Size;
				UInt	StartPosition;
				void**	LockBuff;
				UInt	Flag;
			};
			namespace	Draw{
				/**	\brief	����ģʽ
				*
				*	����ģʽ
				*
				***/
				enum enumPrimitiveType{
					enPT_UNDEFINED                    = 0,
					enPT_POINTLIST                    = 1,
					enPT_LINELIST                     = 2,
					enPT_LINESTRIP                    = 3,
					enPT_TRIANGLELIST                 = 4,
					enPT_TRIANGLESTRIP                = 5,
					enPT_LINELIST_ADJ                 = 10,
					enPT_LINESTRIP_ADJ                = 11,
					enPT_TRIANGLELIST_ADJ             = 12,
					enPT_TRIANGLESTRIP_ADJ            = 13,
					enPT_1_CONTROL_POINT_PATCHLIST    = 33,
					enPT_2_CONTROL_POINT_PATCHLIST    = 34,
					enPT_3_CONTROL_POINT_PATCHLIST    = 35,
					enPT_4_CONTROL_POINT_PATCHLIST    = 36,
					enPT_5_CONTROL_POINT_PATCHLIST    = 37,
					enPT_6_CONTROL_POINT_PATCHLIST    = 38,
					enPT_7_CONTROL_POINT_PATCHLIST    = 39,
					enPT_8_CONTROL_POINT_PATCHLIST    = 40,
					enPT_9_CONTROL_POINT_PATCHLIST    = 41,
					enPT_10_CONTROL_POINT_PATCHLIST   = 42,
					enPT_11_CONTROL_POINT_PATCHLIST   = 43,
					enPT_12_CONTROL_POINT_PATCHLIST   = 44,
					enPT_13_CONTROL_POINT_PATCHLIST   = 45,
					enPT_14_CONTROL_POINT_PATCHLIST   = 46,
					enPT_15_CONTROL_POINT_PATCHLIST   = 47,
					enPT_16_CONTROL_POINT_PATCHLIST   = 48,
					enPT_17_CONTROL_POINT_PATCHLIST   = 49,
					enPT_18_CONTROL_POINT_PATCHLIST   = 50,
					enPT_19_CONTROL_POINT_PATCHLIST   = 51,
					enPT_20_CONTROL_POINT_PATCHLIST   = 52,
					enPT_21_CONTROL_POINT_PATCHLIST   = 53,
					enPT_22_CONTROL_POINT_PATCHLIST   = 54,
					enPT_23_CONTROL_POINT_PATCHLIST   = 55,
					enPT_24_CONTROL_POINT_PATCHLIST   = 56,
					enPT_25_CONTROL_POINT_PATCHLIST   = 57,
					enPT_26_CONTROL_POINT_PATCHLIST   = 58,
					enPT_27_CONTROL_POINT_PATCHLIST   = 59,
					enPT_28_CONTROL_POINT_PATCHLIST   = 60,
					enPT_29_CONTROL_POINT_PATCHLIST   = 61,
					enPT_30_CONTROL_POINT_PATCHLIST   = 62,
					enPT_31_CONTROL_POINT_PATCHLIST   = 63,
					enPT_32_CONTROL_POINT_PATCHLIST   = 64 
				};
				/**	\brief	���ƺ�������
				*
				*	���ƺ�������
				*
				***/
				enum	enumFunctionType{
					//Dx9
					FUNC_TYPE_DP,			///<	DrawPrimitive			��ʹ����������
					FUNC_TYPE_DIP,			///<	DrawIndexedPrimitive
					//Dx10
					FUNC_TYPE_DA,		///<	ID3D10Device::DrawAuto
					FUNC_TYPE_DIP_I,	///<	ID3D10Device::DrawIndexedInstanced
					FUNC_TYPE_DP_I		///<	ID3D10Device::DrawInstanced
				};
	
				/**	\brief	����ѡ��
				*
				*	����ѡ��
				*
				*	ע����ƺ�������	���Բο�IDirect3DDevice�ĸ������ƺ���  ������һһ��Ӧ��
				*	FUNC_TYPE_DP		��Ҫm_uiBaseVertexIndex��m_uiFaceCount����ʼ����ID  �� Ҫ��Ⱦ������������Ƿ���������Ч��
				*	FUNC_TYPE_DIP		���в����������� �����޷���Ⱦ
				*	
				*	��ʱ��Ҫʹ��FUNC_TYPE_DP_UP	��	FUNC_TYPE_DIP_UP����Ⱦ��û��ʵ�ִ˺���
				*
				***/
				struct Option{
					Option(	enumPrimitiveType	type	=	enPT_TRIANGLELIST,
							enumFunctionType	funType	=	FUNC_TYPE_DIP,
							U32					base	=	0,
							U32					count	=	0,
							U32					start	=	0,
							U32					face	=	0){
						m_DrawType			=	type;
						m_DrawFuncType		=	funType;
						m_uiBaseVertexIndex	=	base;
						m_uiVertexCount		=	count;
						m_uiStartIndex		=	start;
						m_uiFaceCount		=	face;
						m_uiInstanceCount	=	0;
					};
					enumPrimitiveType	m_DrawType;				///<	���Ʒ�ʽ
					enumFunctionType	m_DrawFuncType;			///<	���ƺ���
					U32					m_uiBaseVertexIndex;	///<	������������
					U32					m_uiVertexCount;		///<	��������
					U32					m_uiStartIndex;			///<	��ʼ����λ��
					U32					m_uiFaceCount;			///<	��������
					U32					m_uiInstanceCount;		///<	Instance����
				};
	
				/**	\brief	��Ⱦ����
				*
				*	��Ⱦ����
				*
				***/
				struct Buff{
					Buff(){
						for(int i=0;i<4;i++){
							m_pVertexBuffer[i]		=	NULL;
						}
						m_pVertexDeclare	=	NULL;
						m_pIndexBuff		=	NULL;

					};
	
					/**	\brief	������Ⱦѡ��
					*   
					*	@remarks 	������Ⱦѡ��
					*	@see		Buff
					*	@return   	void
					*	@param		Option option
					*	@note
					*
					**/
					inline	void	SetOption(Option option){m_DrawOption	=	option;};
					Buffer*				m_pVertexBuffer[4];		///<	���㻺��
					Vertex::IDeclare*	m_pVertexDeclare;		///<	��������
					Buffer*				m_pIndexBuff;			///<	��������
					Option				m_DrawOption;			///<	��Ⱦѡ��
				};
			}
	
			struct InterSectResult{
				UInt	uiFace;                 // mesh face that was intersected
				Real	fBary1, fBary2;         // barycentric coords of intersection
				Real	fDist;                  // distance from ray origin to intersection
				Real	tu, tv;                 // texture coords of intersection
			};
			/**	\brief	��ȾĿ����
			*
			*	��ȾĿ����
			*
			***/
			struct RENDER_TARGET_BLEND{
				RENDER_TARGET_BLEND(){
					BlendEnable				=	FALSE;
					SrcBlend				=	enB_ONE;
					DestBlend				=	enB_ZERO;
					BlendOp					=	enBOP_ADD;
					SrcBlendAlpha			=	enB_ONE;
					DestBlendAlpha			=	enB_ZERO;
					BlendOpAlpha			=	enBOP_ADD;
					RenderTargetWriteMask	=	0x0f;
				};
				SInt		BlendEnable;
				enumBlend	SrcBlend;
				enumBlend	DestBlend;
				enumBlendOP	BlendOp;
				enumBlend	SrcBlendAlpha;
				enumBlend	DestBlendAlpha;
				enumBlendOP	BlendOpAlpha;
				U8			RenderTargetWriteMask;
			};
			/**	\brief	���״̬
			*
			*	���״̬
			*
			***/
			struct	BLEND_DESC{
				BLEND_DESC(){
					AlphaToCoverageEnable	=	FALSE;
					IndependentBlendEnable	=	FALSE;
				};
				SInt				AlphaToCoverageEnable;
				SInt				IndependentBlendEnable;
				RENDER_TARGET_BLEND	Blend[8];
			};
			/**	\brief	���ģ�����
			*
			*	���ģ�����
			*
			***/
			struct	 DEPTH_STENCILOP{
				DEPTH_STENCILOP(){
					StencilFailOp		=	enSOP_KEEP;
					StencilDepthFailOp	=	enSOP_KEEP;
					StencilPassOp		=	enSOP_KEEP;
					StencilFunc			=	enC_ALWAYS;
				};
				enumStencileOP	StencilFailOp;
				enumStencileOP	StencilDepthFailOp;
				enumStencileOP	StencilPassOp;
				enumCompare		StencilFunc;
			};
			
			/**	\brief	���״̬
			*
			*	���״̬
			*
			***/
			struct	DEPTH_STENCIL_DESC{
				DEPTH_STENCIL_DESC(){
					DepthEnable			=	TRUE;
					DepthWriteMask		=	enDWM_ALL;
					DepthFunc			=	enC_LESS;
					StencilEnable		=	FALSE;
					StencilReadMask		=	0xff;
					StencilWriteMask	=	0xff;
				};
				SInt				DepthEnable;
				enumDepthWriteMask	DepthWriteMask;
				enumCompare			DepthFunc;
				SInt				StencilEnable;
				U8					StencilReadMask;
				U8					StencilWriteMask;
				DEPTH_STENCILOP		FrontFace;
				DEPTH_STENCILOP		BackFace;
			};
			/**	\brief	��դ��״̬
			*
			*	��դ��״̬
			*
			***/
			struct	RASTERIZER_DESC{
				RASTERIZER_DESC(){
					FillMode				=	enFM_SOILD;
					CullMode				=	enCM_CW;
					FrontCounterClockwise	=	FALSE;
					DepthBias				=	0;
					SlopeScaledDepthBias	=	0.0f;
					DepthBiasClamp			=	0.0f;
					DepthClipEnable			=	TRUE;
					ScissorEnable			=	FALSE;
					MultisampleEnable		=	FALSE;
					AntialiasedLineEnable	=	FALSE;
				}
				enumFillMode	FillMode;
				enumCullMode	CullMode;
				SInt			FrontCounterClockwise;
				SInt			DepthBias;
				Real			DepthBiasClamp;
				Real			SlopeScaledDepthBias;
				SInt			DepthClipEnable;
				SInt			ScissorEnable;
				SInt			MultisampleEnable;
				SInt			AntialiasedLineEnable;
			};
			/**	\brief	����״̬	Copy	From	D11
			*
			*	����״̬	Copy	From	D11
			*
			***/
			struct SAMPLER_DESC {
				SAMPLER_DESC(){
					Filter			=	enTF_MIN_MAG_MIP_LINEAR;
					AddressU		=	enTA_CLAMP;
					AddressV		=	enTA_CLAMP;
					AddressW		=	enTA_CLAMP;
					MipLODBias		=	0;
					MaxAnisotropy	=	16;
					ComparisonFunc	=	enC_NEVER;
					MinLOD			=	-3.402823466e+38f;
					MaxLOD			=	3.402823466e+38f;//D3D11_FLOAT32_MAX
				};
				enumTextureFilter				Filter;
				enumTextureAddress				AddressU;
				enumTextureAddress				AddressV;
				enumTextureAddress				AddressW;
				Real							MipLODBias;
				UInt							MaxAnisotropy;
				enumCompare						ComparisonFunc;
				Float4							BorderColor;
				Real							MinLOD;
				Real							MaxLOD;
			};

			typedef	std::map<UInt,UInt>		StateMap;

			/**	\brief	ͨ��״̬��Ϣ
			*
			*	ͨ��״̬��Ϣ
			*
			***/
			struct	StateInfo{
				StateInfo(){
					type	=	enRST_RS;
				};
				enumRenderStateType	type;
				//union{
					BLEND_DESC			bs;
					RASTERIZER_DESC		rs;
					DEPTH_STENCIL_DESC	ds;
					SAMPLER_DESC		ss;
				//};
			};





	
			typedef	std::vector<IntVec4>		IVectorArray;
			class	Texture;
		}
		typedef	Render::Draw::Buff					DrawBuff;
		typedef	Render::Draw::Option				DrawOption;
		typedef	std::vector<Render::Texture*>		TextureArray;
		/**	\brief	���ʲ���
		*
		*	���ʲ���
		*
		***/
		struct	MaterialParam{
			VectorArray		m_FloatArray;
			TextureArray	m_TextureArray;
		};
		//����Texture VB IB�����
		enum	enumBufferFillState{
			enBFS_UNKNOWN,
			enBFS_LOADING,
			enBFS_OK,
			enBFS_FAILED,
			enBFS_DIRTY,
			enBFS_MAX
		};
		//����Texture VB IB�����
		class	BufferFillCallback{
		public:
			virtual	U1					IsLoad(IProduct*	pCaller){return	false;};
			virtual	enumBufferFillState	OnFill(void*	pData,U32	uiSize,IProduct*	pCaller)	=	NULL;
		};
	};
};
#endif // INTERFACERENDERCOMMON_HEAD_FILE