#ifndef INTERFACEPHYSICSCLOTH_HEAD_FILE
#define INTERFACEPHYSICSCLOTH_HEAD_FILE

#include "AirInterfacePhysicsCollision.h"

namespace Air{
	
	namespace Client{
	
		namespace	Physics{
			/**	\brief	����ģ�����
			*
			*	����ģ�����
			*
			***/
			class	ICloth{
			public:
				/**	\brief	�����ϴ�����Ϣ
				*
				*	������Ϣ
				*
				***/
				struct	Info{
					Info(){
						thickness = 0.01f;
						selfCollisionThickness = 0.2f;
						density = 1.0f;
						bendingStiffness = 1.0f;
						stretchingStiffness = 1.0f;
						hardStretchLimitationFactor = 1.0f;
						dampingCoefficient = 0.5f;
						friction = 0.5f;
						pressure = 1.0f;
						tearFactor = 1.5f;
						attachmentTearFactor = 1.5f;
						attachmentResponseCoefficient = 0.2f;
						collisionResponseCoefficient = 0.2f;
						userData	=	NULL;
					};
					Shape	shape;							///<	����ģ��
					Real	thickness;						///<	���
					Real	selfCollisionThickness;			///<	������ײ���
					Real	density;						///<	�ܶ�
					Real	bendingStiffness;				///<	������
					Real	stretchingStiffness;			///<	����
					Real	hardStretchLimitationFactor;
					Real	dampingCoefficient;				///<	����
					Real	friction;						///<	Ħ����
					Real	pressure;						///<	ѹ��
					Real	tearFactor;
					Real	collisionResponseCoefficient;
					Real	attachmentResponseCoefficient;
					Real	attachmentTearFactor;
					void*	userData;
	
				};
	
				virtual	Float3		GetVertexPosition(UInt	uiVertexIdx)	=	NULL;
				virtual	void		SetVertexPosition(UInt	uiVertexIdx,Float3&	vPos)	=	NULL;
				virtual	Float3		GetVertexVelocity(UInt	uiVertexIdx)	=	NULL;
				virtual	void		SetVertexVelocity(UInt	uiVertexIdx,Float3&	vSpeed)	=	NULL;
				virtual	void		AttachToObject(ICollision*	pObject)	=	NULL;
				virtual	void		DetachFromObject(ICollision*	pObject)	=	NULL;
				virtual	void		AddForceAtVertex(UInt	uiVertexIdx,Float3&	vVelocity)	=	NULL;
				virtual	void		AddForceAtPos(Float3&	vPos,Float3&	vVelocity)	=	NULL;
				virtual	const BoundingBox&	GetWorldBoundingBox()	=	NULL;
	
	
				/**	\brief	��ȡ���㻺����
				*   
				*	@remarks 	����ֵΪ������
				*	@see		ICloth
				*	@return   	UInt
				*	@param		SBuff * pBuff
				*	@note
				*
				**/
				virtual	UInt	GetVertexBuff(SBuff*	pBuff)	=	NULL;
				/**	\brief	��ȡ����������
				*   
				*	@remarks 	����ֵΪ��������
				*	@see		ICloth
				*	@return   	UInt
				*	@param		UInt * pBuff
				*	@note
				*
				**/
				virtual	UInt	GetIndexBuff(UInt*				pBuff)	=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXCLOTH_HEAD_FILE