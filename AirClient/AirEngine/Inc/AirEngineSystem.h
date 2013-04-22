//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  g:\tj.src\Client0400\Engine
 \filename  EngineSystem.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINESYSTEM_HEAD_FILE
#define ENGINESYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineSystem.h"
#include "AirEngineScene.h"
#include "AirInterfaceAlphaObjectManager.h"
#include "AirInterfaceAutoReleaseManager.h"


namespace Air{
	
	
	namespace Engine{
		
	
		class ENGINE_EXPORT	System	
			:	public	IFactoryManager,
				public	IAutoReleaseManager,
				public	Common::SystemManagerGroup,
				public	Singleton<System>{
		public:
			System();
			virtual	~System();
			/**	\brief	��ʼ��
			*   
			*	@remarks 	��ʼ��
			*	@see		IPlugin
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool	Initialization();
			/**	\brief	��ʼ
			*   
			*	@remarks 	��ʼ
			*	@see		IPlugin
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool	Start();
	
			/**	\brief	ֹͣ
			*   
			*	@remarks 	ֹͣ
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Stop();
			/**	\brief	�ͷ�
			*   
			*	@remarks 	�ͷ�
			*	@see		IPlugin
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool	Release();
			/**	\brief	��Ⱦǰ�ĸ��º����ص�
			*   
			*	@remarks 	��Ⱦǰ�ĸ��º����ص�
			*	@see		IEngine
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	ExecuteOneFrame(const FrameTime& frameTime);
			/**	\brief	�л�ϵͳǰ
			*   
			*	@remarks 	�л�ϵͳǰ
			*	@see		SystemManagerListener
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@param		ISystem * pOldSys
			*	@param		ISystem * pNewSystem
			*	@note
			*
			**/
			virtual	void	BeforeSwitchSystem(	Common::ISystemManager*	pSystemMgr,
												Common::ISystem*		pOldSys,
												Common::ISystem*		pNewSystem);
			/**	\brief	�л�ϵͳ��
			*   
			*	@remarks 	�л�ϵͳ��
			*	@see		SystemManagerListener
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@param		ISystem * pOldSys
			*	@param		ISystem * pNewSystem
			*	@note
			*
			**/
			virtual	void	OnSwitchSystem(	Common::ISystemManager*	pSystemMgr,
											Common::ISystem*		pOldSys,
											Common::ISystem*		pNewSystem);
			/**	\brief	�л�ϵͳ��ɺ�
			*   
			*	@remarks 	�л�ϵͳ��ɺ�
			*	@see		SystemManagerListener
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@param		ISystem * pOldSys
			*	@param		ISystem * pNewSystem
			*	@note
			*
			**/
			virtual	void	AfterSwitchSystem(	Common::ISystemManager*	pSystemMgr,
												Common::ISystem*		pOldSys,
												Common::ISystem*		pNewSystem);


		protected:
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			U1	CreateWin();
			/**	\brief	������ʾ�����ļ�
			*   
			*	@remarks 	������ʾ�����ļ�
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			U1	ParseDisplayParam();
	
			/**	\brief	������
			*   
			*	@remarks 	������
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			U1	LoadPlugin();

			U1	LoadPlugin(CAString&	strPluginName);
	
			/**	\brief	ж�ز��
			*   
			*	@remarks 	ж�ز��
			*	@see		CEngineSystem
			*	@return   	U1
			*	@note
			*
			**/
			U1	UnLoadPlugin();
		private:
			STD_VECTOR<AString>			m_strPluginNameArray;
			STD_VECTOR<Common::Plugin*>	m_vecPlugin;
			AString						m_strWindowName;
		};
	
		
	
	};
	typedef Engine::System EngineSystem;
};
#endif // ENGINESYSTEM_HEAD_FILE