#ifndef AUDIOBUFFER_HEAD_FILE
#define AUDIOBUFFER_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			enum enumFormat{
				enF_MONO8		=	0x1100,
				enF_MONO16		=	0x1101,
				enF_STEREO8		=	0x1102,
				enF_STEREO16	=	0x1103
			};
			/**	\brief	����������
			*
			*	����������
			*
			***/
			class	ENGINE_EXPORT	Buffer	:
				public	IProduct{
			public:
				static AString	ProductTypeName;
				Buffer(CAString&	strName);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Buffer
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Buffer
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	��ȡ������
				*   
				*	@remarks 	��ȡ������
				*	@see		Buffer
				*	@return   	U8*
				*	@note
				*
				**/
				U8*		GetBuffer(){
					return	m_pBuffer;
				};
				/**	\brief	��ȡ��������С
				*   
				*	@remarks 	��ȡ��������С
				*	@see		Buffer
				*	@return   	UInt
				*	@note
				*
				**/
				UInt	GetBufferSize(){
					return	m_uiSize;
				};
	
				/**	\brief	��ȡ��Ƶ��ʽ
				*   
				*	@remarks 	��ȡ��Ƶ��ʽ
				*	@see		Buffer
				*	@return   	SInt
				*	@note
				*
				**/
				enumFormat	GetFormat(){
					return	m_uiFormat;
				};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		Buffer
				*	@return   	SInt
				*	@note
				*
				**/
				SInt	GetFreqBuffer(){
					return	m_uiFreqBuffer;
				}
	
			protected:
				/**	\brief	����WAV��ʽ�ļ�
				*   
				*	@remarks 	����WAV��ʽ�ļ�
				*	@see		Buffer
				*	@return   	U1
				*	@param		Data * pData
				*	@note
				*
				**/
				U1		LoadWAVFromMemory(Data*	pData);
			protected:
				U8*			m_pBuffer;			///<	��Ƶ����
				UInt		m_uiSize;			///<	��Ƶ�����С
				enumFormat	m_uiFormat;			///<	��Ƶ��ʽ
				SInt		m_uiFreqBuffer;		///<	����
			};
		}
	
	};
};
#endif // AUDIOBUFFER_HEAD_FILE