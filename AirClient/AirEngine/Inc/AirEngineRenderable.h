/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/06
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EngineRenderable.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINERENDERABLE_HEAD_FILE
#define ENGINERENDERABLE_HEAD_FILE

#include "AirRenderCommon.h"

namespace	Air{
	namespace Client{
		class	Material;
		namespace	Render{
			namespace	Vertex{
				class	IBuff;
				class	IDeclare;
			}
			namespace	Index{
				class	IBuff;
			}
			class	Buffer;
		}
	
		/**	\brief	��Ʒ��Ⱦ�Ļص�
		*
		*	��Ʒ��Ⱦ�Ļص�
		*
		***/
		class	ENGINE_EXPORT	Renderable{
		public:
			Renderable();
			virtual	~Renderable();

			/**	\brief	��ȡ��������
			*   
			*	@remarks 	��ȡ��������
			*	@see		Renderable
			*	@return   	Air::U32
			*	@note
			*
			**/
			virtual	U32		GetBoneCount();
			/**	\brief	��ȡ��������
			*   
			*	@remarks 	��ȡ��������
			*	@see		Renderable
			*	@return   	Air::U1
			*	@param		Float44 * pMatrixArray
			*	@note
			*
			**/
			virtual	U1		GetBoneMatrix(Float44*	pMatrixArray);
			/**	\brief	�ж��Ƿ��й���
			*   
			*	@remarks 	�ж��Ƿ��й���
			*	@see		Renderable
			*	@return   	Air::U1
			*	@note
			*
			**/
			virtual	U1		HasSkeleton();
			/**	\brief	���ÿɼ�
			*   
			*	@remarks 	���ÿɼ�
			*	@see		Renderable
			*	@return   	void
			*	@param		U1 bVisiable
			*	@note
			*
			**/
			void			SetVisiable(U1	bVisiable){
				m_bVisiable	= bVisiable;
			};
			/**	\brief	�Ƿ�ɼ�
			*   
			*	@remarks 	�Ƿ�ɼ�
			*	@see		Renderable
			*	@return   	U1
			*	@note
			*
			**/
			U1				IsVisiable(){return m_bVisiable;};
			/**	\brief	��ȡ����
			*   
			*	@remarks 	��ȡ����
			*	@see		Renderable
			*	@return   	IMaterial*
			*	@param		enumPhaseIndex	index
			*	@note
			*
			**/
			Material*		GetMaterial(enumPhaseIndex	index	=	enPI_MRT);
			void			SetMaterial(Material*	pMaterial);
			void			SetMaterialNull(enumPhaseIndex	index);
			void			SetMaterialName(CAString&	strMaterialName);

			/**	\brief	��Ⱦǰ�ص�
			*   
			*	@remarks 	��Ⱦǰ�ص�
			*	@see		Renderable
			*	@return   	void
			*	@param		Material * pMaterial
			*	@note
			*
			**/
			virtual	void	BeforeRender(Material*	pMaterial);

			/**	\brief	����������
			*   
			*	@remarks 	����������
			*	@see		Renderable
			*	@return   	void
			*	@param		U1 bUseSkin
			*	@note
			*
			**/
			void			FillBoneConstantBuffer(U1	bUseSkin	=	false);

			/**	\brief	��ȡ��Ʒ�������
			*   
			*	@remarks 	��ȡ��Ʒ�������
			*	@see		Renderable
			*	@return   	ConstantBuffer*
			*	@note
			*
			**/
			Buffer*			GetObjectConstantBuffer();
			/**	\brief	�����������
			*   
			*	@remarks 	��MovableObject����	�ڲ���������ü���
			*	@see		Renderable
			*	@return   	void
			*	@param		ConstantBuffer * pBuffer
			*	@note
			*
			**/
			void			SetObjectConstantBuffer(Buffer*	pBuffer);
			/**	\brief	��ȡ��������
			*   
			*	@remarks 	��ȡ��������
			*	@see		Renderable
			*	@return   	Buffer*
			*	@note
			*
			**/
			Buffer*			GetBoneConstantBuffer();

			/**	\brief	�ж������Ƿ���Ҫ�������
			*   
			*	@remarks 	��SceneNode->MovableObject->Renderable���ݶ���	����������
			*	@see		Renderable
			*	@return   	Air::U1
			*	@note
			*
			**/
			U1				NeedWorldMatrix();
			/**	\brief	���������Ƿ���Ҫ�������
			*   
			*	@remarks 	��SceneNode->MovableObject->Renderable���ݶ���
			*	@see		Renderable
			*	@return   	void
			*	@param		U1 bNeed
			*	@note
			*
			**/
			void			SetNeedWorldMatrix(U1	bNeed	=	false);

			const DrawBuff&		GetDrawBuff(){
				return	m_DrawBuff;
			};

			/**	\brief	����Instance����
			*   
			*	@remarks 	����Instance����
			*	@see		Renderable
			*	@return   	void
			*	@param		U32 uiCount
			*	@note
			*
			**/
			void			SetInstanceCount(U32	uiCount);

			void			AddToRenderQueue(U32	uiPhaseFlag);

			virtual	Matrix*	GetWorldMatrix(){return	NULL;};
		protected:
			U1							m_bVisiable;			///<	�Ƿ�ɼ�
			U1							m_bNeedWorldMatrix;		///<	�Ƿ���Ҫ�������	//Ĭ����Ҫ�����������
			Material*					m_pMaterial[32];		///<	����
			DrawBuff					m_DrawBuff;				///<	��Ⱦ����
			Buffer*						m_pObjectCB;			///<	��MovableObject->Renderable���ݶ���
			Buffer*						m_pBoneCB;
		};

		typedef	TVector<Renderable*>	RenderableVector;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINERENDERABLE_HEAD_FILE