#ifndef GAMESYSTEM_HEAD_FILE
#define GAMESYSTEM_HEAD_FILE

#include "AirGame.h"
#include "AirInterfaceGameSystem.h"
#include "AirEngineSceneNode.h"

#include "AirInterfaceInputSystem.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Game{
			class	Section;
			/**	\brief	��Ϸϵͳ
			*
			*	��Ϸϵͳ
			*
			***/
			class GAME_EXPORT	System	:
				public	Common::ISystem,
				public	OIS::KeyListener,
				public	OIS::MouseListener,
				public	OIS::JoyStickListener{
			public:
				System();
				virtual ~System();
	
				/**	\brief	��ʼ��
				*   
				*	@remarks 	��ʼ��
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization();
	
				/**	\brief	��ʼ
				*   
				*	@remarks 	��ʼ
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Start();
	
				/**	\brief	ֹͣ
				*   
				*	@remarks	ֹͣ
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Stop();
	
				/**	\brief	�ͷ�
				*   
				*	@remarks 	�ͷ�
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release();
				/**	\brief	֡�ص�֪ͨ
				*   
				*	@remarks 	֡�ص�֪ͨ
				*	@see		ISystem
				*	@return   	void
				*	@param		Real fTotalTime
				*	@param		Real fDeltaTime
				*	@note
				*
				**/
				virtual void	OnFrameMove(Real fTotalTime,Real fDeltaTime);
				/**	\brief	��Ⱦǰ֪ͨ
				*   
				*	@remarks 	��Ⱦ֪ͨ
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual void	OnBeforeRender();
				/**	\brief	��Ⱦ֪ͨ
				*   
				*	@remarks 	��Ⱦ֪ͨ
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual void	OnRender();
				/**	\brief	��Ⱦ��֪ͨ
				*   
				*	@remarks 	��Ⱦ��֪ͨ
				*	@see		ISystem
				*	@return   	void
				*	@note
				*
				**/
				virtual void	OnAfterRender();
	
				/**	\brief	GUI�¼��ص�
				*   
				*	@remarks 	GUI�¼��ص�
				*	@see		IEngine
				*	@return   	void
				*	@param		UINT nEvent
				*	@param		int nControlID
				*	@param		CDXUTControl * pControl
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual void	OnGUIEvent( UINT nEvent, int nControlID, void* pControl, void* pUserContext );
	
	
	
				//����
				virtual bool keyPressed( const OIS::KeyEvent &arg );
				virtual bool keyReleased( const OIS::KeyEvent &arg );
				//���
				virtual bool mouseMoved( const OIS::MouseEvent &arg );
				virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
				virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
				//�ֱ�
				virtual bool buttonPressed( const OIS::JoyStickEvent &arg, int button );
				virtual bool buttonReleased( const OIS::JoyStickEvent &arg, int button );
				virtual bool axisMoved( const OIS::JoyStickEvent &arg, int axis );
	
				void		SwitchSection(AString	strName);
	
	
				void		SetNextSection(AString	strSectionName);
	
				void		SetDebugString(AString	strDebugString);
	
			protected:
				U1	LoadPlugin();
				U1	UnLoadPlugin();
	
				U1	LoadSection();
				U1	UnLoadSection();
			protected:
				SceneNode*		m_pRootNode;
			private:
				Section**		m_ppSection;
				Section**		m_ppLoadingSection;
				Section*		m_pCurrentSection;
				Section*		m_pTempSection;
				StringArray			m_strPluginNameArray;
				Common::PluginFactory*	m_pPluginMgr;
	
				std::map<AString,Plugin*>	m_mapSection;
				Plugin*			m_pCurrentPlugin;
	
				CriticalSection	m_CS;
				AString			m_strNextSectionName;
	
				AString			m_strFirstSectionName;
			};
		}
	
	};
};
#endif // GAMESYSTEM_HEAD_FILE