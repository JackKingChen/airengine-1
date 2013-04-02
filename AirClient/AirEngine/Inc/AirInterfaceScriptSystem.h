//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/05/31
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceScriptSystem.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACESCRIPT_HEAD_FILE
#define INTERFACESCRIPT_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceScriptRegisterManager.h"

namespace Air{
	
	namespace Engine{
		namespace Script{
			class IFunction;
	
			/**	\brief	�ű�����ӿ���
			*
			*	�ṩ�ű��ĵ��ýӿ�
			*
			***/
			class ISystem	:
				public	Common::ISystem,
				public	IRegisterManager{
			public:
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ���� ���������Ѽ��ؽű��ļ��б�
				*	@see		IScript
				*	@return   	IFunction*
				*	@param		std::string strName
				*	@note
				*
				**/
				//Script::IFunction*	GetFunction(std::string strName) {return NULL;};
				virtual IFunction* GetFunction(std::string strName) = NULL;
			};
		};
	};
};
#endif