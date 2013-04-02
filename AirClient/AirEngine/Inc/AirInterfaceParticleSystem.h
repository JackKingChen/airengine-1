#ifndef INTERFACEPARTICLESYSTEM_HEAD_FILE
#define INTERFACEPARTICLESYSTEM_HEAD_FILE

#include "AirInterfaceBaseParticle.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Particle{
			/**	\brief	����ϵͳ��
			*
			*	����ϵͳ��
			*
			***/
			class	ISystem	:
				public	IPlugin,
				public	IFactoryManager{
			public:
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		ISystem
				*	@return   	IBaseObject*
				*	@param		AString strName
				*	@param		Info * pInfo
				*	@note
				*
				**/
				virtual	IBaseObject*	CreateParticle(AString	strName,Info*	pInfo)	=	NULL;
				/**	\brief	�ݻ�����
				*   
				*	@remarks 	�ݻ�����
				*	@see		ISystem
				*	@return   	void
				*	@param		IBaseObject * pObject
				*	@note
				*
				**/
				virtual	void			DestroyParticle(IBaseObject*	pObject)		=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEPARTICLESYSTEM_HEAD_FILE