#ifndef INTERFACERESOURCESYSTEM_HEAD_FILE
#define INTERFACERESOURCESYSTEM_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirCommonThread.h"
#include "AirInterfaceResourceStream.h"

namespace Air{
	namespace Client{
	
		namespace	Resource{
			class	IFindFileListener{
			public:
				virtual	void	OnFindFile(CAString&	strName,Data*	pData)=	NULL;
			};
			/**	\brief	��Դ����ϵͳ
			*
			*	��Դ����ϵͳ
			*
			***/
			class	ENGINE_EXPORT	ISystem	:
				public	Common::ISystem,
				public	Common::Thread{
			public:	
				ISystem(CAString&	strType);

				virtual	U1		Initialization();
				virtual	U1		Release();

				virtual	U1		Start();
				virtual	U1		Stop();
				/**	\brief	���Һ�׺���ļ�
				*   
				*	@remarks 	���Һ�׺���ļ�
				*	@see		ISystem
				*	@return   	void
				*	@param		AString strPostfix
				*	@param		IFindFileListener * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener);
	
				/**	\brief	���һ����Դ��
				*   
				*	@remarks 	���һ����Դ��
				*	@see		ISystem
				*	@return   	U1
				*	@param		CAString& strPackageName
				*	@note
				*
				**/
				virtual	U1			AddPackage(CAString&	strPackageName);
				/**	\brief	�ж��ļ��Ƿ����
				*   
				*	@remarks 	�ж��ļ��Ƿ����
				*	@see		ISystem
				*	@return   	Air::U32
				*	@param		CAString & strFileName
				*	@note
				*
				**/
				virtual	U32		Find(CAString&	strFileName);
				virtual	U32		Find(CAString&	strFileName,Data&	outData);
				/**	\brief	������Ҫ��д��ѭ�����ú���
				*   
				*	@remarks 	�߳������ִ�к���
				*	@see		Thread
				*	@return   	bool
				*	@note
				*
				**/
				virtual bool	RepetitionRun();
				/**	\brief	�����̨���ض���
				*   
				*	@remarks 	�����̨���ض���
				*	@see		ISystem
				*	@return   	Air::U1
				*	@param		IStream * pFile
				*	@note
				*
				**/
				virtual	U1		LoadBackground(IStream*	pFile);
				/**	\brief	�ŵ�����վ
				*   
				*	@remarks 	�ŵ�����վ
				*	@see		ISystem
				*	@return   	Air::U1
				*	@param		IProduct * pFile
				*	@note
				*
				**/
				virtual	U1		PushRecycle(IProduct*	p);
				void			SetMaxRecycleSize(U32	uiSize);
				U32				GetMaxRecycleSize();
			protected:
				CriticalSection	m_LoadCS;
				CriticalSection	m_UnLoadCS;
				//Event			m_Event;
				StreamList		m_lstLoad[2];			///<	���ض���
				U32				m_uiLoadIndex;
				ProductList		m_lstUnLoad[2];		///<	ж�ض���	���ջ���
				U32				m_uiUnloadLoadIndex;
				U32				m_uiRecycleSize;	///<	��ǰ����վ��С
				U32				m_uiMaxRecycle;		///<	����վ�������	���ڻ�ݻ�
			};
		}
	
	};
};
#endif // INTERFACERESOURCESYSTEM_HEAD_FILE