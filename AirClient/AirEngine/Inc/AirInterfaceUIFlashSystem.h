#ifndef INTERFACEUIFLASHSYSTEM_HEAD_FILE
#define INTERFACEUIFLASHSYSTEM_HEAD_FILE

#include "AirInterfaceUIFlashLayout.h"
namespace Air{
	
	
	namespace Engine{
	
		namespace	UI{
			namespace	Flash{
				class	ENGINE_EXPORT	ISystem	:
					public	Common::ISystem{
				public:
					ISystem(CAString&	strType);
	
					/**	\brief	��ʼ��
					*   
					*	@remarks 	
					*	@see		System
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Initialization();
					/**	\brief	�ͷ�
					*   
					*	@remarks 	�ͷ�
					*	@see		System
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Release();
					/**	\brief	����UI
					*   
					*	@remarks 	����UI ���ڴ��������Ϣ������Ϣ �Ա㴦���Ƿ��д��ڱ�����
					*	@see		ISystem
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	Updata();
	
					/**	\brief	��Ⱦ
					*   
					*	@remarks 	��Ⱦ
					*	@see		ISystem
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	Render();
					/**	\brief	��Ⱦ����Ŀ�굽����
					*   
					*	@remarks 	��Ⱦ����Ŀ�굽����
					*	@see		Renderer
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RenderTarget();
					/**	\brief	Windows��Ϣ�ص�
					*   
					*	@remarks 	Windows��Ϣ�ص�
					*	@see		IEngine
					*	@return   	long
					*	@param		HWND hWnd
					*	@param		UINT uMsg
					*	@param		WPARAM wParam
					*	@param		LPARAM lParam
					*	@param		bool * pbNoFurtherProcessing
					*	@param		void * pUserContext
					*	@note
					*
					**/
					virtual long	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,void* pUserContext );
	
					/**	\brief	�豸���ûص�
					*   
					*	@remarks 	�豸���ûص�
					*	@see		IISystem
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	OnResetDevice();
				};
			}
		}
	
	};
};
#endif // INTERFACEUIFLASHSYSTEM_HEAD_FILE