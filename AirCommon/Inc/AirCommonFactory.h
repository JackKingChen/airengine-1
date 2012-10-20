//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonFactory.h
 \note     
       
 \attention:
			����ģ��
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONFACTORY_HEAD_FILE
#define COMMONFACTORY_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonProduct.h"
#include "AirCommonLock.h"
namespace Air{
	
	namespace Common{
	
		/**	\brief	�����б�
		*
		*	�����ഴ��ʱ��ʹ�õĲ����б�
		*
		***/
		typedef	void						IFactoryParamList;
		/**	\brief	����ģ��ӿڻ���
		*
		*	����ģ��ӿڻ���
		*
		***/
		class COMMON_EXPORT IBaseFactory{
		public:
			IBaseFactory();
			virtual ~IBaseFactory();
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		IBaseFactory
			*	@return   	void
			*	@param		AString strTypeName
			*	@note
			*
			**/
			virtual void SetType(const AString& strTypeName);
			/**	\brief	��ȡ��������
			*   
			*	@remarks 	��ȡ��������
			*	@see		IBaseFactory
			*	@return   	AString
			*	@note
			*
			**/
			const AString& GetType()const;
		protected:
			AString		m_strTypeName;		///<	����������
		};
		/**	\brief ����ģ��
		*
		*	����ģ�� ��Ҫ���ڴ��� ɾ��
		*
		***/
		class COMMON_EXPORT IFactory : public IBaseFactory{
		friend class IFactoryManager;
		public:
			typedef stdext::hash_map<AString,IProduct*>					ProductMap;
			typedef stdext::hash_map<AString,IProduct*>::iterator		ProductMapItr;
			typedef stdext::hash_map<AString,IProduct*>::value_type		ProductMapPair;
		public:
			IFactory();
			virtual ~IFactory();
			/**	\brief	������Ʒ
			*   
			*	@remarks 	������Ʒ
			*	@see		IFactory
			*	@return   	T_Product*
			*	@param		AString strName
			*	@note
			*
			**/
			template<typename T_Product>
			T_Product	NewProduct(CAString& strName,IFactoryParamList* lstParam = NULL){
				return dynamic_cast<T_Product>(Create(strName,lstParam));
			};
	
			virtual IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam = NULL)=NULL;
	
	
			/**	\brief	�ݻٲ�Ʒ
			*   
			*	@remarks 	
			*	@see		IFactory
			*	@return   	bool
			*	@param		T_Product * pProduct
			*	@note
			*
			**/
			virtual bool		Destroy(IProduct* pProduct);
	
			/**	\brief	�������в�Ʒ
			*   
			*	@remarks 	�������в�Ʒ
			*	@see		IFactory
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool		DestroyAllProduct();
	
			/**	\brief	���ز�Ʒ����
			*   
			*	@remarks 	���ز�Ʒ����
			*	@see		IFactory
			*	@return   	int
			*	@note
			*
			**/
			virtual U32			GetProductCount()const;
	
			/**	\brief	���Ҳ�Ʒ
			*   
			*	@remarks 	��ȡ��Ʒ ͨ�����ֲ���
			*	@see		IFactory
			*	@return   	T_Product
			*	@param		AString strName
			*	@note
			*
			**/
			template<typename T_Product>
			T_Product GetProduct(const AString& strName){
				return dynamic_cast<T_Product>(GetProduct(strName));
			};
			IProduct* GetProduct(const AString& strName);
			/**	\brief	�Ƿ�������б���
			*   
			*	@remarks 	
			*	@see		IFactory
			*	@return   	bool
			*	@param		AString strName
			*	@note
			*
			**/
			bool Exist(const AString& strName)const;
			/**	\brief	���б����Ƴ�
			*   
			*	@remarks 	���Ƴ� �����ݻ�
			*	@see		IFactory
			*	@return   	bool
			*	@param		const AString& strName
			*	@note
			*
			**/
			virtual bool Erase(const AString& strName);
			/**	\brief	���б����Ƴ�
			*   
			*	@remarks 	���Ƴ� �����ݻ�
			*	@see		IFactory
			*	@return   	bool
			*	@param		IProduct*  pProduct
			*	@note
			*
			**/
			virtual bool Erase(IProduct* pProduct);
	
			/**	\brief	��ȡ��Ʒ�б�
			*   
			*	@remarks 	��ȡ��Ʒ�б�
			*	@see		IFactory
			*	@return   	ProductList&
			*	@note
			*
			**/
			const ProductMap&		GetProductList()const;
		//protected:
			/**	\brief	�����Ʒ�б���
			*   
			*	@remarks 	�������ഴ����һ����Ʒ֮�� �ǵõ���Insert���� ����Ʒָ����ӵ��������б��� �����ڹ��������ٵ�ʱ�� ����δ���ٵĲ�Ʒ��һͬ������
			*	@see		IFactory
			*	@return   	void
			*	@param		IProduct * pProduct
			*	@note
			*
			**/
			void		Insert(IProduct* pProduct);
	
			/**	\brief	���ù���������
			*   
			*	@remarks 	���ù���������
			*	@see		IFactory
			*	@return   	void
			*	@param		IFactoryManager * pFactoryMgr
			*	@note
			*
			**/
			void		SetFactoryManager(IFactoryManager* pFactoryMgr);
		protected:
			ProductMap								m_mapProduct;		///<	��Ʒ�б�
			IFactoryManager*						m_pFactoryMgr;		///>	����������
			CriticalSection							m_CS;				///<	�ٽ�����
		};
		/**	\brief	����������ģ��
		*
		*	����������ģ�� ������
		*
		***/
		class COMMON_EXPORT IFactoryManager : public IBaseFactory{
		public:
			IFactoryManager();
			virtual ~IFactoryManager();
	
			/**	\brief	���һ������
			*   
			*	@remarks 	���һ������
			*	@see		IFactoryManager
			*	@return   	void
			*	@param		IBaseFactory * pFactory
			*	@note
			*
			**/
			virtual void AddFactory(IFactory* pFactory);
			/**	\brief	�Ƴ�����
			*   
			*	@remarks 	�Ƴ�����
			*	@see		IFactoryManager
			*	@return   	void
			*	@param		IBaseFactory * pFactory
			*	@note
			*
			**/
			virtual void RemoveFactory(IFactory* pFactory);
			/**	\brief	�Ƴ�����
			*   
			*	@remarks 	�Ƴ�����
			*	@see		IFactoryManager
			*	@return   	void
			*	@param		const AString& strFactoryName
			*	@note
			*
			**/
			virtual void RemoveFactory(const AString& strFactoryName);
			/**	\brief	��ȡ����ָ��
			*   
			*	@remarks 	��ȡ����ָ��
			*	@see		IFactoryManager
			*	@return   	*
			*	@param		const AString& strFactoryName
			*	@note
			*
			**/
			IFactory* GetFactory(const AString& strFactoryName)const;
	
			/**	\brief	��ȡ��Ʒ
			*   
			*	@remarks 	��ȡ��Ʒ
			*	@see		IFactoryManager
			*	@return   	IProduct*
			*	@note
			*
			**/
			IProduct* GetProduct(const AString& strName,const AString& strFactoryName)const;
	
			/**	\brief	������Ʒ
			*   
			*	@remarks 	������Ʒ
			*	@see		IFactoryManager
			*	@return   	T_Product*;
			*	@param		const AString& strName
			*	@param		const AString& strFactoryName
			*	@param		IFactoryParamList* lstParam
			*	@note
			*
			**/
			template<typename T_Product>
			T_Product CreateProduct(const AString& strName,const AString& strFactoryName,IFactoryParamList* lstParam = NULL){
				IProduct*	pProduct	=	CreateProduct(strName,strFactoryName,lstParam);
				if(pProduct==NULL)
					return	NULL;
				T_Product	p	=	dynamic_cast<T_Product>(pProduct);
				if(	p	==	NULL){
					pProduct->ReleaseRef();
				}
				return p;
			};
			IProduct* CreateProduct(const AString& strName,const AString& strFactoryName,IFactoryParamList* lstParam = NULL);
	
			/**	\brief	�ݻٲ�Ʒ
			*   
			*	@remarks 	
			*	@see		IFactoryManager
			*	@return   	bool
			*	@param		T_Product * pProduct
			*	@note
			*
			**/
	
			bool Destroy(IProduct* pProduct);
	
			/**	\brief	�ݻٲ�Ʒ
			*   
			*	@remarks 	�ݻٲ�Ʒ
			*	@see		IFactoryManager
			*	@return   	bool
			*	@param		T_Product pProduct
			*	@note
			*
			**/
	 		template	<typename	T_Product>
			bool DestroyProduct(T_Product* pProduct){
				//������Ҫע����Ǽ̳������� ����Ҫ��dynamic_cast
				//������ܻ�����쳣
				//����ͼ�ļ̳��� ���Ҫ��A*->B*����Ҫʹ��dynamic_cast
				//------------------------------------------------------
				//	A     B
				//	 \   /
				//    \ /
				//	   C
				//     |
				//     |
				//     D
				//------------------------------------------------------
				m_CS.Enter();
	 			IProduct*	p	=	dynamic_cast<IProduct*>(pProduct);
	 			bool	bReturn	= Destroy(p);
	 			pProduct	=	NULL;
				m_CS.Leave();
	 			return bReturn;
	 		};
	
			/**	\brief	�ͷ������Ѵ����Ĳ�Ʒ
			*   
			*	@remarks 	�ͷ������Ѵ����Ĳ�Ʒ
			*	@see		IFactoryManager
			*	@return   	bool
			*	@note
			*
			**/
			bool DestroyAllProduct();
	
			/**	\brief	�������й���
			*   
			*	@remarks 	�������й���
			*	@see		IFactoryManager
			*	@return   	bool
			*	@note
			*
			**/
			virtual bool DestroyAllFactory();
	
			typedef stdext::hash_map<AString,IFactory*>				FactoryMap;			///<	�����б�
			typedef stdext::hash_map<AString,IFactory*>::iterator	FactoryMapItr;		///<	�����б������
			typedef stdext::hash_map<AString,IFactory*>::value_type	FactoryMapPair;		///<	�����б���
	
			typedef	std::list<IFactory*>							FactoryList;
			typedef	FactoryList::iterator							FactoryListItr;
		protected:
			FactoryMap		m_mapFactory;		///<	�����б�
			FactoryList		m_lstFactory;
			CriticalSection	m_CS;				///<	�ٽ�����
		};
	
	

};
	/**	\brief	ģ�幤���޲���
	*
	*	ģ�幤���޲���
	*
	***/
	template<typename	T_Product>
	class	NoParamFactory	:	
		public	Common::IFactory{
	public:
		NoParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			return	new	T_Product(strName);
		}
	};
	/**	\brief	ģ�幤���в���
	*
	*	ģ�幤���в���
	*
	***/
	template<typename	T_Product>
	class	ParamFactory	:	
		public	Common::IFactory{
	public:
		ParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			if(lstParam	==	NULL)
				return	NULL;
			return	new	T_Product(strName,(T_Product::Info*)lstParam);
		}
	};
		/**	\brief	ģ�幤���в���
	*
	*	ģ�幤���в���
	*
	***/
	template<typename	T_Product>
	class	OptionParamFactory	:	
		public	Common::IFactory{
	public:
		OptionParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			return	new	T_Product(strName,(T_Product::Info*)lstParam);
		}
	};
	/**	\brief	ģ�幤���в���
	*
	*	ģ�幤���в��� �Ǳ�׼
	*
	***/
	template<typename	T_Product,typename	T_ProductInfo>
	class	ExtraParamFactory	:	
		public	Common::IFactory{
	public:
		ExtraParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			if(lstParam	==	NULL)
				return	NULL;
			return	new	T_Product(strName,(T_ProductInfo*)lstParam);
		}
	};
	/**	\brief	ģ�幤����ѡ����
	*
	*	ģ�幤����ѡ���� �Ǳ�׼
	*
	***/
	template<typename	T_Product,typename	T_ProductInfo>
	class	ExtraOptionParamFactory	:	
		public	Common::IFactory{
	public:
		ExtraOptionParamFactory(const AString&	strName){
			m_strTypeName	=	strName;
		};
		virtual	Common::IProduct*	NewProduct(CAString& strName,Common::IFactoryParamList* lstParam /* = NULL */){
			return	new	T_Product(strName,(T_ProductInfo)lstParam);
		}
	};
};
#endif