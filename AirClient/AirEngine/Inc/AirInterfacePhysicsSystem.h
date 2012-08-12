#ifndef INTERFACEPHYSICSSYSTEM_HEAD_FILE
#define INTERFACEPHYSICSSYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfacePhysicsScene.h"
namespace Air{
	
	namespace Client{
	
		namespace	Physics{
			/**	\brief	����ϵͳ
			*
			*	����ϵͳ
			*
			***/
			class	ISystem	:	
				public	Common::ISystem{
			public:
				ISystem(CAString&	strType):Common::ISystem(strType){

				}
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		ISystem
				*	@return   	IScene*
				*	@param		AString strName
				*	@note
				*
				**/
				virtual	IScene*	CreateScene(AString	strName)	=	NULL;
				/**	\brief	�ݻٳ���
				*   
				*	@remarks 	�ݻٳ���
				*	@see		ISystem
				*	@return   	void
				*	@param		IScene * pScene
				*	@note
				*
				**/
				virtual	void	DestroyScene(IScene*	pScene)	=	NULL;
	
			protected:
			private:
			};
		}
	
	};
};
#endif // INTERFACEPHYSXSYSTEM_HEAD_FILE