#ifndef ENGINEPOSTCOMPOSER_HEAD_FILE
#define ENGINEPOSTCOMPOSER_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Engine{
		class	Material;
	
		/**	\brief	����Ч��
		*
		*	����Ч��
		*
		***/
		class	PostComposer	:
			public	IProduct{
		public:
			PostComposer(AString	strName,AString*	strMaterialName);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		PostComposer
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1		Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		PostComposer
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1		Destroy();
	
			/**	\brief	�����Ƿ����øú���Ч��
			*   
			*	@remarks 	�����Ƿ����øú���Ч��
			*	@see		PostComposer
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetEnable(U1	bEnable);
			/**	\brief	��ȡ�Ƿ��Ѿ�����
			*   
			*	@remarks 	��ȡ�Ƿ��Ѿ�����
			*	@see		PostComposer
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		GetEnable();
			/**	\brief	��Ⱦ�ú���Ч��
			*   
			*	@remarks 	��Ⱦ�ú���Ч��
			*	@see		PostComposer
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Render();
	
		protected:
			U1					m_bEnable;				///<	�Ƿ�������ȾĿ��
			RenderTarget*		m_pTerget;				///<	��ȾĿ��
			Material*			m_pMaterial;			///<	����
			AString				m_strMaterialName;		///<	������
		};
	
		class	PostComposerFactory	:
			public	IFactory{
		public:
			PostComposerFactory();
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		BuffFactory
			*	@return   	IProduct*
			*	@param		CAString& strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
		};
	
	};
};
#endif // ENGINEPOSTCOMPOSER_HEAD_FILE