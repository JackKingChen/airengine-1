//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Thread.h
 \note     
       
 \attention:�߳���
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONTHREAD_HEAD_FILE
#define COMMONTHREAD_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
namespace Air{
	
	
	namespace	Common{
		/**	\brief	�߳���
		*
		*	������һ���߳� ��ʹ�������
		*
		***/
		class COMMON_EXPORT Thread	:public	MemoryObject{
	
		public:
			Thread();
			virtual ~Thread();
			/**	\brief	��ʼִ��
			*   
			*	@remarks 	��ʼִ��
			*	@see		Thread
			*	@return   	bool
			*	@note		�����̵߳�ǰ��״̬�� ���� ��ͣ ֹͣ�����ô˺������ἤ���߳�
			*
			**/
			virtual bool StartThread();
			/**	\brief	ֹͣ�߳�
			*   
			*	@remarks 	ֹͣ�߳�
			*	@see		Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool StopThread();
	
			/**	\brief	ֹͣ�߳�
			*   
			*	@remarks 	���ҵȵ����߳��˳�
			*	@see		Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual	bool StopThreadWaitForExit();
	
			/**	\brief	ֹͣ�߳�
			*   
			*	@remarks 	�ȵ���ʱ	��ʱ��ǿ���ս�
			*	@see		Thread
			*	@return   	bool
			*	@param		int iTime
			*	@note
			*
			**/
			virtual	bool StopThreadWaitTimeOut(int iTime);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool Suspend();
			/**	\brief	�ָ�
			*   
			*	@remarks 	�ָ�
			*	@see		Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool Resume();
			/**	\brief	������ͣʱ�����߼��
			*   
			*	@remarks 	��������ʱ��Ч
			*	@see		Thread
			*	@return   	void
			*	@param		unsigned int dwMilliseconds
			*	@note		
			*
			**/
			virtual void SetSleepTime(unsigned int dwMilliseconds = 10);
			/**	\brief	�ж��߳��Ƿ��ڼ���״̬
			*   
			*	@remarks 	����ͣ ֹͣ ���� ���᷵��false
			*	@see		Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool IsRunning();
			/**	\brief	��ͣ�߳�
			*   
			*	@remarks 	��ͣ�߳�
			*	@see		Thread
			*	@return   	bool
			*	@param		bool pause
			*	@note
			*
			**/
			virtual bool PauseThread(bool pause = true);
	
			/**	\brief	ͬ����ͣ�߳�
			*   
			*	@remarks 	��֤���߳��Ѿ�ִ���� һ��ѭ�� ���ڿ���״̬
			*	@see		Thread
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		PauseThreadSync();
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual U1		SuspendSync();
			/**	\brief	������Ҫ��д��ѭ�����ú���
			*   
			*	@remarks 	�߳������ִ�к���
			*	@see		Thread
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool RepetitionRun()=0;
	
			/**	\brief	��ȡ�߳̾��
			*   
			*	@remarks 	��ȡ�߳̾��
			*	@see		Thread
			*	@return   	HANDLE
			*	@note
			*
			**/
			HANDLE	GetHandle(){
				return	(HANDLE)m_hHandle;
			};
			/**	\brief	�߳������ִ�к���
			*   
			*	@remarks 	�߳������ִ�к���
			*	@see		Thread
			*	@return   	unsigned int __stdcall
			*	@param		void * pThread
			*	@note
			*
			**/
			static	unsigned int __stdcall Run(void* pThread);
		protected:	
			
			U1		m_bPause;				///<	��ͣ
			U1		m_bExit;				///<	�˳�
			U1		m_bSuspend;				///<	����
			HANDLE	m_hHandle;				///<	�߳̾��
			UInt	m_iThreadID;			///<	�߳�ID
			UInt	m_pSleepTime;			///<	���߼��ʱ��
	
			U1		m_bHasPause;			///<	�Ƿ��Ѿ���ͣ
		};
	}
};
#endif