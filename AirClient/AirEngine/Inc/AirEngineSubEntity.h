#ifndef ENGINESUBENTITY_HEAD_FILE
#define ENGINESUBENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirInterfacePhysicsShape.h"
#include "AirInterfaceUserData.h"

namespace Air{
	
	namespace Engine{
		namespace	Physx{
			class	Shape;
		}
	
		class	ENGINE_EXPORT	SubEntity	:
			public	Common::IProduct,
			public	MovableObject
		{
		public:
			struct	Info{
				AString	strMeshName;
				AString	strMaterialName;
			};
		public:
			SubEntity(CAString&	strName,Info* pInfo);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		IPage
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Create();
	
			/**	\brief	�ݻ�
			*   
			*	@remarks 	�ݻ�
			*	@see		IPage
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Destroy();
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		IPage
			*	@return   	void
			*	@note
			*
			**/
			virtual void	Updata();
	
			virtual	void	GetShape(Physics::Shape*	pShape,Float3 vScale	=	Float3(1,1,1));
		protected:
			Info			m_Info;
		};
	
		class	SubEntityFactory	:
			public	IFactory{
		public:
			SubEntityFactory();
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
#endif // ENGINESUBENTITY_HEAD_FILE