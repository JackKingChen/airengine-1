#ifndef COMMONSYSTEMMANAGER_HEAD_FILE
#define COMMONSYSTEMMANAGER_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirInterfaceObject.h"
#include "AirCommonFactory.h"
#include "AirCommonListener.h"

namespace Air{
	namespace Common{
		
		/**	\brief	����ϵͳ��
		*
		*	����ϵͳ��
		*
		***/
		class	ISystem
			:	public	IObject,
				public	IFactoryManager{
		public:
			ISystem(CAString&	strType):m_strType(strType){
			};
			virtual	~ISystem(){};

			/**	\brief	��ʼ��ϵͳ
			*   
			*	@remarks 	��ʼ��ϵͳ
			*	@see		ISystem
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Initialization()=	NULL;
			/**	\brief	�ͷ�ϵͳ
			*   
			*	@remarks 	�ͷ�ϵͳ
			*	@see		ISystem
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Release()		=	NULL;
			/**	\brief	��ʼ
			*   
			*	@remarks 	��ʼ
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Start()			=	NULL;
			/**	\brief	ֹͣ
			*   
			*	@remarks 	ֹͣ
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Stop()			=	NULL;

			AString		GetType(){
				return	m_strType;
			}

			AString		m_strType;
		};
	
		typedef	std::map<AString,ISystem*>	SystemMap;
		typedef	SystemMap::iterator			SystemMapItr;
		typedef	std::list<ISystem*>			SystemList;
		typedef	SystemList::iterator		SystemListItr;


		class	ISystemManager;
		/**	\brief	ϵͳ���������
		*
		*	ϵͳ���������
		*
		***/
		class	COMMON_EXPORT	SystemManagerListener{
		public:
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
			virtual	void	BeforeSwitchSystem(ISystemManager*	pSystemMgr,ISystem*	pOldSys,ISystem*	pNewSystem)	=	NULL;
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
			virtual	void	OnSwitchSystem(ISystemManager*	pSystemMgr,ISystem*	pOldSys,ISystem*	pNewSystem)		=	NULL;
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
			virtual	void	AfterSwitchSystem(ISystemManager*	pSystemMgr,ISystem*	pOldSys,ISystem*	pNewSystem)	=	NULL;
		};

		/**	\brief	ϵͳ������
		*
		*	ϵͳ������
		*
		***/
		class	COMMON_EXPORT	ISystemManager
			:	public	IObject,
			public	SimpleListenManager<SystemManagerListener>{
		public:
			ISystemManager(CAString&	strTypeName);
			virtual	~ISystemManager();

			/**	\brief	��ʼ��������
			*   
			*	@remarks 	���ҳ�ʼ�����õ�
			*	@see		ISystemManager
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Initialization();

			/**	\brief	�ͷ�
			*   
			*	@remarks 	�ͷ� ���һ��ͷŵ�ǰ����Ĳ��
			*	@see		ISystemManager
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	Release();

			/**	\brief	���ص�ǰ�����ϵͳ
			*   
			*	@remarks 	���ص�ǰ�����ϵͳ
			*	@see		ISystemManager
			*	@return   	ISystem*
			*	@note
			*
			**/
			inline	ISystem*	GetActiveSystem(){
				return	m_pActiveSys;
			};
			
			/**	\brief	���ص�ǰ�����ϵͳ
			*   
			*	@remarks 	���ص�ǰ�����ϵͳ
			*	@see		ISystemManager
			*	@return   	T_System*
			*	@note
			*
			**/
			template<typename	T_System>
			T_System*			GetActiveSystem(){
				if(m_pActiveSys==NULL)
					return	NULL;
				else
					return	dynamic_cast<T_System*>(m_pActiveSys);
			}
			/**	\brief	���ü���ϵͳ
			*   
			*	@remarks 	���ü���ϵͳ	���ǲ���ʼ��ϵͳ
			*	@see		ISystemManager
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			inline	void		SetActiveSystem(ISystem*	pSys){
				if(m_pActiveSys!=NULL){
					m_pActiveSys->Release();
				}
				m_pActiveSys	=	pSys;
			};

			/**	\brief	�л�ϵͳ
			*   
			*	@remarks 	�л�ϵͳ	��ֱ�ӳ�ʼ���µ�ϵͳ
			*	@see		ISystemManager
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			void				SwitchSystem(ISystem*	pSys);
			/**	\brief	���ص�ǰ�Ѿ���ӵ�ϵͳ�б�
			*   
			*	@remarks 	���ص�ǰ�Ѿ���ӵ�ϵͳ�б�
			*	@see		ISystemManager
			*	@return   	Air::Common::SystemList
			*	@note
			*
			**/
			SystemList			GetSystemList();

			/**	\brief	���ϵͳ
			*   
			*	@remarks 	���ϵͳ
			*	@see		ISystemManager
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			virtual	void		AddSystem(ISystem*	pSys);
			/**	\brief	�Ƴ�ϵͳ
			*   
			*	@remarks 	�Ƴ�ϵͳ
			*	@see		ISystemManager
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			virtual	void		RemoveSystem(ISystem*	pSys);

			
			inline	CAString&	GetName(){return m_strName;};
		protected:
			SystemList	m_lstSystem;		///<	ϵͳ�б�
			ISystem*	m_pActiveSys;		///<	��ǰ�����ϵͳ
			AString		m_strName;
		};

		typedef	std::map<AString,ISystemManager*>	SystemManagerMap;
		typedef	SystemManagerMap::iterator			SystemManagerMapItr;
		typedef	std::list<ISystemManager*>			SystemManagerList;
		typedef	SystemManagerList::iterator			SystemManagerListItr;

		/**	\brief	ϵͳ����������
		*
		*	ϵͳ����������
		*
		***/
		class	COMMON_EXPORT	SystemManagerGroup
			:	public	SystemManagerListener{
		public:
			SystemManagerGroup();
			virtual	~SystemManagerGroup();

			/**	\brief	���һ��ϵͳָ��
			*   
			*	@remarks 	���һ��ϵͳָ��
			*	@see		SystemManagerGroup
			*	@return   	void
			*	@param		ISystem * pSys
			*	@param		U1	bInitWhenNewManager
			*	@note
			*
			**/
			void		AddSystem(ISystem*	pSys,U1	bInitWhenNewManager	=	false);
			/**	\brief	�Ƴ�һ��ϵͳ
			*   
			*	@remarks 	�Ƴ�һ��ϵͳ
			*	@see		SystemManagerGroup
			*	@return   	void
			*	@param		ISystem * pSys
			*	@note
			*
			**/
			void		RemoveSystem(ISystem*	pSys);
			/**	\brief	���ص�ǰ�����ϵͳ
			*   
			*	@remarks 	���ص�ǰ�����ϵͳ
			*	@see		ISystemManager
			*	@return   	T_System*
			*	@note
			*
			**/
			template<typename	T_System>
			T_System*			GetActiveSystem(AString	strSysType){
				SystemManagerMapItr i	=	m_mapSystemMgr.find(strSysType.c_str());
				if(i!=m_mapSystemMgr.end()){
					ISystemManager*	pSystemMgr	=	i->second;
					if(pSystemMgr!=NULL){
						return	pSystemMgr->GetActiveSystem<T_System>();
					}
				}
				return	NULL;
			};

			/**	\brief	���һ��ϵͳ������
			*   
			*	@remarks 	���һ��ϵͳ������
			*	@see		SystemManagerGroup
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@param		U1	bInit
			*	@note
			*
			**/
			void	AddSystemManager(ISystemManager*	pSystemMgr,U1	bInit	=	false);
			/**	\brief	�Ƴ�һ��ϵͳ������
			*   
			*	@remarks 	�Ƴ�һ��ϵͳ������
			*	@see		SystemManagerGroup
			*	@return   	void
			*	@param		ISystemManager * pSystemMgr
			*	@note
			*
			**/
			void	RemoveSystemManager(ISystemManager*	pSystemMgr);

			/**	\brief	��ʼ������ϵͳ������
			*   
			*	@remarks 	��ʼ������ϵͳ������
			*	@see		SystemManagerGroup
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	InitAllSystemManager();
			/**	\brief	�ͷ�����ϵͳ������
			*   
			*	@remarks 	�ͷ�����ϵͳ������
			*	@see		SystemManagerGroup
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	ReleaseAllSystemManager();

			/**	\brief	��������ϵͳ����
			*   
			*	@remarks 	��������ϵͳ����
			*	@see		SystemManagerGroup
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	StartAllSystemManager();

			/**	\brief	ֹͣ����ϵͳ������
			*   
			*	@remarks 	ֹͣ����ϵͳ������
			*	@see		SystemManagerGroup
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1	StopAllSystemManager();

			SystemManagerMap	m_mapSystemMgr;		///<	��ѯ��
			SystemManagerList	m_lstSystemMgr;		///<	˳���

		};
	
	};
};
#endif // COMMONSYSTEMMANAGER_HEAD_FILE