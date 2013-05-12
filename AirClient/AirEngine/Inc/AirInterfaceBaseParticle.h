#ifndef INTERFACEBASEPARTICLE_HEAD_FILE
#define INTERFACEBASEPARTICLE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Particle{
			/**	\brief	������Ϣ
			*
			*	������Ϣ
			*
			***/
			struct	Info{
				Info(AString	str	=	""){
					strConfigName	=	str;
				};
				AString	strConfigName;
			};
			/**	\brief	����������
			*
			*	����������
			*
			***/
			class	ENGINE_EXPORT	IBaseObject	:
				public	Common::IProduct,
				public	MovableObject
				{
			public:
				IBaseObject(CAString&	strName,Info*	pInfo);
	
				virtual	void	SetProperty(AString	strName,SInt&			iParam);
				virtual	void	SetProperty(AString	strName,Real&			fParam);
//				virtual	void	SetProperty(AString	strName,Vector2&		vParam);
//				virtual	void	SetProperty(AString	strName,Float3&		vParam);
				virtual	void	SetProperty(AString	strName,Float4&		vParam);
//				virtual	void	SetProperty(AString	strName,Float4&		qParam);
				virtual	void	SetProperty(AString	strName,Float44&		mParam);
				virtual	void	SetProperty(AString strName,void*			pParam);
	
				
				virtual	void	GetProperty(AString	strName,SInt&			iParam);
				virtual	void	GetProperty(AString	strName,Real&			fParam);
				//virtual	void	GetProperty(AString	strName,Vector2&		vParam);
				//virtual	void	GetProperty(AString	strName,Float3&		vParam);
				virtual	void	GetProperty(AString	strName,Float4&		vParam);
				//virtual	void	GetProperty(AString	strName,Float4&		qParam);
				virtual	void	GetProperty(AString	strName,Float44&		mParam);
				virtual	void*	GetProperty(AString strName);
	
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		IBaseObject
				*	@return   	void
				*	@param		Real fLife
				*	@note
				*
				**/
				virtual	void	SetLife(Real	fLife);
	
				/**	\brief	����Ϊ��������
				*   
				*	@remarks 	����Ϊ��������
				*	@see		IBaseObject
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				virtual	void	SetInfiniteLife(U1	bEnable);
	
				/**	\brief	�ж��Ƿ��Ѿ�����
				*   
				*	@remarks 	�ж��Ƿ��Ѿ�����
				*	@see		IBaseObject
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		IsDead();
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		IBaseObject
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Update(const FrameTime& frameTime);
	
			protected:
				Info			m_Info;				///<	������Ϣ
				U1				m_bIsDead;			///<	�Ƿ��Ѿ�����
				Real			m_fLife;			///<	����
				Real			m_fBornTime;		///<	����ʱ��
				U1				m_bInfiniteLife;	///<	��������
			};
		}
	
	};
};
#endif // INTERFACEBASEPARTICLE_HEAD_FILE