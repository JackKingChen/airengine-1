/*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.


 \author    InfernalHell	Xinhe
 \date      2009/11/01
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceScriptFuncition.h
 \note     
       
 \attention:
			�ű�������
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef INTERFACESCRIPTFUNCITION_HEAD_FILE
#define INTERFACESCRIPTFUNCITION_HEAD_FILE

//#include "Define.h"
#include "AirInterfaceScriptVariable.h"
namespace Air{
	
	namespace Client{
	
		
		namespace Script{
			class IVariable;
			/**	\brief	�ű�������
			*
			*	�ű�������
			*
			***/
			class IFunction{
			public:
				IFunction(){};
				virtual ~IFunction(){};
		
				/**	\brief	��ȡ����
				*   
				*	@remarks 	
				*	@see		IFunction
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual AString		GetName(){return "";};
				/**	\brief	ȫ��
				*   
				*	@remarks 	
				*	@see		IFunction
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual AString		GetFullName(){return "";};
		
				/**	\brief	��ȡ����ֵ
				*   
				*	@remarks 	
				*	@see		IFunction
				*	@return   	IVariable*
				*	@note
				*
				**/
				virtual IVariable	GetReturn(){return IVariable();};
		
				/**	\brief	��ȡ��������
				*   
				*	@remarks 	
				*	@see		IFunction
				*	@return   	int
				*	@note
				*
				**/
				virtual SInt			GetParamCount(){return 0;};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	
				*	@see		IFunction
				*	@return   	IVariable*
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual	IVariable	GetParam(SInt iIndex){return IVariable();};
				/**	\brief	���ò���
				*   
				*	@remarks 	
				*	@see		IFunction
				*	@return   	void
				*	@param		String strParam
				*	@param		int iIndex
				*	@note
				*
				**/
	
				virtual void		SetParam(IVariable variable,SInt iIndex){};
	
				/**	\brief	����
				*   
				*	@remarks 	
				*	@see		IFunction
				*	@return   	void
				*	@note
				*
				**/
				virtual U1		Run(bool bRelease = true){return true;};
			};
		}
	};
};

#endif // INTERFACESCRIPTFUNCITION_HEAD_FILE