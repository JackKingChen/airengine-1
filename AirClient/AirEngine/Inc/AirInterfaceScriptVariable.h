/*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.


 \author    InfernalHell	Xinhe
 \date      2009/11/01
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceScriptVariable.h
 \note     
       
 \attention:
			�ű�����
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef INTERFACESCRIPTVARIABLE_HEAD_FILE
#define INTERFACESCRIPTVARIABLE_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Client{
	
		
		namespace Script{
			/**	\brief	��������
			*
			*	��������
			*
			***/
			enum enumVariableType
			{
				enVoid			 = 0,
				enBool           = 1,
				enInt8           = 2,
				enInt16          = 3,
				enInt32          = 4,
				enInt64          = 5,
				enUint8          = 6,
				enUint16         = 7,
				enUint32         = 8,
				enUint64         = 9,
				enFloat          = 10,
				enDouble         = 11,
				enObjectHandle   = 0x40000000,
				enHANDLETOCONST  = 0x20000000,
				enMASK_OBJECT    = 0x1C000000,
				enAPPOBJECT      = 0x04000000,
				enSCRIPTOBJECT   = 0x08000000,
				enSCRIPTARRAY    = 0x10000000,
				enMASK_SEQNBR    = 0x03FFFFFF
			};
			/**	\brief	�ű�����
			*
			*	�ű�����
			*
			***/
			class IVariable : public Common::Union4{
			public:
				IVariable(AString strName,SInt iType,void* pValue):m_strName(strName),m_iType(iType){
					m_bIsNull	= false;
					if(iType==enObjectHandle){
						m_pVoid	= pValue;
					}else{
						if(pValue!=NULL)
							memcpy(&m_pVoid,pValue,sizeof(Common::Union4));
						else
							memset(&m_pVoid,0,sizeof(Common::Union4));
					}
				};
				//IVariable(String strName,int iType,Union4 pValue):m_strName(strName),m_iType(iType){
				//	m_bIsNull	= false;
				//	if(iType==enObjectHandle){
				//		m_pVoid	= pValue.m_pVoid;
				//	}else{
				//		memcpy(&m_pVoid,&pValue.m_pVoid,sizeof(Union4));
				//	}
				//};
				IVariable():m_iType(0){
					m_bIsNull	= true;
				};
				virtual ~IVariable(){};
		
				/**	\brief	��ȡ��������
				*   
				*	@remarks 	��ȡ��������
				*	@see		IVariable
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual AString	GetName(){return m_strName;};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	
				*	@see		IVariable
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual SInt	GetType(){return m_iType;};
	
				/**	\brief	��ȡ��������
				*   
				*	@remarks 	��ȡ��������
				*	@see		IVariable
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual AString	GetTypeName(){return "";};
	
				/**	\brief	�Ƿ�Ϊ��
				*   
				*	@remarks 	
				*	@see		IVariable
				*	@return   	bool
				*	@note
				*
				**/
				virtual U1 IsNull(){return m_bIsNull;};
	
				/**	\brief	��ȡָ��
				*   
				*	@remarks 	
				*	@see		IVariable
				*	@return   	T_Type*
				*	@note
				*
				**/
				template<typename T_Type>
				T_Type* GetHandle(){
					if(m_iType!=enObjectHandle)
						return NULL;
					return (T_Type*)m_pVoid;
				}
	
				/**	\brief	ת��Ϊ�ַ���
				*   
				*	@remarks 	ת��Ϊ�ַ���
				*	@see		IVariable
				*	@return   	AString
				*	@note
				*
				**/
				AString	ToString(){
					return *(AString*)m_pVoid;
				}
				/**	\brief	ת��Ϊ�ַ���
				*   
				*	@remarks 	������char*
				*	@see		IVariable
				*	@return   	AString
				*	@note
				*
				**/
				AString	ToChar(){
					return (AChar*)m_pVoid;
				}
	
			protected:
				AString		m_strName;
				SInt		m_iType;
				U1			m_bIsNull;
			};
		}
	};
};

#endif // INTERFACESCRIPTVARIABLE_HEAD_FILE