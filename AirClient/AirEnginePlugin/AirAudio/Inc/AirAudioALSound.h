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
			class	ALSound	:
				public	Sound{
			public:
				ALSound(CAString&	strName,Info*	pInfo);
	
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

				virtual	enumState	GetState();
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Sound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Update();

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

				/**	\brief	��������
				*   
				*	@remarks 	����λ����Ϣ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		UpdateSound();
			protected:
				UInt		m_uiSource;
				UInt		m_uiSampleSet;
				Buffer*		m_pBuffer;
				Float3		m_vLastPosition;
			};	
		}
	
	};
};
#endif // AUIDOSOUND_HEAD_FILE