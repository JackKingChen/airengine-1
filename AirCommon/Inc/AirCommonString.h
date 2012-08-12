/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/04/23
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonString.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONSTRING_HEAD_FILE
#define COMMONSTRING_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

namespace	Air{
	namespace Common{
		
		/**	\brief	�ж��ַ����Ƿ���ĳ�ַ���ͷ
		*   
		*	@remarks 	�ж��ַ����Ƿ���ĳ�ַ���ͷ
		*	@see		
		*	@return   	COMMON_EXPORT	U1
		*	@param		CAString & strWhole
		*	@param		CAString & strPart
		*	@note
		*
		**/
		COMMON_EXPORT	U1	StartWith(CAString&	strWhole,CAString&	strPart);
		/**	\brief	�ж��ַ����Ƿ����ַ�����β
		*   
		*	@remarks 	�ж��ַ����Ƿ����ַ�����β
		*	@see		
		*	@return   	COMMON_EXPORT	U1
		*	@param		CAString & strWhole
		*	@param		CAString & strPart
		*	@note
		*
		**/
		COMMON_EXPORT	U1	EndWith(CAString&	strWhole,CAString&	strPart);

		/**	\brief	��ȡ��׺��
		*   
		*	@remarks 	��ȡ��׺��
		*	@see		
		*	@return   	COMMON_EXPORT	AString
		*	@param		CAString & strName
		*	@note
		*
		**/
		COMMON_EXPORT	AString	GetPostfix(CAString&	strName);
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONSTRING_HEAD_FILE