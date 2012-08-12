#ifndef INTERFACEUSERDATA_HEAD_FILE
#define INTERFACEUSERDATA_HEAD_FILE

#include "AirEngineHeader.h"

namespace Air{
	namespace Client{
	
		/**	\brief	�û�������
		*
		*	�û�������
		*
		***/
		class	IUserData{
		public:
			IUserData(){
				m_pUserData	=	NULL;
			};
	
			/**	\brief	��ȡ�û��ַ���
			*   
			*	@remarks 	��ȡ�û��ַ���
			*	@see		IUserData
			*	@return   	AString
			*	@note
			*
			**/
			inline	AString		GetUserString(){
				return	m_strUserString;
			};
			/**	\brief	�����û��ַ���
			*   
			*	@remarks 	�����û��ַ���
			*	@see		IUserData
			*	@return   	void
			*	@param		AString str
			*	@note
			*
			**/
			inline	void		SetUserString(AString	str){
				m_strUserString	=	str;
			};
			/**	\brief	��ȡ�û�����
			*   
			*	@remarks 	��ȡ�û�����
			*	@see		IUserData
			*	@return   	void*
			*	@note
			*
			**/
			inline	void*		GetUserData(){
				return	m_pUserData;
			};
			/**	\brief	�����û�����
			*   
			*	@remarks 	�����û�����
			*	@see		IUserData
			*	@return   	void
			*	@param		void * pData
			*	@note
			*
			**/
			inline	void		SetUserData(void*	pData){
				m_pUserData	=	pData;
			};
	
			AString	m_strUserString;		///<	�û�����
			void*	m_pUserData;			///<	�û�����
		};
	
	};
};
#endif // INTERFACEUSERDATA_HEAD_FILE