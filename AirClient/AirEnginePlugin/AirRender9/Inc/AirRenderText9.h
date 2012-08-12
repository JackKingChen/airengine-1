#ifndef RENDERTEXT_HEAD_FILE
#define RENDERTEXT_HEAD_FILE


#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"
namespace Air{
	
	
	namespace Client{
	
		namespace	Render{
			class	Text	:
				public	Product,
				public	IText{
			public:
	
			public:
				Text(CAString&	strName,Info* pInfo);
				virtual ~Text();
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Text
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Create( );
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Text
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Destroy( );
	
				/**	\brief	�豸��ʧ�ص�����
				*   
				*	@remarks 	�豸��ʧ�ص�����
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnLostDevice();
				/**	\brief	�����豸�ص�����
				*   
				*	@remarks 	�����豸�ص�����
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnResetDevice();
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		Text
				*	@return   	void
				*	@param		AString str
				*	@note
				*
				**/
				virtual	void	SetText(AString	str);
				/**	\brief	������ɫ
				*   
				*	@remarks 	������ɫ
				*	@see		Text
				*	@return   	void
				*	@param		Vector4 vColor
				*	@note
				*
				**/
				virtual	void	SetColor(Float4	vColor);
				/**	\brief	��Ⱦ
				*   
				*	@remarks 	��Ⱦ
				*	@see		Text
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Render();
			protected:
				Info		m_Info;
				AString		m_strInfo;
				RECT		m_Rect;
				DWORD		m_Color;
			private:
			};
	
			class	TextFactory	:
				public	Factory{
			public:
				TextFactory();
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		BuffFactory
				*	@return   	IProduct*
				*	@param		AString& strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
			};
		}
	
	};
};
#endif // RENDERTEXT_HEAD_FILE