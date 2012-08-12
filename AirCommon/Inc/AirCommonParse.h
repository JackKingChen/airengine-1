#ifndef COMMONPARSE_HEAD_FILE
#define COMMONPARSE_HEAD_FILE

#include "AirCommonHeader.h"
#include "AirCommonFile.h"


namespace Air{
	namespace Common{
		//typedef	Common	StringVector;
		/**	\brief	�ʷ�����
		*
		*	�ʷ�����
		*
		***/
		class	COMMON_EXPORT	Parse{
		public:
			/**	\brief	�ļ�����
			*   
			*	@remarks 	
			*	@see		Parse
			*	@return   	U1
			*	@param		Data * pData
			*	@param		StringVector & vecWord
			*	@param		U1 bLowerCase
			*	@param		AString * pError
			*	@note
			*
			**/
			static	U1	StringToWord(U8*	pData,U32	uiSize,StringVector&	vecWord,U1	bLowerCase	=	false,AString*	pError	=	NULL);
			static	U1	StringToWordScript(U8*	pData,U32	uiSize,StringVector&	vecWord,U1	bLowerCase	=	false,AString*	pError	=	NULL);

		};
		
	
	};
};
#endif // COMMONPARSE_HEAD_FILE