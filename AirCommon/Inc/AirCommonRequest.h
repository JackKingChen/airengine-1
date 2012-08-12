/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/04/09
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonRequest.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONREQUEST_HEAD_FILE
#define COMMONREQUEST_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"


#define		UNKNOWN_REQUEST	0

namespace	Air{
	namespace Common{
	
		
		/**	\brief	��������
		*
		*	
		*
		***/
		class	IRequest{
		public:
			IRequest()
				:	type(UNKNOWN_REQUEST)
			{
			}
			virtual	~IRequest(){};

			U1	IsValid(){
				return	type	!=	UNKNOWN_REQUEST;
			}
			UInt	type;
		};

		typedef	std::list<IRequest*>		RequestList;	///<	�����б�

		typedef	IFunction<IRequest>			RFunction;

		typedef	std::map<UInt,RFunction*>	FunctionMap;

		/**	\brief	���������
		*
		*	���������
		*
		***/
		class	COMMON_EXPORT	RequestManager{
		public:
			RequestManager(){

			};
			virtual	~RequestManager();

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

			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		RequestManager
			*	@return   	void
			*	@note
			*
			**/
			virtual	void		ProcessRequest();

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

			/**	\brief	���һ���ص�����
			*   
			*	@remarks 	���һ���ص�����
			*	@see		RequestManager
			*	@return   	void
			*	@param		UInt iRequestID
			*	@param		RFunction * pFunction
			*	@note
			*
			**/
			void				AddFunction(UInt iRequestID,RFunction*	pFunction);

			RequestList			m_lstRequest;		///<	�����б�
			FunctionMap			m_mapFunction;		///<	�����б�
		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONREQUEST_HEAD_FILE