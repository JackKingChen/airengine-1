#ifndef GAMETHIRDCONTROL_HEAD_FILE
#define GAMETHIRDCONTROL_HEAD_FILE


#include "AirGameFPSControl.h"
namespace Air{
	

	
		namespace	Game{
			class	ENGINE_EXPORT	ThirdControl	:
				public	FPSControl{
			public:
				static AString	ProductTypeName;
				ThirdControl(CAString&	strName,Info*	pInfo);
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		FPSControl
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		FPSControl
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	����ƶ��¼�
				*   
				*	@remarks 	����ƶ��¼�
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::MouseEvent & arg
				*	@note
				*
				**/
				virtual bool	mouseMoved( const OIS::MouseEvent &arg );
	
				/**	\brief	ÿ֡����
				*   
				*	@remarks 	ÿ֡����
				*	@see		ThirdControl
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Update(const FrameTime& frameTime);
	
				virtual	U1		keyReleased( const OIS::KeyEvent &arg );
	
				Real			m_fMinCameraDis;
				Real			m_fMaxCameraDis;
				Real			m_fCurrentDis;
				Real			m_fTargetDis;
	
				Float3			m_vTargetPosition;	///<	Ŀ��λ��
				Float3			m_vMoveDirection;
				Real			m_fMoveSensitivity;	///<	�ƶ�������
			};
	
		}
	

};
#endif // GAMETHIRDCONTROL_HEAD_FILE