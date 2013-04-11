#ifndef GLOBALSETTING_HEAD_FILE
#define GLOBALSETTING_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineShaderShareParam.h"
namespace Air{
	
	namespace	Common{
		class	Log;
	}
	
	namespace Engine{
		
		namespace	Render{
			class	System;
			class	ITexture;
			class	IMaterial;
		};
		namespace	Physics{
			class	ISystem;
		}
		namespace	Script{
			class	ISystem;
		}
		namespace	UI{
			class	ISystem;
		}
		namespace	Audio{
			class	ISystem;
		}
		namespace	Resource{
			class	ISystem;
		}
		namespace	Net{
			class	ISystem;
		}
		namespace	Particle{
			class	ISystem;
		}
		namespace	Input{
			class	ISystem;
		}
	
		class Camera;
		class	Font;
		/**	\brief	����������Ҫ�Ĳ���
		*
		*	����������Ҫ�Ĳ���
		*
		***/
		struct	EngineParam{
			EngineParam(){
				hParentWnd	=	NULL;
				hWnd		=	NULL;
				InputWnd	=	NULL;
				ZeroMemory(strPlugin,128);
				ZeroMemory(strGamePlugin,128);
				ZeroMemory(strMedia,128);
				ZeroMemory(strCustomMedia,128);
				ZeroMemory(strDisplay,128);
			};
			HWND	hParentWnd;
			HWND	hWnd;
			HWND	InputWnd;
			AChar	strPlugin[128];
			AChar	strGamePlugin[128];
			AChar	strMedia[128];
			AChar	strCustomMedia[128];
			AChar	strDisplay[128];
		};
		/**	\brief	��ʾ����
		*
		*	��ʾ����
		*
		***/
		struct	DisplayParam{
			DisplayParam(){
				iWidth			=	1024;
				iHeight			=	700;
				bWindow			=	true;
				iMSAAType		=	0;
				iMSAAQuality	=	0;
			};
			U32		iWidth;
			U32		iHeight;
			U1		bWindow;
			U32		iMSAAType;
			U32		iMSAAQuality;
		};
	
	#ifndef MAX_LIGHT
	#define MAX_LIGHT	9
	#endif
		/**	\brief	ȫ��������
		*
		*	ȫ��������
		*
		***/
		class ENGINE_EXPORT	GlobalSetting{
		public:
			GlobalSetting();
			virtual	~GlobalSetting();
	
			/**	\brief	��·���л�ȡ��׺��
			*   
			*	@remarks 	��·���л�ȡ��׺��
			*	@see		GlobalSetting
			*	@return   	AString
			*	@param		AString strName
			*	@note
			*
			**/
			static	U1	ParsePath(AString	strName,AString*	pStrPostfix,AString*	pStrFileName	=	NULL,AString*	pStrPath	=	NULL);	
	
			/**	\brief	��ȡ�������
			*   
			*	@remarks 	��ȡ�������
			*	@see		GlobalSetting
			*	@return   	Client::Ray
			*	@param		SInt x
			*	@param		SInt y
			*	@note
			*
			**/
			Ray		GetCursorPostionRay(SInt x	=	-1,SInt y = -1);
	
			/**	\brief	��ȡ�������ַ���
			*   
			*	@remarks 	��ȡ�������ַ���
			*	@see		GlobalSetting
			*	@return   	AString
			*	@param		U8 key
			*	@note
			*
			**/
			AString	GetKeyString(U8	key);
			/**	\brief	���ַ���ת��Ϊ����
			*   
			*	@remarks 	���ַ���ת��Ϊ����
			*	@see		GlobalSetting
			*	@return   	U8
			*	@param		AString & str
			*	@note
			*
			**/
			U8		GetKey(AString&	str);
	

	
			//��Ⱦϵͳ

			Physics::ISystem*			m_pPhysicsSystem;	///<	����ϵͳָ��
			Input::ISystem*				m_pInputSystem;		///<	����ϵͳָ��
			Script::ISystem*			m_pScriptSystem;	///<	�ű�ϵͳָ��
			UI::ISystem*				m_pUISystem;		///<	����ϵͳָ��

			Net::ISystem*				m_pNetSystem;		///<	����ϵͳָ��

			Particle::ISystem*			m_pParticleSystem;	///<	����ϵͳָ��
	
	
	
	
	
	
	
			UInt						m_uiOrginTechnique;		///<	ԭʼ����
			UInt						m_uiCurrentTechnique;	///<	��ǰ����
	
	
	
			EngineParam					m_EngineParam;			///<	�������
			DisplayParam				m_DisplayParam;			///<	��ʾ����
			ShaderShareParam			m_ShaderParam;			///<	��ɫ���Թ������
	
			Font*						m_pDefaultFont;
	
			U1							m_bQuit;
			/**	\brief	������ά����
			*   
			*	@remarks 	������ά����
			*	@see		GlobalSetting
			*	@return   	Client::Float3
			*	@param		AString & strValue
			*	@note
			*
			**/
			static	inline	Float3			ParseFloat3(AString&	strValue){
				_XMFLOAT4 v	=	_XMFLOAT4(0,0,0,0);
				if(!strValue.empty())
					sscanf_s(strValue.c_str(),"%f,%f,%f",&v.x,&v.y,&v.z);
				return *(Float3*)&v;
			};
			/**	\brief	������ά����
			*   
			*	@remarks 	������ά����
			*	@see		GlobalSetting
			*	@return   	Client::Float4
			*	@param		AString & strValue
			*	@note
			*
			**/
			static	inline	Float4			ParseFloat4(AString&	strValue){
				Float4 v	=	Float4(0,0,0,0);
				if(!strValue.empty())
					sscanf_s(strValue.c_str(),"%f,%f,%f,%f",&v.x,&v.y,&v.z,&v.w);
				return v;
			};
	
			/**	\brief	������Ԫ��
			*   
			*	@remarks 	������Ԫ��
			*	@see		GlobalSetting
			*	@return   	Client::Float4
			*	@param		AString & strValue
			*	@note
			*
			**/
			static	inline	Float4		ParseQuat(AString&	strValue){
				_XMFLOAT4 v	=	_XMFLOAT4(0,0,0,1);
				if(!strValue.empty())
					sscanf_s(strValue.c_str(),"%f,%f,%f,%f",&v.x,&v.y,&v.z,&v.w);
				return *(Float4*)&v;
			};
	
			/**	\brief	���������߼��
			*   
			*	@remarks 	���������߼��
			*	@see		GlobalSetting
			*	@return   	bool
			*	@param		Ray & ray
			*	@param		Float3 & v0
			*	@param		Float3 & v1
			*	@param		Float3 & v2
			*	@param		Real * t
			*	@param		Real * u
			*	@param		Real * v
			*	@note
			*
			**/
			bool IntersectTriangle( Ray&		ray,
									Float3&	v0, 
									Float3&	v1, 
									Float3&	v2,
									Real*		t, 
									Real*		u/*	=	NULL*/, 
									Real*		v/*	=	NULL*/ );
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		GlobalSetting
			*	@return   	void
			*	@param		UInt vertexCount
			*	@param		Float3 * vertex
			*	@param		Float3 * normal
			*	@param		Vector2 * texcoord
			*	@param		UInt triangleCount
			*	@param		UInt * triangle
			*	@param		Float4 * tangent
			*	@note
			*
			**/
			void CalculateTangentArray(	UInt		vertexCount, 
										Float3*	vertex,
										Float3*	normal,
										Float2*	texcoord,
										UInt		triangleCount,
										UInt*		triangle,
										Float3*	tangent);
		};
	
		/**	\brief	��ȡȫ������
		*   
		*	@remarks 	��ȡȫ������
		*	@see		
		*	@return   	GlobalSetting&
		*	@note
		*
		**/
		ENGINE_EXPORT GlobalSetting&	GetGlobalSetting();
	};
};
#endif // GLOBALSETTING_HEAD_FILE