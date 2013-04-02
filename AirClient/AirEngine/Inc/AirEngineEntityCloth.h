#ifndef ENGINEENTITYCLOTH_HEAD_FILE
#define ENGINEENTITYCLOTH_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfacePhysicsCloth.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
		namespace	Physics{
			class	IScene;
		}	
		/**	\brief	����ʵ����
		*
		*	����ʵ����
		*
		***/
		class	EntityCloth	:
			public	MovableObject,
			public	Common::IProduct{
		public:
			/**	\brief	������Ϣ
			*
			*	������Ϣ
			*
			***/
			struct	Info{
				Info(){
					pXScene	=	NULL;
				};
				AString				strMeshName;
				AString				strMaterialName;
				Physics::IScene*		pXScene;			///<	����ָ��
				Physics::ICloth::Info	clothInfo;		
			};
		public:
			EntityCloth(CAString&	strName,Info*	pInfo);
	
			virtual	U1	Create();
	
			virtual	U1	Destroy();
	
			virtual	const BoundingBox&	GetWorldBoundingBox()const;
	
			virtual	void	Updata();
	
			virtual	void	Render();
		protected:
			U1		CreatePhysxMesh();
			U1		CreateRenderMesh();
		protected:
			Physics::ICloth*		m_pCloth;
			Info				m_Info;
		};
	
		class	EntityClothFactory	:
			public	IFactory{
		public:
			EntityClothFactory(){
				m_strTypeName	=	"EntityCloth";
			};
	
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */){
				if(lstParam==NULL)
					return	NULL;
				return	new	EntityCloth(strName,(EntityCloth::Info*)lstParam);
			};
		};
	
	};
};
#endif // ENGINEENTITYCLOTH_HEAD_FILE