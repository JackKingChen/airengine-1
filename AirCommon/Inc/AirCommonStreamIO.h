/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/13
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonStream.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONSTREAM_HEAD_FILE
#define COMMONSTREAM_HEAD_FILE

#include "AirCommonData.h"

namespace	Air{

	namespace Common{
		/**	\brief	���������
		*
		*	���������
		*
		***/
		class	COMMON_EXPORT	StreamIO	:	public MemoryObject{
		public:
			StreamIO();
			virtual	~StreamIO();

			/**	\brief	��λָ��
			*   
			*	@remarks 	��λָ��
			*	@see		StreamIO
			*	@return   	void
			*	@param		S32 iOffset
			*	@note
			*
			**/
			void	Seek(S32	iOffset);
			/**	\brief	�ƶ�ָ�뵽ͷ��
			*   
			*	@remarks 	�ƶ�ָ�뵽ͷ��
			*	@see		StreamIO
			*	@return   	void
			*	@note
			*
			**/
			void	SeekBegin();
			/**	\brief	�ƶ�ָ�뵽β��
			*   
			*	@remarks 	�ƶ�ָ�뵽β��
			*	@see		StreamIO
			*	@return   	void
			*	@note
			*
			**/
			void	SeekEnd();
			/**	\brief	����С
			*   
			*	@remarks 	����С
			*	@see		StreamIO
			*	@return   	Air::U32
			*	@note
			*
			**/
			U32		Size();

			/**	\brief	�Ƿ���Ч
			*   
			*	@remarks 	�Ƿ���Ч
			*	@see		StreamIO
			*	@return   	Air::U1
			*	@note
			*
			**/
			U1		IsVaild();

			U8*		m_pBegin;
			U8*		m_pEnd;
			U8*		m_pCurrent;
		};
		/**	\brief	��ȡ��
		*
		*	��ȡ��
		*
		***/
		class	COMMON_EXPORT	StreamReader	:
			public	StreamIO{
		public:
			StreamReader();
			StreamReader(const	void*		pData,U32		uiSize);
			/**	\brief	��ȡһ���ڴ�
			*   
			*	@remarks 	��ȡ����	ǰ4�ֽ� ���ݳ��� ���� ����
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@param		File::Data & data
			*	@note
			*
			**/
			U1		ReadData(Data&	data);
			/**	\brief	��ȡָ����С��һ���ڴ�
			*   
			*	@remarks 	��ȡָ����С��һ���ڴ�	��Ҫ������ڴ� �Լ��ߴ�
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@param		Data & data
			*	@note
			*
			**/
			U1		ReadDataNoSize(Data&	data);
			/**	\brief	��ȡ�ַ���
			*   
			*	@remarks 	��ȡ�ַ���	ǰ4�ֽ� �ַ������� ���� �ַ�����
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@param		AString & str
			*	@note
			*
			**/
			U1		ReadString(AString&	str);
			/**	\brief	��ȡһ������
			*   
			*	@remarks 	�ڴ���Ҫ�Լ����룬�ٴ����ַ �� ��ȡ�Ĵ�С
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@param		void * p
			*	@param		U32 uiSize
			*	@note
			*
			**/
			U1		ReadBufferNoSize(void*	p,U32	uiSize);
			template<typename T>
			U1		ReadStruct(T&	t){
				return	ReadBufferNoSize(&t,sizeof(T));
			};
			/**	\brief	��ȡ��������
			*   
			*	@remarks 	���� bool char short int float double ֮��
			*	@see		StreamReader
			*	@return   	T
			*	@note
			*
			**/
			template<typename	T>
			T		Read(){
				T	val		=	*(T*)m_pCurrent;
				m_pCurrent+=sizeof(T);
				return	val;
			};
			/**	\brief	��ȡ��������
			*   
			*	@remarks 	���� bool char short int float double ֮��
			*	@see		StreamReader
			*	@return   	T
			*	@note
			*
			**/
			template<typename	T>
			void	Read(T&	t){
				t	=	*(T*)m_pCurrent;
				m_pCurrent+=sizeof(T);
			}

		};
		/**	\brief	д����
		*
		*	д����
		*
		***/
		class	COMMON_EXPORT	StreamWriter	:	
			public	StreamIO{
		public:
			//WriteAPI
			template<typename	T>
			void	Write(const	T&	val){
				*(T*)m_pCurrent	=	val;
				m_pCurrent+=sizeof(T);
			};
			/**	\brief	д��ָ����С������
			*   
			*	@remarks 	ǰ4�ֽ� ���ݳ��� ���� ����
			*	@see		StreamWriter
			*	@return   	void
			*	@param		const void * val
			*	@param		U32 uiSize
			*	@note
			*
			**/
			void	WriteBuffer(const void*		val,U32	uiSize);
			/**	\brief	д��ָ����С������
			*   
			*	@remarks 	ֻд������
			*	@see		StreamWriter
			*	@return   	void
			*	@param		const void * val
			*	@param		U32 uiSize
			*	@note
			*
			**/
			void	WriteBufferNoSize(const void*		val,U32	uiSize);
			/**	\brief	д���ַ���
			*   
			*	@remarks 	ǰ4�ֽ� ���ݳ��� ���� ����
			*	@see		StreamWriter
			*	@return   	void
			*	@param		const AString & str
			*	@note
			*
			**/
			void	WriteString(const	AString&	str);
			/**	\brief	д������
			*   
			*	@remarks 	ǰ4�ֽ� ���ݳ��� ���� ����
			*	@see		StreamWriter
			*	@return   	void
			*	@param		File::Data & data
			*	@note
			*
			**/
			void	WriteData(Data&	data);
			/**	\brief	д������
			*   
			*	@remarks 	��д����
			*	@see		StreamWriter
			*	@return   	void
			*	@param		Data & data
			*	@note
			*
			**/
			void	WriteDataNoSize(Data&	data);
			/**	\brief	д��ṹ��
			*   
			*	@remarks 	������ ����д��4�ֽڵ� �ṹ���С
			*	@see		StreamWriter
			*	@return   	void
			*	@param		T & t
			*	@note
			*
			**/
			template<typename T>
			void	WriteStruct(const	T& t){
					WriteBufferNoSize(&t,sizeof(T));
			};
		};

		class	COMMON_EXPORT	MemoryWriter	:	public	StreamWriter{
		public:
			MemoryWriter(U32	uiSize);
			virtual	~MemoryWriter();

			const	void*	GetDataPtr();
			U32				GetDataSize();
		};

		class	COMMON_EXPORT	FileReader	:	public	StreamReader{
		public:
			FileReader(CAString&	strName);
			virtual	~FileReader();


		};
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONSTREAM_HEAD_FILE