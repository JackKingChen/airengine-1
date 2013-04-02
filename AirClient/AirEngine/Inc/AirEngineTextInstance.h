#ifndef ENGINETEXTINSTANCE_HEAD_FILE
#define ENGINETEXTINSTANCE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineInstanceEntity.h"
namespace Air{
	
	namespace Engine{
		class	Font;
	
		/**	\brief	����ʵ����
		*
		*	������Ⱦ��ǧ������
		*
		***/
		class	ENGINE_EXPORT	TextInstance	:
			public	InstanceEntity{
		public:
			/**	\brief	������Ϣ
			*
			*	������Ϣ
			*
			***/
			struct	Info{
				Info(){
					uiMaxInstance	=	1024;
					uiSize			=	25;
				}
				AString	strMaterialName;	///<	����
				UInt	uiMaxInstance;		///<	���ʵ�����
				UInt	uiSize;				///<	���ִ�С
			};
		public:
			TextInstance(CAString&	strName,Info*	pInfo);
	
			/**	\brief	����ģ�Ͷ��㻺��
			*   
			*	@remarks 	����ģ�Ͷ��㻺��
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateModelVertexBuff();
			/**	\brief	����ʵ�嶥�㻺��
			*   
			*	@remarks 	����ʵ�嶥�㻺��
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateInstanceVertexBuff();
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateDeclare();
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		InstanceEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	CreateIndex();
	
			/**	\brief	�����ַ���
			*   
			*	@remarks 	�����ַ���
			*	@see		TextInstance
			*	@return   	void
			*	@param		AString strText
			*	@note
			*
			**/
			virtual	void	SetText(AString	strText);
	
			/**	\brief	��ȡ����
			*   
			*	@remarks 	��ȡ����
			*	@see		TextInstance
			*	@return   	AString
			*	@note
			*
			**/
			virtual	AString	GetText();
			/**	\brief	�������ִ�С
			*   
			*	@remarks 	�������ִ�С
			*	@see		TextInstance
			*	@return   	void
			*	@param		UInt uiSize
			*	@note
			*
			**/
			virtual	void	SetTextSize(UInt	uiSize);
			/**	\brief	��ȡ���ִ�С
			*   
			*	@remarks 	��ȡ���ִ�С
			*	@see		TextInstance
			*	@return   	UInt
			*	@note
			*
			**/
			inline	UInt	GetTextSize(){
				return	m_uiTextSize;
			};
	
			/**	\brief	�������־���
			*   
			*	@remarks 	�������־���
			*	@see		TextInstance
			*	@return   	void
			*	@param		RECT rect
			*	@note
			*
			**/
			virtual	void	SetTextRect(RECT rect);
			/**	\brief	��ȡ���־���
			*   
			*	@remarks 	��ȡ���־���
			*	@see		TextInstance
			*	@return   	RECT
			*	@note
			*
			**/
			RECT			GetTextRect();
		protected:
			WString		m_strText;			///<	�����ַ���
			Font*		m_pFont;			///<	������
			UInt		m_uiTextSize;		///<	���ִ�С
			UInt		m_Rect[4];			///<	���־���
		};
	
	
		class	TextInstanceFactory	:
			public		IFactory{
		public:
			TextInstanceFactory();
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		TextInstanceFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString&	strName,IFactoryParamList* lstParam	=	NULL);
		};
	
	};
};
#endif // ENGINETEXTINSTANCEENTITY_HEAD_FILE