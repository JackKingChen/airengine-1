//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/08
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  EngineCharacterAnimationModel.h
 \note     
       
 \attention:
			����ģ��
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINECHARACTERANIMATIONMODEL_HEAD_FILE
#define ENGINECHARACTERANIMATIONMODEL_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirEngineCharacterResource.h"
#include "AirEngineRenderable.h"

class	CalModel;
class	CalHardwareModel;
namespace Air{
	namespace	Common{
		class	Float44;
	}
	
	namespace Engine{
	
		
		namespace	Character{
			class	ModelTemplate;
			/**	\brief	 �������
			*
			*	�������
			*
			***/
			namespace	Animation{
				typedef	CalModel							CoreAnimation;	
				/**	\brief	����״̬
				*
				*	����״̬
				*
				***/
				enum	enumActionState{
					ACT_STATE_IDLE,
					ACT_STATE_WALK,
					ACT_STATE_RUN,
					ACT_STATE_RIDE_IDLE,
					ACT_STATE_RIDE_WALK,
					ACT_STATE_RIDE_RUN,
					ACT_STATE_FLY_IDLE,
					ACT_STATE_FIY_WALK,
					ACT_STATE_FLY_RUN,
					ACT_STATE_SWIM_IDLE,
					ACT_STATE_SWIM_WALK,
					ACT_STATE_SWIM_RUN,
					ACT_STATE_DIE,
					ACT_STATE_MAX
				};
				class Model;
				/**	\brief	װ��
				*
				*	װ��
				*
				***/
				class Equipment	:
					public	Renderable{
				public:
					/**	\brief	װ������
					*
					*	װ������
					*
					***/
					enum	enType{
						enFace,
						enChest,
						enShoulder,
						enArm,
						enHand,
						enGloves,
						enwaist,
						enLeg,
						enShoe,
						enFoot,
						enMantle,
						enLeftWeapon,
						enRightWeapon,
						enHair,
						enMax
	
					};
					/**	\brief	ͨ��ID��ȡװ����������
					*   
					*	@remarks 	ͨ��ID��ȡװ����������
					*	@see		Equipment
					*	@return   	AString
					*	@param		enType type
					*	@note
					*
					**/
					static	AString	GetTypeNameByID(enType type);
					/**	\brief	ͨ��װ�����ֻ�ȡID
					*   
					*	@remarks 	ͨ��װ�����ֻ�ȡID
					*	@see		Equipment
					*	@return   	Client::Character::Animation::Equipment::enType
					*	@param		AString strName
					*	@note
					*
					**/
					static	enType	GetTypeIDByName(AString	strName);
	
					
				public:
					Equipment(CoreAnimation*	pCoreAnimation,enType type,Model*	pParent);
					virtual ~Equipment();
	
					/**	\brief	����װ��
					*   
					*	@remarks 	����װ��
					*	@see		Equipment
					*	@return   	U1
					*	@param		UInt uiMeshID
					*	@param		AString strMeshName
					*	@param		AString strMaterialName
					*	@note
					*
					**/
					U1			Create(	UInt			uiMeshID,
										CAString&		strMeshName,
										CAString&		strMaterialName,
										UInt**			pSubMesh	=	NULL);
					/**	\brief	����װ��
					*   
					*	@remarks 	����װ��
					*	@see		Equipment
					*	@return   	U1
					*	@param		UInt uiMeshID
					*	@param		AString strMeshName
					*	@param		AString strMaterialName
					*	@param		MeshHDBuffer * pHDBuff
					*	@note
					*
					**/
					U1			Create(	UInt			uiMeshID,
										CAString&		strMeshName,
										CAString&		strMaterialName,
										MeshHDBuffer*	pHDBuff		=	NULL);
					/**	\brief	�ݻ�װ��
					*   
					*	@remarks 	�ݻ�װ��
					*	@see		Equipment
					*	@return   	void
					*	@note
					*
					**/
					void		Destroy();
					/**	\brief	��ȡװ������
					*   
					*	@remarks 	��ȡװ������
					*	@see		Equipment
					*	@return   	AString
					*	@note
					*
					**/
					inline	CAString&		GetEquipmentName()const{return m_strName;};
	
					U1			IsNull();
					SInt		GetMeshID(){return m_uiMeshID;};

					virtual	U32			GetBoneCount();
					virtual	Float44*	GetBoneMatrix();
					virtual	Float44*	GetWorldMatrix();
				protected:
					enType					m_uiEquipmentType;				///<	����ID
					SInt					m_uiMeshID;						///<	ģ��ID
	
					CoreAnimation*			m_pCoreAnimation;				///<	������ָ��
					AString					m_strName;						///<	װ������
					Model*					m_pModel;
				};
				typedef	std::map<UInt,Equipment*>		EquipmentMap;		///<	װ���б�
				typedef	EquipmentMap::iterator			EquipmentMapItr;	///<	װ���б������
				typedef	EquipmentMap::value_type		EquipmentMapPair;	///<	װ���б�����
	
				/**	\brief	������Ϣ
				*
				*	������Ϣ
				*
				***/
				struct Action{
					AString					m_strName;						///<	��������
					UInt					m_uiActionID;					///<	����ID
				};
	
				typedef	std::map<AString,Action>		ActionMap;			///<	�����б�		
				typedef	ActionMap::iterator				ActionMapItr;		///<	�����б������
				typedef	ActionMap::value_type			ActionMapPair;		///<	�����б�����
	
				typedef	stdext::hash_map<UInt*,Equipment*>	EquipmentMeshMap;
				typedef	EquipmentMeshMap::iterator			EquipmentMeshMapItr;
				typedef	EquipmentMeshMap::value_type		EquipmentMeshMapPair;
				/**	\brief	����ģ��
				*
				*	����ģ��
				*
				***/
				class	ENGINE_EXPORT	Model	:
					public	Common::IProduct,
					public	MovableObject
				{
				public:
					static AString ProductTypeName;
					/**	\brief	������Ϣ
					*
					*	������Ϣ
					*
					***/
					struct Info{
						AString	strTemplate;	///<	��ԴĿ¼
						
					};
				public:
					Model(CAString&	strName,Info* pInfo);
					virtual ~Model();
	
					Real	GetAnimationSpeed();
					void	SetAnimationSpeed(Real	fSpeed	=	1.0f);
					void	SetAnimationSpeedOffset(Real	fSpeedOffset	=	-0.01f);
	
					/**	\brief	���װ��
					*   
					*	@remarks 	����ò�λ����װ��  ����ǰ��װ���ᱻ����
					*	@see		Model
					*	@return   	U1
					*	@param		AString strName
					*	@param		AString strMaterial
					*	@param		AString strTypeName
					*	@note
					*
					**/
					virtual U1				AddEquipment(CAString&	strName,CAString& strMaterial,CAString& strTypeName);
					/**	\brief	���װ��
					*   
					*	@remarks 	���װ��
					*	@see		Model
					*	@return   	U1
					*	@param		AString strName
					*	@param		AString strMaterial
					*	@param		Equipment::enType type
					*	@note
					*
					**/
					virtual U1				AddEquipment(CAString&	strName,CAString& strMaterial,Equipment::enType type);
					/**	\brief	�Ƴ�һ��װ��
					*   
					*	@remarks 	�Ƴ�һ��װ��
					*	@see		Model
					*	@return   	U1
					*	@param		AString strTypeName
					*	@note
					*
					**/
					virtual U1				RemoveEquipment(CAString&	strTypeName);
					/**	\brief	�Ƴ�һ����λ��װ��
					*   
					*	@remarks 	�Ƴ�һ����λ��װ��
					*	@see		Model
					*	@return   	U1
					*	@param		Equipment::enType type
					*	@note
					*
					**/
					virtual U1				RemoveEquipment(Equipment::enType type);
				
					/**	\brief	����ָ����������ϵ���ǰ״̬��
					*   
					*	@remarks 	����ָ������
					*	@see		Model
					*	@return   	U1
					*	@param		AString strActionName
					*	@param		Real fBlendTime
					*	@note
					*
					**/
					virtual U1				PlayAction(CAString&	strActionName,Real	fBlendTime	=	0.3f);
					//virtual U1				PlayAction(AString	strActionName,Real	fBlendTime	=	0.3f);
					/**	\brief	���ö���״̬
					*   
					*	@remarks 	���ö���״̬
					*	@see		Model
					*	@return   	U1
					*	@param		AString strCycleActionName
					*	@param		Real fBlendTime
					*	@note
					*
					**/
					virtual U1				SetActionState(CAString&	strCycleActionName,Real	fBlendTime	=	0.3f);
					/**	\brief	ͬʱ���2��ѭ������
					*   
					*	@remarks 	ͬʱ���2��ѭ������
					*	@see		Model
					*	@return   	U1
					*	@param		AString strState0
					*	@param		AString strState1
					*	@param		Real fWeight0
					*	@param		Real fBlendTime
					*	@note
					*
					**/
					virtual	U1				SetActionState(CAString&	strState0,CAString&	strState1,Real	fWeight0	=	0.5f,Real	fBlendTime	=	0.3f);
					/**	\brief	��ȡ����״̬
					*   
					*	@remarks 	��ȡ����״̬
					*	@see		Model
					*	@return   	AString
					*	@note
					*
					**/
					virtual AString			GetActionState();
	
					/**	\brief	��ȡϸ�ڲ��
					*   
					*	@remarks 	��ȡϸ�ڲ��
					*	@see		Model
					*	@return   	Real
					*	@note
					*
					**/
					virtual Real			GetLodLevel();
					/**	\brief	����ϸ�ڲ��
					*   
					*	@remarks 	����ϸ�ڲ��
					*	@see		Model
					*	@return   	void
					*	@param		Real fLodLevel
					*	@note
					*
					**/
					virtual void			SetLodLevel(Real fLodLevel);
	
					/**	\brief	����
					*   
					*	@remarks 	����
					*	@see		Model
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1				Create();
					/**	\brief	�ݻ�
					*   
					*	@remarks 	�ݻ�
					*	@see		Model
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1				Destroy();
	
					/**	\brief	����
					*   
					*	@remarks 	����
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual void			Update(const FrameTime& frameTime);
					/**	\brief	��Ⱦ
					*   
					*	@remarks 	��Ⱦ
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual void			Render();
	
					/**	\brief	�����Ⱦ
					*   
					*	@remarks 	�����Ⱦ
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual	void			RenderSoftWare();
					/**	\brief	Ӳ����Ⱦ
					*   
					*	@remarks 	Ӳ����Ⱦ
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual	void			RenderHardWare();
	
	
					/**	\brief	��ȡ��������
					*   
					*	@remarks 	��ȡ��������
					*	@see		Model
					*	@return   	void
					*	@param		UInt uiIndex
					*	@param		Float3 * pPos
					*	@param		Float4 * pQ
					*	@note
					*
					**/
					void					GetBoneMatrix(UInt	uiIndex,Float3*	pPos,Float4*	pQ	=	NULL);
					Float44*				GetBoneMatrix();
					U32						GetBoneCount()const;
					/**	\brief	�󶨵�������
					*   
					*	@remarks 	�󶨵�������
					*	@see		Model
					*	@return   	U1
					*	@param		AString	strBoneName
					*	@param		MovableObject * pObject
					*	@note
					*
					**/
					U1						AttachObject2Bone(AString	strBoneName,MovableObject*	pObject);
					SceneNode*				GetBoneSceneNode(AString	strBoneName);
					/**	\brief	�Ƴ���
					*   
					*	@remarks 	�Ƴ���
					*	@see		Model
					*	@return   	U1
					*	@param		MovableObject * pObject
					*	@note
					*
					**/
					U1						detachObject(MovableObject*	pObject);
					/**	\brief	��Ⱦ������
					*   
					*	@remarks 	��Ⱦ������
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					void					RenderAttachObject();
					/**	\brief	���°�����
					*   
					*	@remarks 	���°�����
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					void					UpdateAttachObject();


					virtual	void			ProcessRenderObject(U32	uiPhaseFlag);
				protected:
					CoreAnimation*			m_pAnimation;
					Resource*				m_pResource;			///<	��Դ
					Real					m_fLodLevel;			///<	LODϸ�ڲ��
					AString					m_strCurrentCycleAction;///<	��ǰ����״̬
	
					EquipmentMap			m_mapEquipment;			///<	װ���б�
					ActionMap				m_mapAnimation;			///<	�����б�
					ActionMap				m_mapCycleAnimation;	///<	ѭ�������б�
	
					EquipmentMeshMap		m_mapEquipmentMesh;		///<	������װ���Ķ�Ӧ��ϵ��
	
					Info					m_Info;
	
					Real					m_fAnimationSpeed;		///<	�����ٶ�
	
	
					typedef	std::map<MovableObject*,SceneNode*>	AttachObjectMap;
	// 				typedef	std::map<UInt,AttachObject>	AttachObjectMap;
	 				typedef	AttachObjectMap::iterator	AttachObjectMapItr;
	 				typedef	AttachObjectMap::value_type	AttachObjectMapPair;
	// 				typedef	std::map<MovableObject*,UInt>	ObjectIndexMap;
	
					typedef	std::map<AString,SceneNode*>			BoneNodeMap;
					typedef	BoneNodeMap::iterator					BoneNodeMapItr;
					typedef	BoneNodeMap::value_type					BoneNodeMapPair;
					
	
					AttachObjectMap			m_mapAttachObjects;
					BoneNodeMap				m_mapBoneNode;
					//ObjectIndexMap			m_mapObjectIndex;
	
					CriticalSection			m_CS;

					Float44*				m_BoneMatrix;
					U32						m_uiBoneCount;
					ModelTemplate*			m_pTemplate;

					Action					m_CycleAnimation[3];
				};

			};
		}
	
	};
};
#endif // ENGINECHARACTERAIMATION_HEAD_FILE