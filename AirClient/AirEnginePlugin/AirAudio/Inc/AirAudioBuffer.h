#ifndef AUDIOBUFFER_HEAD_FILE
#define AUDIOBUFFER_HEAD_FILE

#include "AirAudioHeader.h"
namespace Air{
	
	namespace Client{
	
		namespace	Audio{
			/**	\brief	����������
			*
			*	����������
			*
			***/
			class	Buffer	:
				public	IProduct{
			public:
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
				SInt	GetFormat(){
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
				U8*		m_pBuffer;			///<	��Ƶ����
				UInt	m_uiSize;			///<	��Ƶ�����С
				SInt	m_uiFormat;			///<	��Ƶ��ʽ
				SInt	m_uiFreqBuffer;		///<	����
			};
	
			/**	\brief	��Ƶ���幤��
			*
			*	��Ƶ���幤��
			*
			***/
			class	BufferFactory	:
				public	IFactory{
			public:
				BufferFactory();
	
				/**	\brief	������Ƶ����
				*   
				*	@remarks 	������Ƶ����
				*	@see		BufferFactory
				*	@return   	IProduct*
				*	@param		AString strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
			};
		}
	
	};
};
#endif // AUDIOBUFFER_HEAD_FILE