#ifndef RENDERVERTEXBUFF_HEAD_FILE
#define RENDERVERTEXBUFF_HEAD_FILE

#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"

namespace Air{
	
	namespace Client{
	
		namespace	Render{
	
			namespace Vertex{		
				/**	\brief	��������
				*
				*	��������
				*
				***/
				class Declare9	:
					public	IDeclare{
				public:
					Declare9(CAString&	strName,Info*	pInfo);
					/**	\brief	��ȡ��������
					*   
					*	@remarks 	��������Ϊ����Ⱦ��ʱ��Ŵ���
					*	@see		Declare
					*	@return   	IDirect3DVertexDeclaration9*
					*	@note
					*
					**/
					virtual	void*	GetDeclare();
				protected:
					IDirect3DVertexDeclaration9*	m_pDeclare;
				};
				/**	\brief	������������
				*
				*	������������
				*
				***/
				class	Declare9Factory	:
					public	Factory{
				public:
					Declare9Factory();
					/**	\brief	����
					*   
					*	@remarks 	����
					*	@see		DeclareFactory
					*	@return   	IProduct*
					*	@param		AString& strName
					*	@param		IFactoryParamList * lstParam
					*	@note
					*
					**/
					virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
	
				};
				/**	\brief	���㻺��
				*
				*	���㻺��
				*
				***/
				class Buff9	:	
					public	Buffer{
				public:
	
				public:
					Buff9(CAString&	strName,Info*	pInfo);
					/**	\brief	�ݻ�
					*   
					*	@remarks 	�ݻ�
					*	@see		Buff
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Destroy( );
	
					virtual	void*	GetBuffer();

					IDirect3DVertexBuffer9*	m_pBuffer;
				};
			};
		}
	
	};
};
#endif // RENDERVERTEXBUFF_HEAD_FILE