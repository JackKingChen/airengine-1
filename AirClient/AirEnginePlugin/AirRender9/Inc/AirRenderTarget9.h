#ifndef RENDERTARGET_HEAD_FILE
#define RENDERTARGET_HEAD_FILE


#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"

namespace Air{
	
	namespace Client{
	
		class	IMovableObject;
	
		namespace	Render{
	
			class	Target9	:
				public	ITarget{
			public:
				Target9(CAString& strName,Info* pInfo);
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Target
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Destroy( );

				U1			CreateDepthStencil();
				U1			DestroyDepthStencil();
	
	
				/**	\brief	��ʼ��Ⱦ
				*   
				*	@remarks 	��ʼ��Ⱦ
				*	@see		ITarget
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1			BeforeUpdate();
				virtual	U1			AfterUpdate();
	
				/**	\brief	������ȾĿ������
				*   
				*	@remarks 	������ȾĿ������
				*	@see		Target
				*	@return   	void
				*	@param		MovableObject * pObject
				*	@note
				*
				**/
				virtual	void		SetRenderObject(MovableObject*	pObject);
				/**	\brief	��ȡ��ȾĿ������
				*   
				*	@remarks 	��ȡ��ȾĿ������
				*	@see		ITarget
				*	@return   	IMovableObject*
				*	@note
				*
				**/
				virtual	MovableObject*	GetRenderObject();
	
				/**	\brief	�ؽ�
				*   
				*	@remarks 	�ؽ�
				*	@see		Target
				*	@return   	void
				*	@param		Info & info
				*	@note
				*
				**/
				virtual	void		ReCreate(Info&	info);
	
				virtual	void*		GetDepthStencil();

				virtual	void		OnLostDevice();
				virtual	void		OnResetDevice();
			protected:
				DxSurface*						m_pSurface;			///<	���ģ��
				MovableObject*					m_pTargetObject;	///<	��ȾĿ������
			};
	
			class	Target9Factory	:
				public	Factory
			{
			public:
				Target9Factory();
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
		};
	};
};
#endif // RENDERTARGET_HEAD_FILE