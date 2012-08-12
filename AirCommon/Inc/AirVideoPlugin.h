#ifndef VIDEOPLUGIN_HEAD_FILE
#define VIDEOPLUGIN_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

interface	IMediaEventEx;
interface	IMediaPosition;
interface	IMediaControl;
interface	IGraphBuilder;
interface	IVideoWindow;
namespace Air{
	
	namespace	Common{
	
		/**	\brief	��ƵƬͷ���Ų��
		*
		*	��ƵƬͷ����
		*
		***/
		class COMMON_EXPORT CVideoPlugin{
		public:
			CVideoPlugin();
			virtual ~CVideoPlugin();
			void	LoadWmvA(char* tcFileName,HWND hWnd);
			void	LoadWmv(wchar_t* tcFileName);
			void	LoadWmvA(char* tcFileName);
			void	LoadAvi(TCHAR* tcFileName);
			void	Play();
			void	Pause(bool bPause = true);
			void	Stop();
			void	SetSpeed(double fSpeed);
			bool	IsPlaying();
			double	GetLength();
			double	GetCurrentTime();
			double	GetSpeed();
	
		private:
			WString				m_sFileName;
			double				m_fSpeed;
			double				m_fLength;
			double				m_fCurrentTime;
			bool				m_bInit;
			bool				m_bIsFullScreen;
			HWND				m_hWnd;				
	
		private:
			IMediaEventEx*		m_pMediaEventEx;	//���Դ�directshow�����¼���Ϣ
			IMediaPosition*		m_pMediaPosition;	//�������ȡ��/����ý�岥�ŵ�λ�õȡ�
			IMediaControl*		m_pMediaControl;    //������Filter Graph Manager����Command
			IGraphBuilder*		m_pGraphBuilder;    // ���ڴ���Filter Graph�Ľӿ�
			IVideoWindow*		m_pVideoWindow;		// ����ָ��
		};
	}
};

#endif