#ifndef ENGINESHADERSHAREPARAM_HEAD_FILE
#define ENGINESHADERSHAREPARAM_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Engine{
	
	#ifndef MAX_LIGHT
	#define MAX_LIGHT	9
	#endif
	
		class						Material;
	
		class	ShaderShareParam{
		public:
			ShaderShareParam();
	
			void UpdataBound( BoundBox& box );
			/**	\brief	���µƹ���Ϣ
			*   
			*	@remarks 	���µƹ���Ϣ
			*	@see		GlobalSetting
			*	@return   	void
			*	@param		UInt uiLightID
			*	@param		Float4 pos
			*	@param		U1 bPointLight
			*	@param		Float4 diff
			*	@note
			*
			**/
			void	UpdataLight(UInt uiLightID,Float4 pos,Float4 diff);
	
			/**	\brief	��Ⱦ����֮ǰ���ô˺��� ���Լ������������и���
			*   
			*	@remarks 	�ڲ����вſ����Զ���
			*	@see		GlobalSetting
			*	@return   	void
			*	@param		Float44 * pMatrix
			*	@note
			*
			**/
			void	UpdataWorldMatrix(Float44*	pMatrix);
	
			//�����λ�ó���
			Float3				m_vCurrentPosition;
			Float3				m_vCurrentLookAt;
			Float3				m_vCurrentUpDirection;
			Float3				m_vCurrentDirection;
			Float3				m_vCurrentRightDirection;
			//����
			Float44				m_matView;
			Float44				m_matProj;
			Float44				m_matViewProj;
			Float44				m_matShadow[MAX_LIGHT];
			Float44				m_matWorld;
			Float44				m_matWorldView;
			Float44				m_matWorldViewProj;
			Float44				m_matViewProjI;
	
			//������
			Float4				m_AmibentColor;
			//�ƹ�
			VectorArray			m_LightPosition;
			VectorArray			m_LightDiffuse;
	
			//��Ļ
			Real				m_iScreenWidth;
			Real				m_iScreenHeight;
	
			//�����
			Real				m_fFOV;
			Real				m_fASpect;
			Real				m_fNearCullDistance;
			Real				m_fFarCullDistance;
	
			//ʱ��
			Real				m_fTimeDelta;
			Real				m_fTotalTime;
	
			Real				m_fEngineTimeDelta;
			Real				m_fEngineTotalTime;
	
			Float3						m_vBoundMin;			///<	��Χ����Сֵ
			Float3						m_vBoundMax;			///<	��Χ�����ֵ
			Float4						m_vBoundSphere;			///<	��Χ��
	
			Float4						m_vCursorPosition;		///<	���λ��
			Float4						m_vCursorMove;			///<	����ƶ���
	
			Texture*			m_pShadowTexture[MAX_LIGHT];		///<	ƽ�й�;۹�Ƶ�
			Texture*			m_pShadowTextureCube[MAX_LIGHT];	///<	���Դ����Ӱ���
	
		protected:
			U1							m_bLeftHand;			///<	�Ƿ�ʹ����������ϵ
			U1							m_bUpDirY;				///<	������
		public:
			U1	IsLeftHand(){
				return	m_bLeftHand;
			};
			U1	IsUpDirY(){
				return	m_bUpDirY;
			};
			U1							m_bRenderShadow;		///<	�Ƿ�����Ⱦ��Ӱ
	
	
			U1							m_bPostComposer;				///<	�Ƿ�Ϊ����Ч������
			Texture*					m_pLastPostComposerResult;		///<	��һ������Ч������������
			Material*					m_pCurrentPostComposerMaterial;	///<	��ǰ����Ч������
			Texture*					m_pBoneTexture;
	
	
			MatrixArray					m_BoneMatrixArray;				///<	��������
			UInt						m_uiNumBone;					///<	��������
	
		};
	
	};
};
#endif // ENGINESHADERSHAREPARAM_HEAD_FILE