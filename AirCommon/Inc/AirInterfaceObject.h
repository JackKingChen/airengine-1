//*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.



 \author    InfernalHell	Xinhe
 \date      2009/10/21
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  InterfaceObject.h
 \note     
       
 \attention:
			����������ӿ�
       
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACEOBJECT_HEAD_FILE
#define INTERFACEOBJECT_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

namespace	Air{
	
	namespace Common{
		/**	\brief	��������ӿ���
		*
		*	��������������
		*
		***/
		class IObject{
		public:
			IObject(){
				m_pUserData	=	NULL;
			};
			virtual	~IObject(){};
			/**	\brief	��ȡ����
			*			
			*	@remarks		��ȡ����	
			*	@see		IObject
			*	@return   	Client::String
			*	@note
			*
			**/
			inline	Air::AString GetName(){
				return m_strName;
			}
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		IObject
			*	@return   	void
			*	@param		String strName
			*	@note
			*
			**/
			inline	void	SetName(const Air::AString& strName){
				m_strName	= strName;
			};
			/**	\brief	�����û�����
			*   
			*	@remarks 	�����û�����
			*	@see		IObject
			*	@return   	void
			*	@param		void* pUserData
			*	@note
			*
			**/
			inline	void	SetUserData(void*	pUserData){
				m_pUserData	=	pUserData;
			};
			/**	\brief	��ȡ�û�����
			*   
			*	@remarks 	��ȡ�û�����
			*	@see		IObject
			*	@return   	void*
			*	@note
			*
			**/
			inline	void*	GetUserData(){
				return	m_pUserData;
			};
			/**	\brief	�����û��ַ���
			*   
			*	@remarks 	�����û��ַ���
			*	@see		IObject
			*	@return   	void
			*	@param		const Air::AString & strUserString
			*	@note
			*
			**/
			inline	void	SetUserString(const Air::AString&	strUserString){
				m_strUserString	=	strUserString;
			};
			/**	\brief	��ȡ�û��ַ���
			*   
			*	@remarks 	��ȡ�û��ַ���
			*	@see		IObject
			*	@return   	Air::AString
			*	@note
			*
			**/
			inline	Air::AString	GetUserString(){
				return	m_strUserString;
			};
		protected:
			Air::AString	m_strName;			///<	��������
			Air::AString	m_strUserString;	///<	�û��ַ���Ϣ
			void*			m_pUserData;		///<	�û�����
		};
	};
};
#endif