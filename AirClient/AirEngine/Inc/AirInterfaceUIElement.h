#ifndef INTERFACEUIELEMENT_HEAD_FILE
#define INTERFACEUIELEMENT_HEAD_FILE

#include "AirInterfaceUIImage.h"
namespace Air{
	
	
	namespace Engine{
	
		namespace	UI{
			class	IImage;
			/**	\brief	��Ⱦ����
			*
			*	��Ⱦ����
			*
			***/
			class	Buffer{
			public:
				Float4	m_vPositionSize;		///<	λ�úʹ�С
				Float4	m_vUV;					///<	ͼƬλ�úʹ�С
				Float4	m_vColor;				///<	������ɫ
				Float4	m_vCustom;				///<	�Զ���
			};
			/**	\brief	����Ԫ����
			*
			*	����Ԫ����
			*
			***/
			class	ENGINE_EXPORT	IElement	:
				public	Buffer{
			public:
				enum	enumType{
					enTexture,		///<	ͼƬ
					enCharacter,	///<	����
					enVideo,		///<	��Ƶ
					enMax
				};
	
			public:
				IElement();
				UInt	m_uiMark;				///<	���	���ڸ�������
			};
	
			typedef		std::vector<IElement>	ElementArray;
			typedef		ElementArray::iterator	ElementArrayItr;
	
			typedef		std::vector<ElementArray>	StateArray;
			typedef		StateArray::iterator		StateArrayItr;
		}
	
	};
};
#endif // INTERFACEUIELEMENT_HEAD_FILE