#ifndef COMMONNETFILE_HEAD_FILE
#define COMMONNETFILE_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonFile.h"
namespace Air{
	
	namespace Common{
	
		typedef	File::Data	Buffer;
	
		/**	\brief	�����ļ���ӿ�
		*
		*	�����ļ���ӿ�	�����ļ�����
		*
		***/
		class	NetFile{
		public:
			NetFile(){
				m_Type	=	0;
			};
			virtual	~NetFile(){
	
			};
	
			/**	\brief	��ȡ����
			*   
			*	@remarks 	��ȡ����
			*	@see		NetFile
			*	@return   	int
			*	@note
			*
			**/
			int					GetType(){
				return	m_Type;
			};
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		NetFile
			*	@return   	void
			*	@param		int iType
			*	@note
			*
			**/
			void				SetType(int iType){
				m_Type	=	iType;
			};
	
			/**	\brief	�����ļ�
			*   
			*	@remarks 	�����ļ�
			*	@see		NetFile
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1			Load()								=	NULL;
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		NetFile
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1			Save()								=	NULL;
	
			/**	\brief	����Դ����
			*   
			*	@remarks 	���ڴ����
			*	@see		NetFile
			*	@return   	U1
			*	@param		Buffer * pBuffer
			*	@note
			*
			**/
			virtual	U1			LoadFromBuffer(Buffer*	pBuffer)	=	NULL;
			/**	\brief	���л�Ϊ�ڴ�
			*   
			*	@remarks 	���л�Ϊ�ڴ�
			*	@see		NetFile
			*	@return   	Buffer*
			*	@note
			*
			**/
			virtual	Buffer*		BuildBuffer()						=	NULL;
	
			int			m_Type;
			AString		m_strName;
		};
	
	};
};
#endif // COMMONNETFILE_HEAD_FILE