#ifndef INTERFACEUIWINDOWSTATE_HEAD_FILE
#define INTERFACEUIWINDOWSTATE_HEAD_FILE


#include "AirInterfaceUIElement.h"
#include "AirInterfaceUIEvent.h"
#include "AirEngineMovableObject.h"

namespace Air{
	
	namespace Engine{
	
		namespace	UI{
	
			namespace	Window{
				/**	\brief	������Ϣ
				*
				*	������Ϣ
				*
				***/
				struct	Info{
					Info(){
						vPositionSize	=	Float4(1,1,0,0);
						vColor			=	Float4(1,1,1,1);
						vTextColor		=	Float4(1,1,1,1);
						vCenter			=	Float2(0,0);
						bVisiable		=	true;
						bEnable			=	true;
						memset(&key,0,sizeof(KeyUnion));
					};
					Float4		vPositionSize;
					Float4		vColor;
					Float2		vCenter;
					Float4		vTextColor;
					AString		strText;
					U1			bVisiable;
					U1			bEnable;
					KeyUnion	key;
				};
				//typedef	std::vector<Float4>	VectorArray;
				/**	\brief	����״̬
				*
				*	����״̬
				*
				***/
				class	ENGINE_EXPORT	State	:
					public	Event::Sender,
					public	MovableObject{
				public:
	
				public:
					State(StateArray*	pArray,Info*	pInfo);
					/**	\brief	�����Ƿ�ɼ�
					*   
					*	@remarks 	�����Ƿ�ɼ�
					*	@see		IControl
					*	@return   	void
					*	@param		U1 bVisiable
					*	@note
					*
					**/
					void			SetVisiable(U1	bVisiable);
					/**	\brief	�Ƿ�ɼ�
					*   
					*	@remarks 	�Ƿ�ɼ�
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					inline	U1		IsVisiable(){return	m_Info.bVisiable;};
					/**	\brief	�����Ƿ���Ч
					*   
					*	@remarks 	�����Ƿ���Ч
					*	@see		IControl
					*	@return   	void
					*	@param		U1 bEnable
					*	@note
					*
					**/
					void			SetEnable(U1	bEnable);
					/**	\brief	��ȡ�Ƿ���Ч
					*   
					*	@remarks 	��ȡ�Ƿ���Ч
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					inline	U1		IsEnable(){return	m_Info.bEnable;};
	
	
					/**	\brief	���ü���
					*   
					*	@remarks 	���ü���
					*	@see		IControl
					*	@return   	void
					*	@param		U1 bActive
					*	@note
					*
					**/
					virtual	void			SetActive(U1	bActive);
	
					/**	\brief	�����Ƿ�Ϊ�����
					*   
					*	@remarks 	�����Ƿ�Ϊ�����
					*	@see		State
					*	@return   	U1
					*	@note
					*
					**/
					U1				IsActive(){
						return	m_bActive;
					};
					/**	\brief	���ÿ�ݼ�
					*   
					*	@remarks	���ÿ�ݼ�
					*	@see		IControl
					*	@return   	void
					*	@param		ShortcutKey & key
					*	@note
					*
					**/
					inline	void	SetKey(KeyUnion&	key){
						memcpy(&m_Info.key,&key,sizeof(KeyUnion));
					};
	
					/**	\brief	�Ƿ���Ч
					*   
					*	@remarks 	�Ƿ���Ч
					*	@see		IControl
					*	@return   	U1
					*	@note
					*
					**/
					U1				IsKeyVaild(){
						return	(m_Info.key.Value!=0);
					}
					/**	\brief	����״̬
					*   
					*	@remarks 	����״̬
					*	@see		WindowState
					*	@return   	void
					*	@param		enumStateType type
					*	@note
					*
					**/
					virtual	void	SetState(enumStateType	type);
					/**	\brief	��ȡ״̬
					*   
					*	@remarks 	��ȡ״̬
					*	@see		WindowState
					*	@return   	enumStateType
					*	@note
					*
					**/
					inline	enumStateType	GetState(){
						return		m_Type;
					}
					/**	\brief	���ݵ�ǰ״̬ѡ����Ⱦ
					*   
					*	@remarks 	���ݵ�ǰ״̬ѡ����Ⱦ
					*	@see		WindowState
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RenderElement();
	
					/**	\brief	��ȾԪ��
					*   
					*	@remarks 	
					*	@see		State
					*	@return   	void
					*	@param		ElementArray&	eArray
					*	@note
					*
					**/
					virtual	void	BeforeRenderElement(ElementArray&	eArray)	=	NULL;
				protected:
					StateArray							m_StateArray;		///<	ͼƬ���б�
					enumStateType						m_Type;				///<	��ǰ״̬
					enumStateType						m_LastType;			///<	��һ״̬
					U1									m_bActive;			///<	���ü���
					Info								m_Info;
					Message								m_Message;
					U1									m_bChanged;	
				};
			}
		}
	
	};
};
#endif // INTERFACEUISTATE_HEAD_FILE