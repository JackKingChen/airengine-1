#ifndef AUIDOSOUND_HEAD_FILE
#define AUIDOSOUND_HEAD_FILE

#include "AirAudioHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			class	Buffer;
			/**	\brief	����
			*
			*	����
			*
			***/
			class	Sound	:
				public	ISound{
			public:
				Sound(CAString&	strName,Info*	pInfo);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Sound
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Sound
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		IProperty
				*	@return   	void
				*	@param		Real f
				*	@note
				*
				**/
				virtual	void	SetVolume(Real	f);
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		IProperty
				*	@return   	void
				*	@param		Real f
				*	@note
				*
				**/
				virtual	void	SetPitch(Real	f);
				/**	\brief	��ȡ��������
				*   
				*	@remarks 	��ȡ��������
				*	@see		ISound
				*	@return   	Client::Audio::ISound::enumType
				*	@note
				*
				**/
				virtual	enumType	GetType();
				/**	\brief	�����ļ�����Ҫ��Ⱦ
				*   
				*	@remarks 	�����ļ�����Ҫ��Ⱦ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Render();
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Sound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Updata();
				/**	\brief	��ȡ��ǰ״̬
				*   
				*	@remarks 	��ȡ��ǰ״̬
				*	@see		ISound
				*	@return   	Client::Audio::ISound::enumState
				*	@note
				*
				**/
				virtual	enumState	GetState();
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Play();
				/**	\brief	��ͣ
				*   
				*	@remarks 	��ͣ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Pause();
				/**	\brief	ֹͣ
				*   
				*	@remarks 	ֹͣ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Stop();
				/**	\brief	���¿�ʼ����
				*   
				*	@remarks 	���¿�ʼ����
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		RePlay();
				/**	\brief	��ȡʣ�����
				*   
				*	@remarks 	��ȡʣ�����
				*	@see		ISound
				*	@return   	UInt
				*	@note
				*
				**/
				virtual	SInt		GetRepeatCount();
				/**	\brief	��������
				*   
				*	@remarks 	����λ����Ϣ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		UpdataSound();
			protected:
				UInt		m_uiSource;
				UInt		m_uiSampleSet;
				Info		m_Info;
				Buffer*		m_pBuffer;
				Float3		m_vLastPosition;
			};	
	
			class	SoundFactory	:
				public	IFactory{
			public:
				SoundFactory();
	
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		SoundFactory
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
#endif // AUIDOSOUND_HEAD_FILE