#ifndef INTERFACEAUDIOSCENE_HEAD_FILE
#define INTERFACEAUDIOSCENE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceAudioSound.h"
namespace Air{
	
	namespace Engine{
		class	Camera;
	
		namespace	Audio{
			class	IScene	:
				public	IFactoryManager,
				public	IProperty{
			public:
				/**	\brief	��ʼ��
				*   
				*	@remarks 	��ʼ��
				*	@see		Scene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Initialization()	=	NULL;
				/**	\brief	�ͷ�
				*   
				*	@remarks 	�ͷ�
				*	@see		Scene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Release()	=	NULL;
				/**	\brief	���������
				*   
				*	@remarks 	���������
				*	@see		IScene
				*	@return   	void
				*	@param		Camera * pCamera
				*	@note
				*
				**/
				virtual	void	SetCamera(Camera*	pCamera)	=	NULL;
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Scene
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Updata()	=	NULL;
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Scene
				*	@return   	void
				*	@param		ISound::Info & info
				*	@note
				*
				**/
				virtual	ISound*	Play(ISound::Info*	pInfo)	=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEAUDIOSCENE_HEAD_FILE