#ifndef COMMONLISTENER_HEAD_FILE
#define COMMONLISTENER_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonLock.h"

namespace Air{

	namespace	Common{
		/**	\brief	��һ����������
		*
		*	��һ����������
		*
		***/
		template<typename	T_Listener>
		class	SimpleListenManager{
		public:
			SimpleListenManager(){
				m_pListener	=	NULL;
			};


			/**	\brief	���ü�����
			*   
			*	@remarks 	���ü�����
			*	@see		SimpleListenManager
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			void	SetListener(T_Listener*	pListener){
				m_pListener	=	pListener;
			};
			T_Listener*	m_pListener;		///<	������
		};

		/**	\brief	�����������
		*
		*	�����������
		*
		***/
		template<typename T_Listener>
		class	MutilListenerManager{
		public:
			typedef	std::list<T_Listener*>	ListenerList;
			typedef	typename ListenerList::iterator	ListenerListItr;
		public:
			MutilListenerManager(){

			};
			virtual	~MutilListenerManager(){

			};

			/**	\brief	��ӹ�����
			*   
			*	@remarks 	��ӹ�����
			*	@see		MutilListenerManager
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			virtual	void	AddListener(T_Listener*	pListener){
				m_lstListener.push_back(pListener);
			};
			/**	\brief	��ӹ�����
			*   
			*	@remarks 	��ӹ�����
			*	@see		MutilListenerManager
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			virtual	void	RemoveListener(T_Listener*	pListener){
				m_lstListener.remove(pListener);
			};

			ListenerList	m_lstListener;	///<	�����б�
			
		};
		/**	\brief	�����������(����)
		*
		*	�����������(����)
		*
		***/
		template<typename T_Listener>
		class	MutilListenerManagerMT
			:	public	MutilListenerManager<T_Listener>{
		public:
			/**	\brief	��ӹ�����
			*   
			*	@remarks 	��ӹ�����
			*	@see		MutilListenerManagerMT
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			void	AddListener(T_Listener*	pListener){
				if(pListener==NULL)
					return;
				m_CS.Enter();
				m_lstListener.push_back(pListener);
				m_CS.Leave();
			};
			/**	\brief	�Ƴ�������
			*   
			*	@remarks 	�Ƴ�������
			*	@see		MutilListenerManagerMT
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			void	RemoveListener(T_Listener*	pListener){
				if(pListener==NULL)
					return;
				m_CS.Enter();
				m_lstListener.remove(pListener);
				m_CS.Leave();
			};
			//CriticalSection	m_CS;	///<	��ʱ������������ٽ��� ��Ҫ������������ٽ�����
		};
	}
	

};
#endif // COMMONLISTENER_HEAD_FILE