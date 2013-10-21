#ifndef COMMONNET_HEAD_FILE
#define COMMONNET_HEAD_FILE

#include "MCommon.h"


#ifndef MAX_NET_BUFF
#define	MAX_NET_BUFF	1024
#endif

#ifndef REAL_NET_BUFF
#define REAL_NET_BUFF	MAX_NET_BUFF-4
#endif
namespace Air{
	
	namespace Common{
	
		/**	\brief	��ʼ������
		*   
		*	@remarks 	��ʼ������
		*	@see		
		*	@return   	U1
		*	@note
		*
		**/
		MCOMMON_EXPORT	U1		InitNet();
		/**	\brief	ж������
		*   
		*	@remarks 	ж������
		*	@see		
		*	@return   	U1
		*	@note
		*
		**/
		MCOMMON_EXPORT	U1		ReleaseNet();
	
		MCOMMON_EXPORT	void	GetLocalIP(AString& strIP);
		//�������ݰ�
		struct	NetPack{
			NetPack(){
				uiSocket	=	0;
				uiSize		=	0;
				pData		=	NULL;
			};
	
			NetPack(U32 sock,U32 size,const void*	p){
				if(sock==0||size==0||p==NULL)
					return;
				uiSocket	=	sock;
				uiSize		=	size+4;
				pData		=	new	S8[uiSize];
				memcpy(pData,&size,4);
				memcpy(&pData[4],p,size);
			};
	
			~NetPack(){
				SAF_DA(pData);
			}
			/**	\brief	���ݰ��Ƿ���Ч
			*   
			*	@remarks 	���ݰ��Ƿ���Ч
			*	@see		SendPack
			*	@return   	U1
			*	@note
			*
			**/
			U1	IsValid(){
				if(	uiSocket	==	NULL	||
					uiSize		==	0		||
					pData		==	NULL)
				{
					return	false;
				}
				return	true;
			};
			U32		uiSocket;
			U32		uiSize;
			S8*		pData;
	
		};
	
		/**	\brief	��·������
		*
		*	��·������
		*
		***/
		class	NetListener{
		public:
			virtual	~NetListener(){};
			/**	\brief	�������
			*   
			*	@remarks 	������ɣ��ͻ������������ӷ������ɹ� ����Ƿ���� �����пͻ������룩
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 socket
			*	@param		AString& strIP
			*	@param		AString& strtPort
			*	@note
			*
			**/
			virtual	U1	OnConnected(U32	socket,CAString&	strIP,CAString&	strPort)	=	NULL;
			/**	\brief	����رջص�
			*   
			*	@remarks 	����رջص�	�����������رջ����쳣�ر�
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@note
			*
			**/
			virtual	U1	OnClose(U32	uiSocket)					=	NULL;
	
			/**	\brief	�����յ���������
			*   
			*	@remarks 	�����յ���������
			*	@see		NetListener
			*	@return   	U1
			*	@param		U32 uiSocket
			*	@param		AChar * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize)	=	NULL;
		};
	
		//��������
		struct	INetData{
			INetData(){
				MainID	=	0;
				SubID	=	0;
			};
			U32		MainID;
			U32		SubID;
		};
	
		/**	\brief	IPת��Ϊ�ַ���
		*   
		*	@remarks 	IPת��Ϊ�ַ���
		*	@see		
		*	@return   	MCOMMON_EXPORT	AString
		*	@param		U32 ip
		*	@note
		*
		**/
		MCOMMON_EXPORT	AString	IP2String(U32	ip);
		/**	\brief	�ַ���ת��ΪIP
		*   
		*	@remarks 	�ַ���ת��ΪIP
		*	@see		
		*	@return   	MCOMMON_EXPORT	U32
		*	@param		AString strIP
		*	@note
		*
		**/
		MCOMMON_EXPORT	U32		String2IP(AString	strIP);
	};
};
#endif // COMMONNET_HEAD_FILE