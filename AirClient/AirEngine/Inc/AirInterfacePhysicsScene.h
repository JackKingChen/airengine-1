#ifndef INTERFACEPHYSICSSCENE_HEAD_FILE
#define INTERFACEPHYSICSSCENE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfacePhysicsCollision.h"
#include "AirInterfacePhysicsController.h"
#include "AirInterfacePhysicsCloth.h"
namespace Air{
	
	namespace Client{
	
		namespace	Physics{
			//class	ICollision;
			/**	\brief	������
			*
			*	������
			*
			***/
			class	IScene	:
				public	IFactoryManager{
			public:
				/**	\brief	��ʼ��
				*   
				*	@remarks 	��ʼ��
				*	@see		IScene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization()	=	NULL;
				/**	\brief	�ͷ�
				*   
				*	@remarks 	�ͷ�
				*	@see		IScene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release()			=	NULL;
				/**	\brief	ģ��
				*   
				*	@remarks 	ģ�� bSynchronousΪfalseʱ Ϊ�첽ģ��  ����ʹ���첽ģʽ
				*	@see		IScene
				*	@return   	U1
				*	@param		U1 bSynchronous
				*	@note
				*
				**/
				virtual	U1	Simulate(U1	bSynchronous	=	true)	=	NULL;
	
				/**	\brief	���߼��
				*   
				*	@remarks 	���߼��
				*	@see		IScene
				*	@return   	U1
				*	@param		Ray ray
				*	@param		Float3 * pHitPosition
				*	@param		Float3 * pNormal
				*	@param		Real * fDistance
				*	@note
				*
				**/
				virtual	U1	RayCast(Ray	ray,Float3*	pHitPosition	=	NULL,Float3*	pNormal	=	NULL,Real*	fDistance	=	NULL,void**	ppUserData	=	NULL)	=	NULL;
	
				/**	\brief	�Ƿ��Ѿ�ģ�����
				*   
				*	@remarks 	�Ƿ��Ѿ�ģ�����	û��ģ�����ʱ ��������ģ�� �ݻ�ģ�Ͷ���ʧ��
				*	@see		IScene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		WaitSimulateFinished()	=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXSCENE_HEAD_FILE