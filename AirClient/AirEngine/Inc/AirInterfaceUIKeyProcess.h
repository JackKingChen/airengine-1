#ifndef INTERFACEUIKEYPROCESS_HEAD_FILE
#define INTERFACEUIKEYPROCESS_HEAD_FILE

#include "AirInterfaceUICommon.h"
namespace Air{
	
	namespace Client{
	
		namespace	UI{
			namespace	Window{
				class	IControl;
			}
	
			typedef		std::map<U64,Window::IControl*>	KeyMap;
			typedef		KeyMap::iterator				KeyMapItr;
			typedef		KeyMap::value_type				KeyMapPair;
			/**	\brief	��ݼ�����
			*
			*	��ݼ�����
			*
			***/
			class	ENGINE_EXPORT	KeyProcess{
			public:
				KeyProcess();
	
				/**	\brief	���һ����ݼ�
				*   
				*	@remarks 	���һ����ݼ�
				*	@see		KeyProcess
				*	@return   	void
				*	@param		U64 Key
				*	@param		Window::IControl * pControl
				*	@note
				*
				**/
				void	AddKey(U64	Key,Window::IControl*	pControl);
				/**	\brief	�Ƴ�һ����ݼ�
				*   
				*	@remarks 	�Ƴ�һ����ݼ�
				*	@see		KeyProcess
				*	@return   	void
				*	@param		U64 Key
				*	@param		Window::IControl * pControl
				*	@note
				*
				**/
				void	RemoveKey(U64	Key,Window::IControl*	pControl);
	
				/**	\brief	��������Ϣ
				*   
				*	@remarks 	��������Ϣ
				*	@see		KeyProcess
				*	@return   	void
				*	@param		U64 Key
				*	@param		U1 bKeyDown
				*	@note
				*
				**/
				void	ProcessKey(U64	Key,U1	bKeyDown);
	
				KeyMap		m_mapKey;
			};
		}
	
	};
};
#endif // INTERFACEUIKEYPEOCESS_HEAD_FILE