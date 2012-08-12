/*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.


 \author    InfernalHell	Xinhe
 \date      2009/11/01
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceScriptFile.h
 \note     
       
 \attention:
			�ű��ļ���
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef INTERFACESCRIPTFILE_HEAD_FILE
#define INTERFACESCRIPTFILE_HEAD_FILE

//#include "Define.h"
#include "AirInterfaceScriptVariable.h"
namespace Air{
	
	namespace Client{
	
		
		namespace Script{
			class	IFunction;
			class	IVariable;
			/**	\brief	�ű��ļ�
			*
			*	�ű��ļ�
			*
			***/
			class IFile{
			public:
		
				/**	\brief	��ȡ�ű��ļ���
				*   
				*	@remarks 	��ȡ�ű��ļ���
				*	@see		IFile
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual AString		GetFileName(){return "";};
	
				/**	\brief	��ȡ�ļ�ȫ�ֱ�����
				*   
				*	@remarks 	��ȡ�ļ�ȫ�ֱ�����
				*	@see		IFile
				*	@return   	int
				*	@note
				*
				**/
				virtual SInt			GetVariableCount(){return 0;};
				/**	\brief	��ȡȫ�ֱ�������
				*   
				*	@remarks 	��ȡȫ�ֱ�������
				*	@see		IFile
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual AString		GetVariableName(){return "";};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	����
				*	@see		IFile
				*	@return   	IVariable*
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual IVariable	GetVariable(SInt iIndex){return IVariable();};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		IFile
				*	@return   	IVariable*
				*	@param		String strName
				*	@note
				*
				**/
				virtual IVariable	GetVariable(AString strName){return IVariable();};
		
				/**	\brief	��ȡ��������
				*   
				*	@remarks 	��ȡ��������
				*	@see		IFile
				*	@return   	int
				*	@note
				*
				**/
				virtual SInt			GetFunctionCount(){return 0;};
				/**	\brief	��ȡ������
				*   
				*	@remarks 	��ȡ������
				*	@see		IFile
				*	@return   	Client::String
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual AString		GetFunctionName(SInt iIndex){return "";};
				/**	\brief	��ȡ����ȫ��
				*   
				*	@remarks 	��ȡ����ȫ��
				*	@see		IFile
				*	@return   	Client::String
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual AString		GetFunctionString(SInt iIndex){return  "";};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		IFile
				*	@return   	IFunction*
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual IFunction*	GetFunction(SInt iIndex){return NULL;};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	
				*	@see		IFile
				*	@return   	IFunction*
				*	@param		String strName
				*	@note
				*
				**/
				virtual IFunction*	GetFunction(AString strName){return NULL;};
				/**	\brief	��ȡ����ͨ������ȫ��
				*   
				*	@remarks 	��ȡ����ͨ������ȫ��
				*	@see		IFile
				*	@return   	IFunction*
				*	@param		String strFullName
				*	@note
				*
				**/
				virtual IFunction*	GetFunctionByFullName(AString strFullName){return NULL;};
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		IFile
				*	@return   	void
				*	@note
				*
				**/
				virtual U1		Compile(){return true;};
				/**	\brief	�Ƿ����
				*   
				*	@remarks 	�Ƿ����
				*	@see		IFile
				*	@return   	bool
				*	@note
				*
				**/
				virtual U1		HasCompile(){return true;};
	
	
				/**	\brief	��ȡ������
				*   
				*	@remarks 	��ȡ������
				*	@see		IFile
				*	@return   	bool
				*	@note
				*
				**/
				virtual U1		ReadBinary(){return true;};
				/**	\brief	д�������
				*   
				*	@remarks 	
				*	@see		IFile
				*	@return   	bool
				*	@note
				*
				**/
				virtual U1		WriteBinary(){return true;};
		
			};
		}
	};
};

#endif // INTERFACESCRIPTFILE_HEAD_FILE