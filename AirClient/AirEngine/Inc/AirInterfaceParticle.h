#ifndef INTERFACEPARTICLE_HEAD_FILE
#define INTERFACEPARTICLE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
		//namespace	Particle{
	
		/**	\brief	��������
		*
		*	��������
		*
		***/
		class	IParticle	:	
			public	MovableObject,
			public	Common::IProduct{
		public:
			struct	Info{
				Info(){
					vVelocity	=	Float3(0,0,0);
					vPosition	=	Float3(0,0,0);
				}
				AString	strParticleFile;
				Float3	vVelocity;
				Float3	vPosition;
			};
		public:
			IParticle(CAString&	strName,Info*	pInfo);
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		IParticle
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
	
			/**	\brief	�ݻ�����
			*   
			*	@remarks 	�ݻ�����
			*	@see		IParticle
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		IParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Updata();
	
			/**	\brief	��Ⱦ
			*   
			*	@remarks 	��Ⱦ
			*	@see		IParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Render();
			/**	\brief	��Ⱦalpha
			*   
			*	@remarks 	��Ⱦalpha
			*	@see		IParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual void	RenderAlpha();
	
			/**	\brief	�������Ӳ���
			*   
			*	@remarks 	�������Ӳ���
			*	@see		IParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	SetParticleParam();
	
			inline	U1		IsDeath(){
				return	m_bDeath;
			}
		protected:
			Info		m_Info;
			Real		m_fLife;
			Real		m_fCreateTime;
			U1			m_bDeath;
			Real&		m_fTotalTime;
			//Float3		m_vVelocity;
		};
	
		class	IParticleFactory	:
			public	IFactory{
		public:
			IParticleFactory();
	
			/**	\brief	��������Ч��
			*   
			*	@remarks 	��������Ч��
			*	@see		IParticleFactory
			*	@return   	IProduct*
			*	@param		AString& strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
		};
		//}
	
	};
};
#endif // INTERFACEPARTICLE_HEAD_FILE