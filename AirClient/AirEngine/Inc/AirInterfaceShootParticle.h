#ifndef INTERFACESHOOTPARTICLE_HEAD_FILE
#define INTERFACESHOOTPARTICLE_HEAD_FILE

#include "AirInterfaceParticle.h"
namespace Air{
	
	namespace Engine{
	
		class	ShootParticle	:
			public	IParticle{
		public:
			static AString	ProductTypeName;
			ShootParticle(CAString&	strName,Info*	pInfo);
	
			/**	\brief	���ò���
			*   
			*	@remarks 	���ò���
			*	@see		ShootParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	SetParticleParam();
	
			virtual	void	Updata();
	
			virtual void	SetPosition(Float3 vSrcPos,Float3 vDstPos);
	
		};
		class	ShootParticleFactory	:
			public	IFactory{
		public:
			ShootParticleFactory();
	
			/**	\brief	��������Ч��
			*   
			*	@remarks 	��������Ч��
			*	@see		IParticleFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
		};
	};
};
#endif // INTERFACESHOOTPARTICLE_HEAD_FILE