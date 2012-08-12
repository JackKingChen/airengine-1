/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InterfalHell	Xinhe
 \date      2011/03/29
 \version   ver 0.6.0.0
 \filepath  f:\EngineSource\Air\AirClient\AirEnginePlugin\AirRender9
 \filename  RenderVertexDeclarationManager.h
 \note     
       
 \attention:
			
 \remarks    created by InterfalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef RENDERVERTEXDECLARATIONMANAGER_HEAD_FILE
#define RENDERVERTEXDECLARATIONMANAGER_HEAD_FILE

#include "AirRenderHeader9.h"

namespace	Air{
	namespace Client{
	
		namespace	Render{

			typedef	Vertex::IDeclare::ElementVector	VDElementVector;

			//������������
			struct	VD_Data{
				VD_Data(){
					pVD		=	NULL;
				};
				IDirect3DVertexDeclaration9*	pVD;
				VDElementVector					vecElement;
			};

			//����������������
			typedef	std::vector<VD_Data>		VD_DataVector;

			/**	\brief	��������������
			*
			*	��������������
			*
			***/
			class	VertexDeclarationManager
				:	public	Singleton<VertexDeclarationManager>
			{
			public:
				virtual	~VertexDeclarationManager();


				/**	\brief	������������
				*   
				*	@remarks 	������������
				*	@see		VertexDeclarationManager
				*	@return   	IDirect3DVertexDeclaration9*
				*	@param		VDElementVector & vecElement
				*	@note
				*
				**/
				IDirect3DVertexDeclaration9*	CreateVD(VDElementVector& vecElement);
				/**	\brief	�ݻ����ж�������
				*   
				*	@remarks 	�ݻ����ж�������
				*	@see		VertexDeclarationManager
				*	@return   	void
				*	@note
				*
				**/
				void	DestroyAllVD();


				VD_DataVector	m_vecVD_Data;
			};
		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // RENDERVERTEXDECLARATIONMANAGER_HEAD_FILE