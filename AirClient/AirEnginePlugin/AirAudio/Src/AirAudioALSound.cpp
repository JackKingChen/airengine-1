#include "AirAudioALSound.h"
#include "AirAudioOggBuffer.h"

namespace Air{
	
	namespace	Engine{
		namespace	Audio{
	
	
			ALSound::ALSound( CAString& strName,Info* pInfo ):Sound(strName,pInfo){
				m_Info			=	*pInfo;
				m_pBuffer		=	NULL;
				m_uiSource		=	0;
				m_uiSampleSet	=	0;
				m_vLastPosition	=	m_Info.vPosition;


			}
	
			U1 ALSound::Create(){
				if(m_Info.strName.empty())
					return false;
				//解析后缀名
				AString	strPostfix;
				GlobalSetting::ParsePath(m_Info.strName,&strPostfix);
				AString	strType	=	"Buffer";
				//判断后缀名
	// 			if(strPostfix	==	"Ogg"	||
	// 				strPostfix	==	"OGG"	||
	// 				strPostfix	==	"ogg"){
	// 					strType	=	"OggBuffer";
	// 			}
				m_pBuffer	=	AudioSystem::GetSingleton()->CreateProduct<Buffer>(m_Info.strName,strType);
				if(m_pBuffer==NULL)
					return false;
				//生成一个源（用于播放）
				alGenSources(1, &m_uiSource);
				//生成一个播放的缓冲
				alGenBuffers(1, &m_uiSampleSet);
				//指定播放的资源
				alBufferData(m_uiSampleSet, m_pBuffer->GetFormat(), m_pBuffer->GetBuffer(), m_pBuffer->GetBufferSize(), m_pBuffer->GetFreqBuffer());
				//把缓冲绑定到源
				alSourcei(m_uiSource, AL_BUFFER, m_uiSampleSet);
	
				switch(m_Info.type){
					case	enStatic:{
						alSourcei(m_uiSource,AL_SOURCE_RELATIVE,AL_TRUE);
	
					break;}
					case	enDynamic:{
						Float3	vPos	=	m_Info.vPosition;
						if(m_Info.pParentNode!=NULL){
							m_Info.pParentNode->attachObject(this);
							vPos=m_Info.pParentNode->GetGlobalPosition();
	
						}
						
						alSource3f(m_uiSource,AL_POSITION,vPos.x,vPos.y,vPos.z);
						alSource3f(m_uiSource,AL_VELOCITY,0,0,0);
						alSourcef(m_uiSource,AL_MAX_DISTANCE,m_Info.fDistance);
	
					break;}
					case	enDirection:{
						Float3	vPos	=	m_Info.vPosition;
						alSource3f(m_uiSource,AL_POSITION,vPos.x,vPos.y,vPos.z);
						alSource3f(m_uiSource,AL_VELOCITY,0,0,0);
						alSourcei(m_uiSource,AL_CONE_INNER_ANGLE,m_Info.fInner);
						alSourcei(m_uiSource,AL_CONE_OUTER_ANGLE,m_Info.fOuter);
						alSourcef(m_uiSource,AL_MAX_DISTANCE,m_Info.fDistance);
						if(m_Info.pParentNode!=NULL)
							m_Info.pParentNode->attachObject(this);
					break;}
					default:{
					
					}
				}
				SetVolume(m_Info.fVolume);
				SetPitch(m_Info.fPitch);
	
				//alSoure
	
				m_pObject	=	&m_uiSource;
				
	
				return true;
			}
	
			U1 ALSound::Destroy(){
				//停止声音
				Stop();
				//摧毁声音
				alDeleteSources(1,&m_uiSource);
				alDeleteBuffers(1,&m_uiSampleSet);
				
				m_uiSource		=	0;
				m_uiSampleSet	=	0;
	
				if(m_pBuffer!=NULL){
					m_pBuffer->ReleaseRef();
				}
				m_pBuffer		=	NULL;
				m_pObject		=	NULL;
				return true;
			}
	
			void ALSound::SetVolume( Real f ){
				m_fVolume		=	f;
				if(m_fVolume<0.0f)
					m_fVolume		=	0.0f;
	
				Real	fVolume	=	m_fVolume;
				if(m_pParent!=NULL)
					fVolume		=	m_fVolume	*	m_pParent->GetVolume();
				//设置音量
				alSourcef(m_uiSource,AL_GAIN,fVolume);
			}
	
			void ALSound::SetPitch( Real f ){
				m_fPitch	=	f;
				m_fPitch		=	f;
				if(m_fPitch<0.0f)
					m_fPitch		=	0.0f;
	
				Real	fPitch	=	m_fPitch;
				if(m_pParent!=NULL)
					fPitch		=	m_fPitch	*	m_pParent->GetPitch();
				//设置音调高低
				alSourcef(m_uiSource,AL_PITCH,fPitch);
			}
	


	
			void ALSound::Update(){
				UpdateSound();
			}
	
			Sound::enumState ALSound::GetState(){
				SInt	iState	=	0;
				alGetSourcei( m_uiSource, AL_SOURCE_STATE, &iState);
				return	(enumState)iState;
			}
	
			void ALSound::Play(){
				if(GetState() == AL_PLAYING){
					Stop();
				}
				alSourcePlay(m_uiSource);
				//大于9999表面是无限播放
				if(m_Info.iNumRepeat	>	999)
					return;
				//播放一次就减少次数  当这个数值小于0  则会被摧毁
				m_Info.iNumRepeat--;
		
	// 			AChar	str[256];
	// 			sprintf_s(str,256,"Play	Sound	%d	\n",m_Info.iNumRepeat);
	// 			OutputDebugStringA(str);
			}
	
			void ALSound::Pause(){
				if(GetState() == AL_PAUSED){
					Play();
					return;
				}
				alSourcePause(m_uiSource);
			}
	
			void ALSound::Stop(){
				if(GetState() == AL_STOPPED)
					return;
				alSourceStop(m_uiSource);
			}
	
			void ALSound::RePlay(){
				alSourceRewind(m_uiSource);
	
				//大于9999表面是无限播放
				if(m_Info.iNumRepeat	>	999)
					return;
				//播放一次就减少次数  当这个数值小于0  则会被摧毁
				m_Info.iNumRepeat--;
			}
	
			void ALSound::UpdateSound(){
	
				if(	m_pParentNode	!=	NULL	&&
					m_Info.type		==	enDynamic)
				{
	
					Float3	vPos	=	m_pParentNode->GetGlobalPosition();
					static	Real*	pTimeDelta	=	&GetGlobalSetting().m_ShaderParam.m_fTimeDelta;
					Float3	vVelocity	=	Float3(0,0,0);
 					if(*pTimeDelta!=0.0f)
 						vVelocity	=	(vPos	-	m_vLastPosition)/(*pTimeDelta);
	
					alSource3f(m_uiSource,AL_POSITION,vPos.x,vPos.y,vPos.z);
					alSource3f(m_uiSource,AL_VELOCITY,vVelocity.x,vVelocity.y,vVelocity.z);
					m_vLastPosition	=	vPos;
				}
	
				if(GetState()	==	AL_STOPPED){
					if(m_Info.iNumRepeat>=0)
						Play();
					else{
						if(m_pParentNode!=NULL){
							GetParentSceneNode()->detachObject(this);
						}
						ReleaseRef();
						return;
					}
				}
	
			}
		}
	}
};