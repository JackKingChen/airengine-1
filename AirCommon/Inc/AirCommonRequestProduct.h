/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/04/09
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonRequestProduct.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONREQUESTPRODUCT_HEAD_FILE
#define COMMONREQUESTPRODUCT_HEAD_FILE

#include "AirCommonProduct.h"
#include "AirCommonRequest.h"

namespace	Air{
	namespace Common{
	
		class	COMMON_EXPORT	RequestProduct	:
			public	IProduct,
			public	RequestManager
		{
		public:
			RequestProduct(const AString&	strName);
			/**	\brief	���һ������
			*   
			*	@remarks 	���һ������
			*	@see		RequestManager
			*	@return   	void
			*	@param		IRequest * pRequest
			*	@note
			*
			**/
			virtual	void		AddRequest(IRequest*	pRequest);
			/**	\brief	��ȡһ������
			*   
			*	@remarks 	��ȡһ������
			*	@see		RequestManager
			*	@return   	IRequest*
			*	@note
			*
			**/
			virtual	IRequest*	GetRequest();
			/**	\brief	�ж��Ƿ�������
			*   
			*	@remarks 	�ж��Ƿ�������
			*	@see		RequestManager
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1			HasReuqest();
			/**	\brief	ִ�лص�
			*   
			*	@remarks 	ִ�лص�
			*	@see		RequestManager
			*	@return   	void
			*	@param		const IRequest & request
			*	@note
			*
			**/
			virtual	void		ExcuteFunction(const IRequest&	request);
		protected:
			CriticalSection		m_CS;
		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONREQUESTPRODUCT_HEAD_FILE