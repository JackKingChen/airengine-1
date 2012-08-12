#ifndef INTERFACEUISTATICTEXT_HEAD_FILE
#define INTERFACEUISTATICTEXT_HEAD_FILE

#include "AirInterfaceUIWindowControl.h"
namespace Air{
	
	namespace Client{
	
		namespace	UI{
			namespace	Window{
				/**	\brief	��̬�ı���
				*
				*	��̬�ı���
				*
				***/
				class	IStaticText{
				public:
					/**	\brief	�����ı�
					*   
					*	@remarks 	�����ı�
					*	@see		IStaticText
					*	@return   	void
					*	@param		AString strName
					*	@note
					*
					**/
					virtual	void	SetText(AString	strName)	=	NULL;
					/**	\brief	��ȡ�ı�
					*   
					*	@remarks 	��ȡ�ı�
					*	@see		IStaticText
					*	@return   	AString
					*	@note
					*
					**/
					virtual	AString	GetText()					=	NULL;
					/**	\brief	�����ı���С
					*   
					*	@remarks 	�����ı���С
					*	@see		IStaticText
					*	@return   	void
					*	@param		Real fSize
					*	@note
					*
					**/
					virtual	void	SetTextSize(Real	fSize)	=	NULL;
					/**	\brief	��ȡ���ִ�С
					*   
					*	@remarks 	��ȡ���ִ�С
					*	@see		IStaticText
					*	@return   	Real
					*	@note
					*
					**/
					virtual	Real	GetTextureSize()			=	NULL;
					/**	\brief	�����ı���ɫ
					*   
					*	@remarks 	�����ı���ɫ
					*	@see		IStaticText
					*	@return   	void
					*	@param		Float4 v
					*	@note
					*
					**/
					virtual	void	SetTextColor(Float4 v)		=	NULL;
					/**	\brief	��ȡ�ı���ɫ
					*   
					*	@remarks 	��ȡ�ı���ɫ
					*	@see		IStaticText
					*	@return   	Client::Float4
					*	@note
					*
					**/
					virtual	Float4	GetTextureColor()			=	NULL;
				};
			}
		}
	
	};
};
#endif // INTERFACEUISTATICTEXT_HEAD_FILE