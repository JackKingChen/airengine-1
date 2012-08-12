#ifndef ENGINESHARESHADERLIGHTPARAM_HEAD_FILE
#define ENGINESHARESHADERLIGHTPARAM_HEAD_FILE

namespace Client{

#ifndef		LIGHT_COUNT
#define		LIGHT_COUNT	50
#endif

	/**	\brief	�ƹ����
	*
	*	�ƹ����
	*
	***/
	class	LightParam{
	public:
		LightParam(){
			m_AmibentColor	=	Float4(0.5,0.5,0.5,1);
			m_LightPosition.resize(LIGHT_COUNT);
			m_LightDiffuse.resize(LIGHT_COUNT);

			for(UInt i=0;i<LIGHT_COUNT;i++){
				m_pShadowTexture[i]		=	NULL;
				m_pShadowTextureCube[i]	=	NULL;
				m_LightPosition[i]		=	Float4(100,100,100,100);
				m_LightDiffuse[i]		=	Float4(0,0,0,0);

			}
		};

		//������
		Float4						m_AmibentColor;
		//�ƹ�
		VectorArray					m_LightPosition;
		VectorArray					m_LightDiffuse;

		Float44						m_matShadow[LIGHT_COUNT];
		//��Ӱ����
		Render::ITexture*			m_pShadowTexture[LIGHT_COUNT];		///<	ƽ�й�;۹�Ƶ�
		Render::ITexture*			m_pShadowTextureCube[LIGHT_COUNT];	///<	���Դ����Ӱ���
	};

};
#endif // ENGINESHARESHADERLIGHTPARAM_HEAD_FILE