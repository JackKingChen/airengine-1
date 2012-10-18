//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonReference.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONREFERENCE_HEAD_FILE
#define COMMONREFERENCE_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
namespace Air{
	
	namespace Common{
	
		class COMMON_EXPORT	IReference{
		public:
			IReference();
			virtual	~IReference();
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual U32		AddRef();
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U32		ReleaseRef();
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Create()	=	NULL;
			/**	\brief	�ͷ�
			*   
			*	@remarks 	
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Destroy()	=	NULL;
			/**	\brief	��ȡ���ö���ָ��
			*   
			*	@remarks 	��ȡ���ö���ָ��
			*	@see		IReference
			*	@return   	UInt*
			*	@note
			*
			**/
			inline	void*	GetObject(){return	m_pObject;};
			/**	\brief	��ȡ���ö���ָ��
			*   
			*	@remarks 	��ȡ���ö���ָ�루ģ�壩
			*	@see		IReference
			*	@return   	T_Object
			*	@note
			*
			**/
			template	<typename	T_Object>
			T_Object		GetObjectT(){return	(T_Object)(m_pObject);};
	
			/**	\brief	�Ƿ�Ϊ��
			*   
			*	@remarks 	�Ƿ�Ϊ��
			*	@see		IReference
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		IsNull(){return	(m_pObject	==	NULL);};
	
			/**	\brief	��ȡ���ü���
			*   
			*	@remarks 	��ȡ���ü���
			*	@see		IReference
			*	@return   	UInt
			*	@note
			*
			**/
			inline	U32	GetRefCount(){return m_uiNumRef;};
		protected:
			void*	m_pObject;		///<	���ö���ָ��
			U32		m_uiNumRef;		///<	���ü���
		private:
		};
	
	};
};
#endif // COMMONREFERENCE_HEAD_FILE