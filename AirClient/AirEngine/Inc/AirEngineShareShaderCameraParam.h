#ifndef ENGINESHARESHADERCAMERAPARAM_HEAD_FILE
#define ENGINESHARESHADERCAMERAPARAM_HEAD_FILE

namespace Client{

	class	CameraParam{
	public:
		CameraParam(){
			m_bLeftHand			=	true;
			m_bUpDirY			=	true;


			m_matView			=	Float44::IDENTITY;
			m_matProj			=	Float44::IDENTITY;
			m_matViewProj		=	Float44::IDENTITY;
			m_matViewProjI		=	Float44::IDENTITY;

			//������Ƕ�
			m_fFOV				=	3.14159265f/4.0f;
			//�ݺ��
			m_fASpect			=	(Real)m_iScreenWidth/m_iScreenHeight;
			//����ü����� ��Ҫ�趨��̫С ����ᵼ�� ģ����ģ�� ������ ����������
			//һ���趨1���ҾͿ����� 0.01��ʱ��Ƚ���
			m_fNearCullDistance	=	1.0f;
			m_fFarCullDistance	=	5000.0f;

			m_vCurrentLookAt	=	Float3::ZERO;
			m_vCurrentPosition	=	Float3(300,10,10);
			if(m_bUpDirY)
				m_vCurrentUpDirection	=	Float3::UNIT_Y;
			else
				m_vCurrentUpDirection	=	Float3::UNIT_Z;
			m_vCurrentRightDirection	=	Float3::UNIT_X;

			m_iScreenWidth				=	1024;
			m_iScreenHeight				=	768;
		};
		//�����λ�ó���
		Float3				m_vCurrentPosition;
		Float3				m_vCurrentLookAt;
		Float3				m_vCurrentUpDirection;
		Float3				m_vCurrentDirection;
		Float3				m_vCurrentRightDirection;
		//����
		Float44				m_matView;
		Float44				m_matProj;
		Float44				m_matViewProj;
		Float44				m_matViewProjI;

		//��Ļ
		Real				m_iScreenWidth;
		Real				m_iScreenHeight;

		//�����
		Real				m_fFOV;
		Real				m_fASpect;
		Real				m_fNearCullDistance;
		Real				m_fFarCullDistance;

		U1					m_bLeftHand;			///<	�Ƿ�ʹ����������ϵ
		U1					m_bUpDirY;				///<	������

		PlaneList			m_lstCullPlane;			///<	�ü����б�
	};

};
#endif // ENGINESHARESHADERCAMERAPARAM_HEAD_FILE