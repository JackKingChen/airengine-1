//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/06/03
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonLog.h
 \note     
       
 \attention:
			��־��
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONLOG_HEAD_FILE
#define COMMONLOG_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirSingleton.h"
#include "AirCommonLock.h"


#ifndef	LOG_BUFF_SIZE
#define LOG_BUFF_SIZE	4096
#endif

namespace Air{
	
	namespace Common{
		class	COMMON_EXPORT	Log	:
			public	MemoryObject,
			public	Singleton<Log>{
		public:
			Log();
			virtual	~Log();
			/**	\brief	д�뻺��
			*   
			*	@remarks 	д�뻺��
			*	@see		Log
			*	@return   	void
			*	@param		AString & strName
			*	@note
			*
			**/
			void	Write(CAString&	strName);
			/**	\brief	�����ļ���
			*   
			*	@remarks 	�����ļ���
			*	@see		Log
			*	@return   	void
			*	@note
			*
			**/
			void	SetFileName(AString&	strFileName);
		private:
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Log
			*	@return   	U1
			*	@note
			*
			**/
			U1	Create();
	
			/**	\brief	д���ļ�
			*   
			*	@remarks 	д���ļ�
			*	@see		Log
			*	@return   	void
			*	@note
			*
			**/
			void	Write2File();
	
		private:
			AChar				m_pBuff[LOG_BUFF_SIZE];		///<	1K������
			UInt				m_uiBuffSize;				///<	��������ǰλ��
			//UInt				m_uiLockCount;				///<	�ٽ���������
			AString				m_strProductName;
			CriticalSection		m_CS;
		};
	
	#ifndef	LOG
	#define LOG(strPlugin,strType)\
		AChar StringBuff[1024];\
		sprintf_s(StringBuff,1024,"["#strPlugin"]["#strType"] Function[%s]",__FUNCTION__);\
		Common::Log::GetSingleton()->Write(StringBuff);
	
		inline	void LogTitle(AChar*	strPlugin,AChar*	str){
			AChar buff[1024];
			sprintf_s(buff,1024,"[%s][Title] --<[%s]>--",strPlugin,str);
			Common::Log::GetSingleton()->Write(buff);
		}
		inline	void Logger(AChar*	strPlugin,AChar*	strType,AChar*	str){
			AChar buff[1024];
			sprintf_s(buff,1024,"[%s][%s] --<[%s]>--",strPlugin,strType,str);
			Common::Log::GetSingleton()->Write(buff);
		}
	#define LOG_ERROR(strPlugin)	LOG(strPlugin,Error)
	#define LOG_WARNING(strPlugin)	LOG(strPlugin,Warning)
	#define LOG_INFO(strPlugin)		LOG(strPlugin,Log)
	
	#endif
	
	
	
	};
};
#endif // COMMONLOG_HEAD_FILE