#ifndef INTERFACEAUDIOSOUND_HEAD_FILE
#define INTERFACEAUDIOSOUND_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			/**	\brief	����
			*
			*	����
			*
			***/
			class	IProperty{
			public:
				IProperty(){
					m_pParent	=	NULL;
					m_fVolume	=	1.0f;
					m_fPitch	=	1.0f;
					m_bIsChange	=	false;
				};
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		IProperty
				*	@return   	void
				*	@param		Real f
				*	@note
				*
				**/
				virtual	void	SetVolume(Real	f){
					m_bIsChange	=	true;
					m_fVolume	=	f;
				};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		IProperty
				*	@return   	Real
				*	@note
				*
				**/
				virtual	Real	GetVolume(){
					if(m_pParent!=NULL){
						return	m_pParent->GetVolume()*m_fVolume;
					}else{
						return	m_fVolume;
					}
				};
	
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		IProperty
				*	@return   	void
				*	@param		Real f
				*	@note
				*
				**/
				virtual	void	SetPitch(Real	f){
					m_bIsChange	=	true;
					m_fPitch	=	f;
				};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		IProperty
				*	@return   	Real
				*	@note
				*
				**/
				virtual	Real	GetPitch(){
					if(m_pParent!=NULL){
						return	m_pParent->GetPitch()*m_fPitch;
					}else{
						return	m_fPitch;
					}
				};
				/**	\brief	�ж��Ƿ񱻸ı�
				*   
				*	@remarks 	�ж��Ƿ񱻸ı�
				*	@see		IProperty
				*	@return   	U1
				*	@note
				*
				**/
				inline	U1		HasChange(){return	m_bIsChange;};
			protected:
				IProperty*	m_pParent;		///<	���ڵ�����
				Real		m_fVolume;		///<	����
				Real		m_fPitch;		///<	����
				U1			m_bIsChange;	///<	�Ƿ��Ѿ��ı�
			};
			/**	\brief	����
			*
			*	����
			*
			***/
			class	ISound	:
				public	TProduct<ISound>,
				public	IProperty,
				public	MovableObject
				{
			public:
				/**	\brief	��������
				*
				*	��������
				*
				***/
				enum	enumType{
					enStatic,		///<	��̬	���米������
					enDynamic,		///<	��̬	���糡����������ƶ�������
					enDirection,	///<	��������
					enMax
				};
				enum	enumState{
					enInit		=	0x1011,
					enPlaying	=	0x1012,
					enPause		=	0x1013,
					enStop		=	0x1014,
					enUnknown
				};
				/**	\brief	����������Ϣ
				*
				*	����������Ϣ
				*
				***/
				struct	Info{
					Info(){
						type		=	enStatic;
						strName		=	"..\\Data\\Audio\\1.wav";
						vPosition	=	Float3(0,0,0);
						fPitch		=	1.0f;
						fVolume		=	1.0f;
						iNumRepeat	=	1;
						fInner		=	360;
						fOuter		=	360;
						fDistance	=	5000.0f;
						pParentNode	=	NULL;
					};
					void	SetDynamic(AString	strSoundName,Float3	v	=	Float3(0,0,0),UInt	iRepeat	=	1){
						type		=	enDynamic;
						strName		=	strSoundName;
						vPosition	=	v;
						iNumRepeat	=	iRepeat;
						fInner		=	360;
						fOuter		=	360;
						fDistance	=	1000.0f;
						pParentNode	=	NULL;
					};
					void	SetDirection(AString	strSoundName,UInt	fInnerAngle,UInt	fOuterAngle,Float3	v	=	Float3(0,0,0),UInt	iRepeat	=	1){
						type		=	enDirection;
						strName		=	strSoundName;
						fInner		=	fInnerAngle;
						fOuter		=	fOuterAngle;
						vPosition	=	v;
						iNumRepeat	=	iRepeat;
						fDistance	=	2000.0f;
						pParentNode	=	NULL;
					};
					enumType	type;			///<	����
					AString		strName;		///<	�����ļ���
					Float3		vPosition;		///<	��ʼλ��
					Real		fVolume;		///<	��ʼ����
					Real		fPitch;			///<	��ʼ�����ٶ�
					SInt		iNumRepeat;		///<	�ظ�����
					UInt		fInner;			///<	��Ȧ
					UInt		fOuter;			///<	��Ȧ
					Real		fDistance;		///<	������Χ
					SceneNode*	pParentNode;	///<	Ҫ�󶨵��Ľڵ�
				};
			public:
				ISound(CAString&	strName,Info*	pInfo):TProduct(strName){

				};
				/**	\brief	��ȡ��������
				*   
				*	@remarks 	��ȡ��������
				*	@see		ISound
				*	@return   	Client::Audio::ISound::enumType
				*	@note
				*
				**/
				virtual	enumType	GetType()						=	NULL;
				/**	\brief	�����ļ�����Ҫ��Ⱦ
				*   
				*	@remarks 	�����ļ�����Ҫ��Ⱦ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Render(){};
	
				/**	\brief	��ȡ��ǰ״̬
				*   
				*	@remarks 	��ȡ��ǰ״̬
				*	@see		ISound
				*	@return   	Client::Audio::ISound::enumState
				*	@note
				*
				**/
				virtual	enumState	GetState()=	NULL;
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Play()=	NULL;
				/**	\brief	��ͣ
				*   
				*	@remarks 	��ͣ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Pause()=	NULL;
				/**	\brief	ֹͣ
				*   
				*	@remarks 	ֹͣ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Stop()=	NULL;
				/**	\brief	���¿�ʼ����
				*   
				*	@remarks 	���¿�ʼ����
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		RePlay()=	NULL;
	
				/**	\brief	��ȡʣ�����
				*   
				*	@remarks 	��ȡʣ�����
				*	@see		ISound
				*	@return   	UInt
				*	@note
				*
				**/
				virtual	SInt		GetRepeatCount()	=	NULL;
	
				/**	\brief	��������
				*   
				*	@remarks 	����λ����Ϣ
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		UpdateSound()		=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEAUDIOSOUND_HEAD_FILE