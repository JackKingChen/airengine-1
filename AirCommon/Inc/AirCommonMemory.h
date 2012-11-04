#ifndef COMMONMEMORY_HEAD_FILE
#define COMMONMEMORY_HEAD_FILE

#include <memory.h>
#include "AirCommon.h"
namespace Air{

	/**	\brief	���������ڴ��
	*   
	*	@remarks 	���������ڴ��
	*	@see		
	*	@return   	COMMON_EXPORT	void*
	*	@param		UInt uiSize
	*	@note
	*
	**/
	COMMON_EXPORT	void*	__Alloc(unsigned int	uiSize);
	/**	\brief	�ͷ������ڴ��
	*   
	*	@remarks 	�ͷ������ڴ��
	*	@see		
	*	@return   	COMMON_EXPORT	void
	*	@param		void * p
	*	@note
	*
	**/
	COMMON_EXPORT	void	__Free(void*	p);

#ifdef	USE_AIR_ALLOC
	#define AIR_ALLOC(Type,Size)	static_cast<Type*>(__Alloc(Size))
	#define AIR_FREE(p)				if(p!=NULL){__Free(p);p=NULL;}
#else
	#define AIR_ALLOC(Type,Size)	(Type*)(new	unsigned char[Size])
	#define AIR_FREE(p)				if(p!=NULL){delete[] p;p=NULL;}
#endif

	template<typename T>
	T* AirNew()
	{
		void *p	=	__Alloc(sizeof(T));
		return new(p)T();
	};
	template<typename T>
	T* AirNew(unsigned int	uiCount)
	{
		T *p	=	(T*)__Alloc(sizeof(T)*uiCount);
		for(unsigned int i=0;i<uiCount;i++){
			new (&p[i])T();
		}
		return p;
	};
	template<typename T,typename P0>
	T* AirNew(P0 p0)
	{
		void *p	=	__Alloc(sizeof(T));
		return new(p)T(p0);
	};
	template<typename T,typename P0,typename P1>
	T* AirNew(P0 p0,P1 p1)
	{
		void *p	=	__Alloc(sizeof(T));
		return new(p)T(p0,p1);
	};
	template<typename T>
	void	AirDelete(T* p){
		if(p!=NULL){
			p->~T();
			__Free(p);
		}
	};
	template<typename T>
	void	AirDeleteArray(T* p,unsigned int uiCount){
		if(p!=NULL){
			for(unsigned int i=0;i<uiCount;i++){
				p[i].~T();
			}
			__Free(p);
		}
	};
	namespace Common{
		/**	\brief	�ڴ濽��
		*   
		*	@remarks 	ע�� ������2�ֽڶ���	�ڲ�û�жԿ�ָ������ж�
		*	@see		
		*	@return   	void
		*	@param		void * pDst
		*	@param		void * pSrc
		*	@param		int iCount
		*	@note
		*
		**/
		COMMON_EXPORT	void	Memcpy2(void* pDst,const void* pSrc,int iSize);
		/**	\brief	�ڴ濽��
		*   
		*	@remarks 	ע�� ������4�ֽڶ���	�ڲ�û�жԿ�ָ������ж�
		*	@see		
		*	@return   	void
		*	@param		void * pDst
		*	@param		void * pSrc
		*	@param		int iCount
		*	@note
		*
		**/
		COMMON_EXPORT	void	Memcpy4(void* pDst,const void* pSrc,int iSize);
		/**	\brief	�ڴ�Ա�
		*   
		*	@remarks 	ע�� ������4�ֽڶ���	�ڲ�û�жԿ�ָ������ж�
		*	@see		
		*	@return   	bool
		*	@param		void * p1
		*	@param		void * p2
		*	@param		int iCount
		*	@note
		*
		**/
		COMMON_EXPORT	bool	Memcmp4(void* p1,const void* p2,int iSize);
	
		/**	\brief	�ԱȲ�����
		*   
		*	@remarks 	�ԱȲ�����������ڴ�鲻ͬ�������
		*	@see		
		*	@return   	bool
		*	@param		void * p1
		*	@param		void * p2
		*	@param		unsigned int uiSize
		*	@note
		*
		**/
		inline	bool	CompareCopy(void*	p1,void*	p2,unsigned int uiSize	){
			if(memcmp(p1,p2,uiSize)!=0){
				memcpy(p1,p2,uiSize);
				return	false;
			}
			return	true;
		};
		/**	\brief	�ԱȲ�����
		*   
		*	@remarks 	�ԱȲ�����������ڴ�鲻ͬ������� 4�ֽڶ���
		*	@see		
		*	@return   	bool
		*	@param		void * p1
		*	@param		void * p2
		*	@param		unsigned int uiSize
		*	@note
		*
		**/
		inline	bool	CompareCopy4(void* p1,const void* p2,unsigned int uiSize){
			if(!Memcmp4(p1,p2,uiSize)){
				Memcpy4(p1,p2,uiSize);
				return	false;
			}
			return	true;
		};
	
	};
};
#endif // COMMONMEMORY_HEAD_FILE