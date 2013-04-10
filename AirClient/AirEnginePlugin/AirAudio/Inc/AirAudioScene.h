#ifndef AUDIOSCENE_HEAD_FILE
#define AUDIOSCENE_HEAD_FILE

#include "AirAudioHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			class	Scene	:
				public	IScene{
			public:
				Scene(AString	strName);
	
				/**	\brief	��ʼ��
				*   
				*	@remarks 	��ʼ��
				*	@see		Scene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Initialization();
				/**	\brief	�ͷ�
				*   
				*	@remarks 	�ͷ�
				*	@see		Scene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Release();
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Scene
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Update();
				/**	\brief	���������
				*   
				*	@remarks 	���������
				*	@see		IScene
				*	@return   	void
				*	@param		Camera * pCamera
				*	@note
				*
				**/
				virtual	void	SetCamera(Camera*	pCamera);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Scene
				*	@return   	void
				*	@param		ISound::Info & info
				*	@note
				*
				**/
				virtual	ISound*	Play(ISound::Info*	pInfo);
	
				/**	\brief	ֹͣ��������
				*   
				*	@remarks 	ֹͣ��������
				*	@see		Scene
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	StopAllSound();
				/**	\brief	�ݻ�����
				*   
				*	@remarks 	�ݻ�����
				*	@see		Scene
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	DestroyAllSound();
	
				
	
				typedef		std::list<ISound*>	SoundList;
				typedef		SoundList::iterator	SoundListItr;
	
			protected:
				virtual	void	UpdateListener(Camera*	pCamera);
			protected:
				AString		m_strName;
				Camera*		m_pCamera;
			};
		}
	
	};
};
#endif // AUDIOSCENE_HEAD_FILE