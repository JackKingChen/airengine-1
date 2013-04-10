#ifndef ENGINEPARTICLEENTITY_HEAD_FILE
#define ENGINEPARTICLEENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderSystem.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
	
		/**	\brief	��Ļ������Ⱦ����
		*
		*	��Ļ������Ⱦ����
		*
		***/
		class	ENGINE_EXPORT	ParticleEntity	:
			public	TProduct<ParticleEntity>,
			public	MovableObject
		{
		public:
			struct	Info{
				Info(AString	strName	=	""){strParticleName	=	strName;};
				AString	strParticleName;
				Float3	vPosition;
				Float3	vVelocity;
				Real	fLife;
			};
		public:
			ParticleEntity(CAString&	strName,Info*	pInfo);
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
	
	// 		/**	\brief	��Ⱦ
	// 		*   
	// 		*	@remarks 	��Ⱦ
	// 		*	@see		ScreenEntity
	// 		*	@return   	void
	// 		*	@note
	// 		*
	// 		**/
	// 		virtual	void	Render();
		protected:
			Info			m_Info;
	
		};
	
		class	ParticleEntityFactory	:
			public	IFactory{
		public:
			ParticleEntityFactory();
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