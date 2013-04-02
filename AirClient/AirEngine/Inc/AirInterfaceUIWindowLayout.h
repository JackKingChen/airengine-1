#ifndef INTERFACEUIWINDOWLAYOUT_HEAD_FILE
#define INTERFACEUIWINDOWLAYOUT_HEAD_FILE

#include "AirInterfaceUIWindowControl.h"
namespace Air{
	
	namespace Engine{
	
		namespace	UI{
			namespace	Window{
	
				class	Layout	:
					public	IControl{
				public:
	
				public:
					Layout(AString	strName,AString*	strLayout,Info*	pInfo);
	 
	
					/**	\brief	����
					*   
					*	@remarks 	����
					*	@see		Layout
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Create();
					/**	\brief	�ж��Ƿ�����ڴ�������
					*   
					*	@remarks 	�ж��Ƿ�����ڴ�������
					*	@see		IControl
					*	@return   	IControl*
					*	@note
					*
					**/
					virtual	IControl*		IsMouseInWindow();
	
				protected:
					U1	ParseKey(KeyUnion&	k,AString&	strInfo);
					U8	GetKey(AString&	str);
	
					AString		m_strLayout;
				};
			}
		}
	
	};
};
#endif // INTERFACEUIWINDOWLAYOUT_HEAD_FILE