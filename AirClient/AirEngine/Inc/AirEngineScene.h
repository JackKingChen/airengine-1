#ifndef ENGINESCENE_HEAD_FILE
#define ENGINESCENE_HEAD_FILE

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirEngineSceneNode.h"
#include "AirEngineLight.h"
#include "AirInterfaceParticle.h"
#include "AirSceneLoader.h"
namespace Air{
	
	namespace Client{
		namespace	Render{
			class	Target;
			class	ITexture;
			class	IMaterial;
			class	Queue;
		}
		class	Camera;
		class	Light;
		class	ScreenEntity;
		class	PostComposer;
		
	
	
	
		class	ENGINE_EXPORT	Scene	:
			public	IFactoryManager{
		public:
			Scene(CAString&	strName);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Scene
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1			Initialization();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		Scene
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1			Release();
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Scene
			*	@return   	void
			*	@note
			*
			**/
			virtual	void		Updata();
			/**	\brief	��ȡ���ڵ�
			*   
			*	@remarks 	��ȡ���ڵ�
			*	@see		Scene
			*	@return   	SceneNode*
			*	@note
			*
			**/
			SceneNode*			GetRootNode();

	
			/**	\brief	���������
			*   
			*	@remarks 	���������
			*	@see		Scene
			*	@return   	void
			*	@param		Camera * pCamera
			*	@note
			*
			**/
			void				SetMainCamera(Camera*	pCamera);
			/**	\brief	��ȡ�����
			*   
			*	@remarks 	��ȡ�����
			*	@see		Scene
			*	@return   	Camera*
			*	@note
			*
			**/
			Camera*				GetMainCamera();
	
			/**	\brief	�����ƹ�
			*   
			*	@remarks 	�����ƹ�
			*	@see		Scene
			*	@return   	Light*
			*	@param		AString strName
			*	@param		Light::enumType type
			*	@param		U1	bCastShadow
			*	@note
			*
			**/
			Light*				CreateLight(AString	strName,Light::enumType type,U1	bCastShadow	=	false);
			/**	\brief	�ݻٵƹ�
			*   
			*	@remarks 	�ݻٵƹ�
			*	@see		Scene
			*	@return   	void
			*	@param		Light * pLight
			*	@note
			*
			**/
			void				DestroyLight(Light*	pLight);

	
			/**	\brief	���������
			*   
			*	@remarks 	���������
			*	@see		Scene
			*	@return   	Camera*
			*	@note
			*
			**/
			Camera*				CreateCamera(AString	strName);
			/**	\brief	�ݻ������
			*   
			*	@remarks 	�ݻ������
			*	@see		Scene
			*	@return   	void
			*	@note
			*
			**/
			void				DestroyCamera(Camera*	pCamera);
			
	
			/**	\brief	��������Ч��
			*   
			*	@remarks 	
			*	@see		Scene
			*	@return   	void
			*	@param		AString strName
			*	@note
			*
			**/
			void				PlayParticle(AString	strName,Float3 vPosition,Float3 vNormal);
	
			void				SaveTargetToFile();


			void				UpdateSceneTree();
			void				FindMovableObject(Camera*	pCamera);


			SceneNode*			GetDynamicSceneNode();
			SceneNode*			GetStaticSceneNode();
			SceneNode*			GetParticleSceneNode();
			SceneNode*			GetTerrainSceneNode();
		protected:

	
		protected:
			//AString			m_strName;
			SceneNode		m_pRootNode;			///<	���ڵ�
			SceneNode		m_DynamicNode;
			SceneNode		m_StaticNode;
			SceneNode		m_ParticleNode;
			SceneNode		m_TerrainNode;
			Camera*			m_pMainCamera;				///<	Ĭ�������
	
			U1				m_bShadowEnable;
			typedef		std::list<Render::Target*>	RenderTargetList;
			typedef		RenderTargetList::iterator	RenderTargetListItr;
			typedef		std::list<Light*>			LightList;
			typedef		LightList::iterator			LightListItr;
			typedef		std::list<PostComposer*>	PostComposerList;
			typedef		PostComposerList::iterator	PostComposerListItr;
	
			RenderTargetList	m_lstRenderTarget;	///<	��ȾĿ���б�
			LightList			m_lstLight;
	
			Render::Target*	m_pSceneTarget;				///<	����Ŀ��
			Render::Target*	m_pAlphaSceneTarget;		///<	��͸��������ȾĿ��
			Render::ITexture*	m_pDefferedResult;
	
			ScreenEntity*		m_pScreenEntity;			///<	��Ļ��Ⱦ����
			PostComposerList	m_lstPostComposer;			///<	����Ч���б�
	
//			Render::IMaterial*	m_pScreenMaterial;			///<	������Ⱦ����Ļ�Ĳ���
//			Render::IMaterial*	m_pDefferedMaterial;		///<	�ӳ���ɫ	�ƹ⴦�����
	
			U1					m_bRenderWithoutComposer;	///<	��ʹ�ú���Ч����Ⱦ
			U1					m_bDeferredRender;			///<	�Ƿ������ӳ���ɫ
			U1					m_bRenderAlphaObject;		///<	�Ƿ�ֻ��Ⱦ��͸������
	
			//Render::Queue*		m_pRenderQueue;				///<	��Ⱦ����

			SceneLoader			m_Loader;
		};
	
	};
};
#endif // ENGINESCENE_HEAD_FILE