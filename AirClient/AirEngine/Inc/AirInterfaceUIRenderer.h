#ifndef INTERFACEUIRENDERER_HEAD_FILE
#define INTERFACEUIRENDERER_HEAD_FILE

#include "AirRenderTarget.h"
#include "AirInterfaceUIElement.h"
#include "AirEngineRenderable.h"
namespace Air{
	
	namespace Engine{
		class	ScreenEntity;

	
		namespace	UI{
			namespace	Window{
				class	IControl;
			}
	#define	MAX_WINDOW	60
			/**	\brief	UI��Ⱦ
			*
			*	UI��Ⱦ
			*
			***/
			class	ENGINE_EXPORT	Renderer	:
				public	Renderable,
				public	Render::TargetManager{
			public:
				Renderer();
	
				/**	\brief	��ʼ��
				*   
				*	@remarks 	��ʼ��
				*	@see		Renderer
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		InitEffect();
				/**	\brief	�ͷ�
				*   
				*	@remarks 	�ͷ�
				*	@see		Renderer
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	ReleaseEffect();
	
				/**	\brief	������Ҫ��Ⱦ��UI
				*   
				*	@remarks 	������Ҫ��Ⱦ��UI
				*	@see		Renderer
				*	@return   	void
				*	@param		IElement*	pElement
				*	@note
				*
				**/
				virtual	void	Push(IElement*	pElement);
	
	
				/**	\brief	��ʼ��Ⱦ
				*   
				*	@remarks 	��ʼ��Ⱦ
				*	@see		Renderer
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	StartRender();
	
				/**	\brief	��Ⱦһ��UI
				*   
				*	@remarks 	
				*	@see		Renderer
				*	@return   	void
				*	@param		Window::IControl*	pControl
				*	@note
				*
				**/
				virtual	void	RenderControl(Window::IControl*	pControl);
	
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		Renderer
				*	@return   	void
				*	@param		AString strMaterialName
				*	@note
				*
				**/
				void			SetMaterialName(AString	strMaterialName);
	
				/**	\brief	��ȡ�����С
				*   
				*	@remarks 	��ȡ�����С
				*	@see		Renderer
				*	@return   	Client::Float4
				*	@note
				*
				**/
				inline	Float4*	GetTextureSize(){
					return	&m_vTextureSize;
				};
				/**	\brief	��ȡͼƬ������
				*   
				*	@remarks 	��ȡͼƬ������
				*	@see		Renderer
				*	@return   	IImageSet*
				*	@note
				*
				**/
				inline	IImageSet*		GetImageSet(){
					return	m_pImageSet;
				};
	
				/**	\brief	��ȡͼƬ
				*   
				*	@remarks 	��ȡͼƬ
				*	@see		Renderer
				*	@return   	Client::Float4
				*	@param		AString strName
				*	@note
				*
				**/
				Float4	GetImage(AString	strName){
					if(m_pImageSet!=NULL){
						return	m_pImageSet->GetImage(strName);
					}
					return Float4(0,0,0,0);
				}
				/**	\brief	��Ⱦ����Ŀ�굽����
				*   
				*	@remarks 	��Ⱦ����Ŀ�굽����
				*	@see		Renderer
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	RenderTarget();
			protected:
				VectorArray				m_vPositionSizeArray;
				VectorArray				m_vUVPositionSizeArray;
				VectorArray				m_vColorArray;
				VectorArray				m_vCustomArray;
				UInt					m_uiSize;
				Float4					m_vTextureSize;
				IImageSet*				m_pImageSet;
	
				ScreenEntity*			m_pScreenEnt;
			};
		}
	
	};
};
#endif // INTERFACEUIRENDER_HEAD_FILE