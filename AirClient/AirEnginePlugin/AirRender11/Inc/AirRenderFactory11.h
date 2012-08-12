//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InterfalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.4.0.0
 \filepath  f:\tj.src\Client0400\Render
 \filename  RenderFactory.h
 \note     
       
 \attention:
			��Ⱦ����Ĺ�������
 \remarks    created by InterfalHell version 0.4.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef RENDERFACTORY_HEAD_FILE
#define RENDERFACTORY_HEAD_FILE

#include "AirRenderHeader11.h"
#include "AirRenderDevice11.h"


namespace Air{
	
	namespace Client{
	
		namespace	Render{
	
			/**	\brief	��Ⱦ��Ʒ����
			*
			*	��Ⱦ��Ʒ����
			*
			***/
			class	Product	:	
				public	IProduct{
			public:
				Product(CAString&	strName):IProduct(strName){
					m_Pool					=	POOL_MANAGED;
					m_bDestroyByLostDevice	=	false;
					m_bLoaded				=	false;
				};
				//virtual	~Product(){};
	
		
				/**	\brief	��Ҫ���صĴ���
				*   
				*	@remarks 	��Ҫ���صĴ���
				*	@see		Product
				*	@return   	U1
				*	@param		U1 bBackThread
				*	@note
				*
				**/
				virtual	U1	Create( )	=	NULL;
				/**	\brief	��Ҫ���صĴݻ�
				*   
				*	@remarks 	����Ϊ�Ƿ�Ϊ���̴߳���
				*	@see		Product
				*	@return   	U1
				*	@param		U1 bBackThread
				*	@note
				*
				**/
				virtual	U1	Destroy( )	=	NULL;
	
				/**	\brief	�豸��ʧ�ص�����
				*   
				*	@remarks 	����Ϊ�Ƿ�Ϊ���̴߳���
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnLostDevice(){
					if(m_Pool == POOL_DEFAULT){
						Destroy();
						m_bDestroyByLostDevice	=	true;
					}
					return	true;
				};
				/**	\brief	�����豸�ص�����
				*   
				*	@remarks 	�����豸�ص�����
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnResetDevice(){
					if(m_Pool == POOL_DEFAULT	&&	m_bDestroyByLostDevice){
						Create();
						m_bDestroyByLostDevice	=	false;
					}
					return	true;
				};
	
				inline	U1	IsLoad(){
					return	m_bLoaded;
				};
				/**	\brief	DirextX����Դ�ͷ�ģ�庯��
				*   
				*	@remarks 	DirextX����Դ�ͷ�ģ�庯��
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				template	<typename	T_DirectXType>
				U1	DirectXDestroy(){
	
	
					T_DirectXType	pDirectXObject	=	(T_DirectXType)m_pObject;
					if(pDirectXObject	!=	NULL){
						pDirectXObject->Release();
						pDirectXObject=NULL;
					}
					m_pObject	=	NULL;
					return true;
				};
	
				#ifndef DirectXImplement
				#define DirectXImplement(Type,Function)	\
					Type	p	=	(Type)m_pObject;\
					if(p!=NULL)p->Function;\
					return true;
				#endif
				/**	\brief	��ʧ�豸ģ�庯��
				*   
				*	@remarks 	��ʧ�豸ģ�庯��
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				template	<typename	T_DirectXType>
				U1	DirectXOnLostDevice(){
					DirectXImplement(T_DirectXType,OnLostDevice());
				};
				/**	\brief	�����豸ģ�庯��
				*   
				*	@remarks 	�����豸ģ�庯��
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				template	<typename	T_DirectXType>
				U1	DirectXOnResetDevice(){
					DirectXImplement(T_DirectXType,OnResetDevice());
				};
	
				/**	\brief	�ж��Ƿ�Ϊ��
				*   
				*	@remarks 	�ж��Ƿ�Ϊ��
				*	@see		Product
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	IsNull(){
					U1	b	=	(m_pObject	==	NULL);
					return	b;
				}
			protected:
				enumPool			m_Pool;					///<	��Դ����ʽ
				U1					m_bDestroyByLostDevice;	///<	�Ƿ񱻶�ʧ�豸ʱ�ݻ�
				U1					m_bLoaded;				///<	�Ƿ��Ѿ�����
			private:
			};
			class	Factory	:	public	IFactory
			{
			public:
				virtual	~Factory(){};
				/**	\brief	�豸��ʧ�ص�����
				*   
				*	@remarks 	�豸��ʧ�ص�����
				*	@see		Factory
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnLostDevice(){
					ProductMapItr	i	=	m_mapProduct.begin();
					for(;i!=m_mapProduct.end();i++){
						Product*	pProduct	=	(Product*)i->second;
						if(pProduct==NULL)
							continue;
						if(pProduct->IsNull())
							continue;
						pProduct->OnLostDevice();
					}
					return	true;
				};
				/**	\brief	�豸���ûص�����
				*   
				*	@remarks 	�豸���ûص�����
				*	@see		Factory
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	OnResetDevice(){
					ProductMapItr	i	=	m_mapProduct.begin();
					for(;i!=m_mapProduct.end();i++){
						Product*	pProduct	=	(Product*)i->second;
						if(pProduct==NULL)
							continue;
	
						pProduct->OnResetDevice();
					}
					return	true;
				};
			protected:
				
			private:
				
			};
	
			
		}
	
	};
};
#endif // RENDERFACTORY_HEAD_FILE