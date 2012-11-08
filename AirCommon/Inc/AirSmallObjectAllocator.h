#ifndef AirSmallObjectAllocator_h__
#define AirSmallObjectAllocator_h__

#include "AirCommonHeader.h"

namespace	Air{
	class	COMMON_EXPORT	SmallObjectAllocator{
	public:
		SmallObjectAllocator(U32 uiMaxSize	=	512,U32 uiMaxCount	=	32768);
		~SmallObjectAllocator();

		void*	Alloc(U32 uiSize);
		void	Free(void* p);

	protected:
		U8*		m_pBuffer;
		U8*		m_pAllocBase;
		void**	m_pFreeBase;
		U32		m_uiMaxSize;
		U32		m_uiMaxCount;
		U32		m_uiFreeBegin;
		U32		m_uiFreeEnd;
		U32		m_uiMask;
	};
	template<class T>  
	class user_defined_allocator : public std::allocator<T>  
	{  
	public:  
		typedef std::allocator<T> base_type;  

		// ����Ҫ���¶��壬���������� list, set, map ʹ��ʱ������ֻ�ܵ��� std::allocator   
		template<class Other>  
		struct rebind  
		{  
		   typedef user_defined_allocator<Other> other;  
		};  

		// ���캯������ʵ��   
		user_defined_allocator() {};  

		user_defined_allocator(user_defined_allocator<T> const&) {};  

		user_defined_allocator<T>& operator=(user_defined_allocator<T> const&) { return (*this); };  

		// idiom: Coercion by Member Template   
		template<class Other>  
		user_defined_allocator(user_defined_allocator<Other> const&) {};  

		// idiom: Coercion by Member Template   
		template<class Other>  
		user_defined_allocator<T>& operator=(user_defined_allocator<Other> const&) { return (*this); };  

		// �ڴ�ķ������ͷſ���ʵ��Ϊ�Զ�����㷨���滻�����弴��   
		pointer allocate(size_type count) { return (pointer)__Alloc(count); };  
	
		void	deallocate(pointer ptr, size_type count) { __Free(ptr); };  
	}; 
	
#define 	air_vector(T)	std::vector<T,user_defined_allocator<T> >
}
#endif // AirSmallObjectAllocator_h__
