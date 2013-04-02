#ifndef INTERFACEUILOOKFEEL_HEAD_FILE
#define INTERFACEUILOOKFEEL_HEAD_FILE

#include "AirInterfaceUIElement.h"
namespace Air{
	
	namespace Engine{
	
		namespace	UI{
			//typedef		std::vector<Common::StringVector>		StateStringMap;
			typedef		std::map<AString,StateArray>		WindowStateMap;
			typedef		WindowStateMap::value_type			WindowStateMapPair;
			/**	\brief	�Ӿ�������
			*
			*	�����Ӿ�������
			*
			***/
			class	ENGINE_EXPORT	Lookfeel	:
				public	IProduct{
			public:
				Lookfeel(CAString&	strName);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Lookfeel
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Lookfeel
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	��ȡ�Ӿ�����
				*   
				*	@remarks 	��ȡ�Ӿ�����
				*	@see		Lookfeel
				*	@return   	StateArray*
				*	@param		AString & strName
				*	@note
				*
				**/
				StateArray*	GetWindowLookfeel(AString&	strName);
			//protected:
				/**	\brief	�����Ӿ�����
				*   
				*	@remarks 	�����Ӿ�����
				*	@see		Lookfeel
				*	@return   	U1
				*	@param		AString & strLookfeelFile
				*	@param		StateArray * pArray
				*	@note
				*
				**/
				static	U1				ParseLookfeel(AString&	strLookfeelFile,StateArray*	pArray);
				/**	\brief	����״̬
				*   
				*	@remarks 	����״̬
				*	@see		Lookfeel
				*	@return   	U1
				*	@param		SortMap * pMap
				*	@param		ElementArray * pArray
				*	@note
				*
				**/
				static	U1				ParseState(SortMap*	pMap,ElementArray*		pArray);
	
				WindowStateMap	m_mapLookfeel;
				AString		m_strLookfeel;
			};
		}
	
	};
};
#endif // INTERFACEUILOOKFEEL_HEAD_FILE