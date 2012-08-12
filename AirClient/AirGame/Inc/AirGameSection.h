#ifndef GAMESECTION_HEAD_FILE
#define GAMESECTION_HEAD_FILE

#include "AirGame.h"
#include "AirGameHeader.h"
#include "AirGameControl.h"
namespace Air{
	
	namespace Client{
	
		namespace	Game{
			/**	\brief	���ػص�
			*
			*	���ػص�
			*
			***/
			class	ILoadingCallback{
			public:
				/**	\brief	��ʼ����
				*   
				*	@remarks 	��ʼ����
				*	@see		ILoadingCallback
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnLoadingStart(){};
				/**	\brief	���ؽ�����
				*   
				*	@remarks 	���ؽ�����
				*	@see		ILoadingCallback
				*	@return   	void
				*	@param		Real fPercent
				*	@note
				*
				**/
				virtual	void	OnLoadingProcess(Real	fPercent){};
				/**	\brief	���ؽ���
				*   
				*	@remarks 	���ؽ���
				*	@see		ILoadingCallback
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnLoadingFinished(){};
	
				/**	\brief	���볡��ǰ�ĵ���
				*   
				*	@remarks 	���볡��ǰ�ĵ���
				*	@see		ILoadingCallback
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnEnter(){};
	
				/**	\brief	�뿪�����ĵ���
				*   
				*	@remarks 	�뿪�����ĵ���
				*	@see		ILoadingCallback
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnLeave(){};
			};
			/**	\brief	��Ϸ�ؿ���
			*
			*	��Ϸ�ؿ���
			*
			***/
			class	GAME_EXPORT	Section	:
				public	Common::IProduct,
				public	Control,
				public	ILoadingCallback{
			public:
	
			public:
				Section(CAString&	strName);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Section
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Section
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Destroy();
	
				/**	\brief	��Ⱦ
				*   
				*	@remarks 	��Ⱦ
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual void	OnRender();
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnUpdata();
	
				/**	\brief	��ȾĿ��
				*   
				*	@remarks 	��ȾĿ��
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	OnRenderTarget();
	
				/**	\brief	���عؿ�
				*   
				*	@remarks 	���عؿ�
				*	@see		Section
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				virtual	U1		Load(AString	strName);
				/**	\brief	ж�عؿ�
				*   
				*	@remarks 	ж�عؿ�
				*	@see		Section
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		UnLoad();
				/**	\brief	GUI�¼��ص�
				*   
				*	@remarks 	GUI�¼��ص�
				*	@see		Section
				*	@return   	void
				*	@param		UINT nEvent
				*	@param		int nControlID
				*	@param		CDXUTControl * pControl
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual void	OnGUIEvent( UINT nEvent, int nControlID, void* pControl, void* pUserContext );
	
				/**	\brief	��ȡ����ָ��
				*   
				*	@remarks 	��ȡ����ָ��
				*	@see		Section
				*	@return   	Scene*
				*	@note
				*
				**/
				inline	Scene*			GetScene(){return	m_pScene;};
				/**	\brief	��ȡ��Ƶ����ָ��
				*   
				*	@remarks 	��ȡ��Ƶ����ָ��
				*	@see		Section
				*	@return   	Audio::IScene*
				*	@note
				*
				**/
				inline	Audio::IScene*	GetAudioScene(){return	m_pAudioScene;};
				/**	\brief	��ȡ������ָ��
				*   
				*	@remarks 	��ȡ������ָ��
				*	@see		Section
				*	@return   	Physx::IScene*
				*	@note
				*
				**/
				//inline	Physx::IScene*	GetPhysxScene(){return	m_pPhysxScene;};
	
				/**	\brief	���õ�ǰ�ؿ����������
				*   
				*	@remarks 	���õ�ǰ�ؿ����������
				*	@see		Section
				*	@return   	void
				*	@param		Camera * pCamera
				*	@note
				*
				**/
				virtual	void	SetCamera(Camera*	pCamera);
				/**	\brief	����Ĭ�������
				*   
				*	@remarks 	����Ĭ�������
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	Camera*	CreateDefaultCamera();
				/**	\brief	����Ĭ�Ͽ�����
				*   
				*	@remarks 	����Ĭ�Ͽ�����
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	Control*	CreateDefaultControl(Camera*	pSceneCamera);
	
				/**	\brief	���볡��
				*   
				*	@remarks 	���볡��
				*	@see		Section
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		OnEnter();
			protected:
				Scene*			m_pScene;			///<	������
				Audio::IScene*	m_pAudioScene;		///<	��Ƶ����
				//Physx::IScene*	m_pPhysxScene;		///<	������
	
				Camera*			m_pDefaultCamera;	///<	Ĭ�������
				Control*		m_pDefaultControl;	///<	Ĭ�Ͽ�����
	
			};
	
			class	SectionFactory	:
				public	Common::IFactory{
			public:
				SectionFactory();
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		BuffFactory
				*	@return   	Common::IProduct*
				*	@param		AString strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam =	NULL);
			};
		}
	};
};
#endif // GAMESECTION_HEAD_FILE