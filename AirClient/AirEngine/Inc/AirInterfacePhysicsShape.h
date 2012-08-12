#ifndef INTERFACEPHYSICSSHAPE_HEAD_FILE
#define INTERFACEPHYSICSSHAPE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderBuffer.h"
#include "AirEngineMesh.h"
namespace Air{
	
	namespace Client{
	
		namespace	Physics{
			/**	\brief	����
			*
			*	����
			*
			***/
			class	Shape{
			public:
				/**	\brief	��״����
				*
				*	��״����
				*
				***/
				enum	enumType{
					//enUnKnown,
					enPlane,
					enBox,
					enSphere,
					enCapsule,
					enConvex,
					enTriangleMesh,
					enMax
				};
				Shape(){
					m_Type		=	enBox;
					m_pUserData	=	NULL;
					//m_VertexArray.push_back(Float3(1,1,1));
					m_vLocalPosition	=	Float3(0,0,0);
					m_vLocalQuat		=	Float4(0,0,0,1);
				};
	
				void	Clear(){
					m_VertexArray.clear();
					m_FaceArray.clear();
				};
	
				/**	\brief	ƽ��
				*   
				*	@remarks 	XYZΪ����	�߶�ΪW
				*	@see		Shape
				*	@return   	void
				*	@param		Float4 v
				*	@note
				*
				**/
				void	SetPlane(Float3	vNormal,Real	fHeight){
					m_VertexArray.push_back(vNormal);
					m_VertexArray.push_back(Float3(fHeight,0,0));
					m_Type	=	enPlane;
	
				};
	
				/**	\brief	���÷���
				*   
				*	@remarks 	���÷���
				*	@see		Shape
				*	@return   	void
				*	@param		Float3 vSize
				*	@note
				*
				**/
				void	SetBox(Float3	vSize){
					m_VertexArray.push_back(vSize);
					m_Type	=	enBox;
				};
	
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		Shape
				*	@return   	void
				*	@param		Float3 vPosition
				*	@param		Real fRadius
				*	@note
				*
				**/
				void	SetSphere(Real	fRadius){
					//m_VertexArray.push_back(vPosition);
					m_VertexArray.push_back(Float3(fRadius,0,0));
					m_Type	=	enSphere;
				};
				/**	\brief	���ý�����
				*   
				*	@remarks 	���ý�����
				*	@see		Shape
				*	@return   	void
				*	@param		Float3 vPosition
				*	@param		Real fHeight
				*	@param		Real fRadius
				*	@note
				*
				**/
				void	SetCapsule(Real	fHeight,Real	fRadius){
					//m_VertexArray.push_back(vPosition);
					m_VertexArray.push_back(Float3(fHeight,fRadius,0));
					m_Type	=	enCapsule;
				};
	
				/**	\brief	����͹����
				*   
				*	@remarks 	����͹����
				*	@see		Shape
				*	@return   	void
				*	@param		Float3 * vPositionArray
				*	@param		UInt uiSize
				*	@note
				*
				**/
				void	SetConvex(Float3* vPositionArray,UInt	uiSize){
					if(uiSize==0)
						return;
					m_VertexArray.resize(uiSize);
					memcpy(&m_VertexArray[0],vPositionArray,uiSize*(sizeof(Float3)));
					m_Type	=	enConvex;
				};
	
				/**	\brief	����������
				*   
				*	@remarks 	����������
				*	@see		Shape
				*	@return   	void
				*	@param		Float3 * vPositionArray
				*	@param		UInt uiSize
				*	@param		UInt * pIndex
				*	@param		UInt uiIndexSize
				*	@note
				*
				**/
				void	SetTriangleMesh(Float3* vPositionArray,UInt	uiSize,UInt*	pIndex,UInt uiIndexSize){
					if(uiSize==0	||	uiIndexSize	==	0)	
						return;
					m_VertexArray.resize(uiSize);
					memcpy(&m_VertexArray[0],vPositionArray,uiSize*(sizeof(Float3)));
					m_FaceArray.resize(uiIndexSize);
					memcpy(&m_FaceArray[0],pIndex,uiIndexSize*sizeof(UInt));
					m_Type	=	enTriangleMesh;
				}
	
	
				std::vector<Float3>		m_VertexArray;
				std::vector<UInt>		m_FaceArray;
				std::vector<Float2>		m_UVArray;
				Float3					m_vLocalPosition;
				Float4					m_vLocalQuat;
				enumType				m_Type;
				void*					m_pUserData;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXSHAPE_HEAD_FILE