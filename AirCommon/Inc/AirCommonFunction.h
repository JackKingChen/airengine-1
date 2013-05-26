/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/04/09
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonFunction.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONFUNCTION_HEAD_FILE
#define COMMONFUNCTION_HEAD_FILE


namespace	Air{
	namespace Common{
		/**	\brief	�ص�����
		*
		*	�ص�����
		*
		***/
		template<typename T_Param>
		class	IFunction{
		public:
			virtual ~IFunction(){};
			/**	\brief	����ִ�лص��ӿ�
			*
			*	����ִ�лص��ӿ�
			*
			***/
			virtual bool operator()(const T_Param&	param) = 0;
		};

		/**	\brief	��ͨ�����ص�
		*
		*	��ͨ�����ص�
		*
		***/
		template<typename T_Param>
		class	Function	:	
			public	IFunction<T_Param>{
		public:
			typedef bool (*NormalCallBack)(const T_Param&);

			Function(NormalCallBack func) :
			m_pFunction(func)
			{}

			/**	\brief	���ûص�����
			*   
			*	@remarks 	���ûص�����
			*	@see		Function
			*	@return   	bool
			*	@param		const T_Param& param
			*	@note
			*
			**/
			virtual bool operator()(const T_Param& param){
				return (*m_pFunction)(param);
			}

			//private:
			NormalCallBack m_pFunction;		///<	�ص�����
		};

		/**	\brief	��Ա�����ص�
		*
		*	��Ա�����ص�
		*
		***/
		template<typename	T_Member,typename T_Param>
		class	MemberFunction	:
			public IFunction<T_Param>{
		public:
			//! Member function	typedef
			typedef bool(T_Member::*MemberCallBack)(const T_Param&);
			MemberFunction(MemberCallBack func, T_Member* obj) :
			m_pFunction(func),
				m_pObject(obj){

			};

			/**	\brief	���ûص�����
			*   
			*	@remarks 	���ûص�����
			*	@see		MemberFunction
			*	@return   	bool
			*	@param		const T_Param& param
			*	@note
			*
			**/
			virtual bool operator()(const T_Param&	param){
				return (m_pObject->*m_pFunction)(param);
			}

			//private:
			MemberCallBack	m_pFunction;		///<	���Ա����
			T_Member*		m_pObject;			///<	��ָ��
		};

		/**	\brief	����������
		*
		*	����������
		*
		***/
		template<typename T_Param>
		class	FunctionSlot{
		public:
			FunctionSlot(){
				m_pFunction=NULL;
			};

			
			FunctionSlot(bool (*func)(const T_Param&)){
				m_pFunction	=	new	Function(func);
			};
			//���벻��ȥ ����ʾ û�����غ������� 2 ��������ͷ����
			template<typename T_Member>
			FunctionSlot(bool (T_Member::*function)(const T_Param&), T_Member* obj)
				:m_pFunction(new	MemberFunction<T_Member,T_Param>(function,obj)){
			};

			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		FunctionSlot
			*	@return   	void
			*	@note
			*
			**/
			void	Clean(){
				if(m_pFunction!=NULL){
					delete m_pFunction;
					m_pFunction	=	NULL;
				}
			}

			/**	\brief	�Ƿ�Ϊ��
			*   
			*	@remarks 	�Ƿ�Ϊ��
			*	@see		FunctionSlot
			*	@return   	bool
			*	@note
			*
			**/
			bool	IsNull(){
				return	m_pFunction	==	NULL;
			};

			IFunction<T_Param>*	m_pFunction;
		};
	};//end of	namespace	Client

	template<typename T_Source>
	void*	Convert(T_Source t){
#ifdef _X86_
		U32* pp =	(U32*)&t;	
#else
		U64* pp	=	(U64*)&t;	
#endif
		return (void*)*pp;
	};
};//end of namespace Air
#endif // COMMONFUNCTION_HEAD_FILE