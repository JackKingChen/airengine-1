//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Random.h
 \note     
       
 \attention:
			�����
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef RANDOM_HEAD_FILE
#define RANDOM_HEAD_FILE
#include "AirCommon.h"
#include "AirCommonHeader.h"
namespace Air{
	
	namespace Common{
		/**	\brief	������
		*
		*	��ȡ�������������
		*
		***/
		class COMMON_EXPORT Number{
		public:
			/**	\brief	�������
			*   
			*	@remarks 	��ΧĬ����0-100
			*	@see		Number
			*	@return   	int
			*	@param		int iMin
			*	@param		int iMax
			*	@note
			*
			**/
			static SInt				RandomI(SInt	 iMin   ,SInt   iMax);
			/**	\brief	�������
			*   
			*	@remarks 	��ΧĬ����0.0f-1.0f
			*	@see		Number
			*	@return   	float
			*	@param		float fMin
			*	@param		float fMax
			*	@note
			*
			**/
			static Real				RandomF();
			/**	\brief	��ֵ����
			*   
			*	@remarks 	��0��ʼ ÿ�ε�������1	
			*	@see		Number
			*	@return   	unsigned int
			*	@note
			*
			**/
			static UInt		Increase();
			/**	\brief	�ַ�������
			*   
			*	@remarks 	�ڸ����ַ���֮�����������ֵ����֤�������������岻������
			*	@see		Number
			*	@return   	Client::String
			*	@param		char * strName
			*	@note
			*
			**/
			static AString		Increase(const AString& strName);
			/**	\brief	��ʼ������
			*   
			*	@remarks 	��ʼ������
			*	@see		Number
			*	@return   	void
			*	@note
			*
			**/
			static void InitSrand();
		};
	};
	COMMON_EXPORT	void	RandomF3(Float3& v);
	COMMON_EXPORT	void	RandomF2(Float2& v);
};
#endif