#ifndef ENGINESCREENENTITY_HEAD_FILE
#define ENGINESCREENENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderSystem.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
		class	Material;
		/**	\brief	��Ļ������Ⱦ����
		*
		*	��Ļ������Ⱦ����
		*
		***/
		class	ENGINE_EXPORT	ScreenEntity	:
			public	Common::IProduct,
			public	MovableObject
		{
		public:
			static AString ProductTypeName;
	 		struct	Info{
				Info(AString	strName	=	""){strMaterialName	=	strName;};
	 			AString	strMaterialName;
	 		};
		public:
			ScreenEntity(CAString&	strName,Info*	pInfo);
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		ScreenEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Create();
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		ScreenEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Destroy();
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		ScreenEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual void	Update();
		
			/**	\brief	��Ⱦ
			*   
			*	@remarks 	��Ⱦ
			*	@see		ScreenEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Render();
	
			/**	\brief	��Ⱦ����Ч��
			*   
			*	@remarks 	��Ⱦ����Ч��
			*	@see		ScreenEntity
			*	@return   	ITexture*
			*	@param		IMaterial * pMaterial
			*	@param		ITexture * pInputTexture
			*	@note
			*
			**/
			virtual void	RenderPostComposer(Material*	pMaterial/*,Render::ITexture*	pInputTexture*/);
		protected:
			Info			m_Info;
	
		};
	
		class	ScreenEntityFactory	:
			public	IFactory{
		public:
			ScreenEntityFactory();
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		BuffFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
		};
	
	};
};
#endif // ENGINESCREENENTITY_HEAD_FILE