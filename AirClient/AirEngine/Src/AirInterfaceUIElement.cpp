#include "AirInterfaceUIElement.h"

namespace Air{
	
	namespace	Engine{
		namespace	UI{
			IElement::IElement( ){
				m_vPositionSize	=	Float4(0,0,0,0);		///<	λ�úʹ�С
				m_vUV			=	Float4(0,0,0,0);		///<	ͼƬλ�úʹ�С
				m_vColor		=	Float4(0,0,0,0);		///<	������ɫ
				m_vCustom		=	Float4(0,0,0,0);		///<	�Զ���
	
				m_uiMark		=	-1;
			}	
		}
	}
};




