#ifndef INTERFACEAUTORELEASEMANAGER_HEAD_FILE
#define INTERFACEAUTORELEASEMANAGER_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Engine{
	
		/**	\brief	�Զ��ͷ���
		*
		*	��Ҫ��������Ƶ�������ݻٵ����� ������ο� ����Ч�� ��Ч
		*
		***/
		class	IAutoReleaseManager{
		public:
			IAutoReleaseManager();
	
			/**	\brief	�����Ҫ�Զ��ͷŵĲ�Ʒ
			*   
			*	@remarks 	�����Ҫ�Զ��ͷŵĲ�Ʒ
			*	@see		IAutoReleaseManager
			*	@return   	void
			*	@param		IProduct * pProduct
			*	@note
			*
			**/
			void	PushObject2Release(IProduct*	pProduct);
			/**	\brief	��ȡ��Ʒ����
			*   
			*	@remarks 	��ȡ��Ʒ����
			*	@see		IAutoReleaseManager
			*	@return   	UInt
			*	@note
			*
			**/
			UInt	GetProductCount();
			/**	\brief	�ݻ�һ����Ʒ �����ǰ�������ڻ���ֵ
			*   
			*	@remarks 	��ݻ�һ��
			*	@see		IAutoReleaseManager
			*	@return   	void
			*	@note
			*
			**/
			void	ReleaseOneObject();
			/**	\brief	�ͷ����в�Ʒ
			*   
			*	@remarks 	�ͷ����в�Ʒ
			*	@see		IAutoReleaseManager
			*	@return   	void
			*	@note
			*
			**/
			void	ReleaseAllAutoObject();
			/**	\brief	���û�������С
			*   
			*	@remarks 	���û�������С
			*	@see		IAutoReleaseManager
			*	@return   	void
			*	@param		UInt uiSize
			*	@note
			*
			**/
			inline	void	SetCacheSize(UInt	uiSize){
				m_uiCacheSize	=	uiSize;
			};
			/**	\brief	��ȡ��������С
			*   
			*	@remarks 	��ȡ��������С
			*	@see		IAutoReleaseManager
			*	@return   	UInt
			*	@note
			*
			**/
			UInt	GetCacheSize(){
				return	m_uiCacheSize;
			};
	
			typedef	std::list<IProduct*>	ProductList;
			typedef	ProductList::iterator	ProductListItr;
	
			ProductList				m_lstProduct;
			SInt					m_uiProductCount;
			SInt					m_uiCacheSize;
		};
	
	};
};
#endif // INTERFACEAUTORELEASEMANAGER_HEAD_FILE