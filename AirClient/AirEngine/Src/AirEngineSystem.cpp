#include "AirEngineSystem.h"

#include "AirGlobalSetting.h"
#include "AirInterfaceUISystem.h"
#include "AirResourceSystem.h"
#include "AirInterfaceNetSystem.h"
#include "AirSlkReader.h"

//工厂头文件
#include "AirCommonLog.h"
#include "AirCommonPlugin.h"
#include "AirEngineCharacterResource.h"
#include "AirEngineCharacterAnimationModel.h"
#include "AirEngineCharacterTextureAnimationModel.h"
#include "AirEngineCharacterTemplate.h"
#include "AirEngineTerrainCommon.h"
#include "AirEngineSubEntity.h"
#include "AirEngineMaterial.h"
#include "AirEngineLight.h"
#include "AirEngineCamera.h"
#include "AirEngineMesh.h"
#include "AirEngineScreenEntity.h"
#include "AirEnginePostComposer.h"
#include "AirEngineParticleEntity.h"
//#include "AirInterfaceShootParticle.h"
#include "AirEngineFont.h"
#include "AirEngineTextInstance.h"
#include "AirStaticMesh.h"
#include "AirMeshEntity.h"
#include "AirManualMeshEntity.h"

#include "AirCommonIniFile.h"
#include "AirInterfaceInputSystem.h"

#include "AirEnginePipeline.h"

#define USE_PROFILE
#include "AirCommonProfile.h"
#include "AirCommonWindow.h"
#include "AirRenderWindow.h"
#include "AirEngineMaterialParse.h"

#include "AirEngineMaterialTemplate.h"
#include "AirEngineMaterial.h"
#include "AirEngineLight.h"

#include "AirGameSystem.h"
#include "AirAudioSystem.h"
#include "AirParticle.h"
#include "AirPhysicsSystem.h"


#include <fstream>

namespace Air{
	
	
	namespace	Engine{
	
		
		const	static	UInt	g_uiNumPlugin		=	16;
		const	static	AString	g_strPluginArray[]	=	{
			"Resource",
			"Render",
			"Physx",
			"Audio",
			"Script",
			"Particle",
			"Input",
			"UI",
			"FlashUI",
			"Net",
			"Game",
			"Custom",
			"Custom1",
			"Custom2",
			"Custom3",
			"Custom4",
			"Custom5"
		};
	
	
		System::System(){
			
			m_strPluginNameArray.resize(g_uiNumPlugin);
			m_pCurrentPipeline		=	NULL;
		}
	
		System::~System(){
			//Release();
			
		}
	
		void System::ExecuteOneFrame(const FrameTime& frameTime){
			//PROFILE_FUNCTION
			//Render::System::GetSingleton()->OnFrameMove(fTime,fElapsedTime,pUserContext);
			//检测是否需要释放缓冲区中的物体
			ReleaseOneObject();
	
			//捕获输入系统
			//Input::Capture();
			if(GetGlobalSetting().m_pInputSystem!=NULL)
				GetGlobalSetting().m_pInputSystem->Capture();

			
	
	
			//渲染界面
			UI::ISystem*	pUISystem		=	GetGlobalSetting().m_pUISystem;
			if(pUISystem!=NULL){
				pUISystem->Update();
			}

			GameSystem::GetSingleton()->Update(frameTime);

			ParticleSystem::GetSingleton()->Update(frameTime);

			GameSystem::GetSingleton()->RenderOneFrame(frameTime);
			
		}
	
		U1 System::Initialization(){
			//ENGINE_LOG_INFO;
			//解析显示参数
			ParseDisplayParam();
			//创建窗口
			CreateWin();


			//AddFactory(new	Common::PluginFactory());
			AddFactory(new	NoParamFactory<DefaultPipeline>());
			//AddFactory(new	FontFactory());
			AddFactory(new	ExtraOptionParamFactory<MaterialTemplate,MaterialTemplateInfo>());
			AddFactory(new	OptionParamFactory<Material>());
			//AddFactory(new	SubEntityFactory());
			
			//AddFactory(new	LightFactory());
			AddFactory(new	ExtraOptionParamFactory<Character::Resource,AString>());
			AddFactory(new  ParamFactory<Character::ModelTemplate>());
			AddFactory(new	ParamFactory<Character::Animation::Model>());
			//AddFactory(new	Character::Animation::TextureModelFactory());
			//AddFactory(new	Terrain::IPageFactory());
			//AddFactory(new	MeshFactory());
			//AddFactory(new	ScreenEntityFactory());
			///AddFactory(new	PostComposerFactory());
			//AddFactory(new	ParticleEntityFactory());
			//AddFactory(new	IParticleFactory());
			//AddFactory(new	ShootParticleFactory());
			//AddFactory(new	TextInstanceFactory());

			AddFactory(new	NoParamFactory<StaticMesh>());
			AddFactory(new	ParamFactory<MeshEntity>());
			AddFactory(new	ParamFactory<ManualMeshEntity>());
			AddFactory(new	NoParamFactory<Camera>());
			AddFactory(new	OptionParamFactory<Light>());

			AddFactory(new NoParamFactory<DefaultPipeline>());

			AddFactory(new NoParamFactory<Scene>());
			
			AddFactory(new ExtraOptionParamFactory<Plugin,void>());

			
	
			//加载所有插件
 			if(!LoadPlugin())
 				return false;
			ResourceSystem::GetSingleton()->Initialization();
			ResourceSystem::GetSingleton()->AddPackage(GetGlobalSetting().m_EngineParam.strMedia);

			PhysicsSystem::GetSingleton()->Initialization();
			RenderSystem::GetSingleton()->Initialization();
			AudioSystem::GetSingleton()->Initialization();
			ParticleSystem::GetSingleton()->Initialization();


			Data	data;
			ResourceSystem::GetSingleton()->Find("..\\Data\\Material\\TestState.State",data);
			MaterialParse::GetSingleton()->CompileState(data.buff,data.size);
			ResourceSystem::GetSingleton()->Find("..\\Data\\Material\\TestMaterial.MaterialTemplate",data);
			MaterialParse::GetSingleton()->CompileMaterialTemplate(data.buff,data.size);
			ResourceSystem::GetSingleton()->Find("..\\Data\\Material\\TestMaterial.Material2",data);
			MaterialParse::GetSingleton()->CompileMaterial(data.buff,data.size);
			data.Clear();
			class MaterialSetCB	:	public	Resource::FindFileCallback
			{
			public:
				virtual	U1	OnFindFile(CAString&	strName,Data*	pData)
				{
					OutputDebugStringA(strName.c_str());
					OutputDebugStringA("\n--Compile Begin!---\n");
					MaterialParse::GetSingleton()->CompileMaterialSet(pData->buff,pData->size);
					OutputDebugStringA("---Compile End!---\n");
					return true;
				};
			}mscb;
			class ParticleCB	:	public	Resource::FindFileCallback
			{
			public:
				virtual	U1	OnFindFile(CAString&	strName,Data*	pData)
				{
					ParticleSystem::GetSingleton()->Compile(*pData);
					return true;
				};
			}pcb;

			ResourceSystem::GetSingleton()->FindWithPostfix(".material",&mscb);
			ResourceSystem::GetSingleton()->FindWithPostfix(".particle",&pcb);

			//初始化所有系统管理器
			InitAllSystemManager();

			//创建Pipeline
			//m_pCurrentScreen=	CreateProduct<Pipeline*>("DefaultPipeline","Pipeline");
	
			//启动系统
			StartAllSystemManager();


			Character::InitModelTemplate("Character.csv");

			GameSystem::GetSingleton()->Initialization();

			//加载Game
			CreateProduct<Plugin>("AirGame.dll");



			return true;
		}
	
		U1 System::Start(){
			//ENGINE_LOG_INFO;

// 					static	ShaderShareParam&	sParam	=	GetGlobalSetting().m_ShaderParam;
// 					static	Real	fLastTime		=	timeGetTime()*0.001f;
// 					//循环逻辑
// 					Real	fCurrentTime	=	timeGetTime()*0.001f;
// 					sParam.m_fEngineTimeDelta		=	fCurrentTime	-	fLastTime;
// 					fLastTime						=	fCurrentTime;
// 					sParam.m_fEngineTotalTime		+=	sParam.m_fEngineTimeDelta	;
// 	
// 	  				static	UInt	uiFrameCount	=	0;
// 	  				uiFrameCount++;
// 	  				static	Real	fTime			=	0;
// 	  				fTime+=	sParam.m_fEngineTimeDelta;
// 	  
// 	  				if(fTime	>	2.0f){
// 	  					Real	fps	=	uiFrameCount/fTime;
// 	  					AChar	str[128];
// 	  					sprintf_s(str,128,"[Engine]FPS=%f\n",fps);
// 	  					OutputDebugStringA(str);
// 	  					uiFrameCount=0;
// 	  					fps	=	0;fTime=0;
// 	  				}
// 					Sleep(16);
			MSG msg;
			::ZeroMemory(&msg, sizeof(MSG));
			while(true){
				if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
				}else{

					//Sleep(10);
					GetTimer().AddFrame();
					ExecuteOneFrame(GetTimer().m_FrameTime);
				}

				if(msg.message	==	WM_QUIT){
					break;
				}
			}


			return true;
	
		}
	
		U1 System::Release(){

			//卸载Game
			DestroyProduct<Plugin>("AirGame.dll");

			GameSystem::GetSingleton()->Release();
			GameSystem::ReleaseSingleton();
			ParticleSystem::GetSingleton()->Release();
			ParticleSystem::ReleaseSingleton();
			MaterialParse::ReleaseSingleton();

			//停止系统
			StopAllSystemManager();

			//释放所有缓冲区中的物体
			ReleaseAllAutoObject();
		
			DestroyAllProduct();

			//释放所有系统管理器
			ReleaseAllSystemManager();

			AudioSystem::GetSingleton()->Release();
			AudioSystem::ReleaseSingleton();
			Render::System::GetSingleton()->Release();
			Render::System::ReleaseSingleton();
			PhysicsSystem::GetSingleton()->Release();
			PhysicsSystem::ReleaseSingleton();
			ResourceSystem::GetSingleton()->Release();
			ResourceSystem::ReleaseSingleton();
			//最后释放所有插件
			UnLoadPlugin();

			Common::Log::ReleaseSingleton();
			return true;
	
		}
	
	
	
		U1 System::LoadPlugin(){
			ENGINE_LOG_INFO
			EngineParam*	pDst	=	&GetGlobalSetting().m_EngineParam;
			AString strPluginName	=	"..\\Data\\Config\\Plugin.ini";//GetGlobalSetting().m_EngineParam.strPlugin;
			File	file(strPluginName);
	
			if(!file.Open())
				return	false;
	
			IniFile	inifile;
			if(!inifile.LoadFileFromMemory(file.GetData()))
				return false;
	
			StringVector*	pLstString	=	inifile.GetStringList("Plugin","Plugins");
			StringVector&	lstString	=	*pLstString;
			UInt	uiSize	=	lstString.size();



			for(UInt i=0;i<uiSize;i++){
				Plugin*	pPlugin	=	new Plugin(lstString[i],0);
				pPlugin->AddRef();
				m_vecPlugin.push_back(pPlugin);
			}

			
	
// 			for(SInt	i=0;i<g_uiNumPlugin;i++){
// 				//获取插件名
// 				m_strPluginNameArray[i]	=	cfgFile.Get("Plugin",(AChar*)g_strPluginArray[i].c_str());
// 				if(!m_strPluginNameArray[i].empty()){
// 					//加载插件	并初始化
// 					Plugin*		p		=	m_pPluginMgr->Create<Plugin*>(m_strPluginNameArray[i],"Plugin");
// 					p->AddRef();
// 					p->SetFactory(m_pPluginMgr);
// 					m_pPluginMgr->Insert(p);
// 					p->Excute(Plugin::enInit);
// 	
// 	// 				Log::GetSingleton()->Write(m_strPluginNameArray[i]);
// 	// 				Log::GetSingleton()->Write("LoadPlugin");
// 				}
// 			}
	
			
			return	true;
		}

		Air::U1 System::LoadPlugin( CAString& strPluginName ){
			//CreateProduct(strPluginName,"Plugin");
			return	true;
		}

		U1 System::UnLoadPlugin(){

			U32	uiSize	=	m_vecPlugin.size();
			for(int	i	=	uiSize-1;i>=0;i--){
				m_vecPlugin[i]->ReleaseRef();
			}
			m_vecPlugin.clear();
			return	true;
		}
	
		U1 System::Stop(){
			//::PostQuitMessage(0);
			return	true;
		}
	
		U1 System::ParseDisplayParam(){
			EngineParam*	pSdt	=	&GetGlobalSetting().m_EngineParam;
			AString strDisplayName	=	GetGlobalSetting().m_EngineParam.strDisplay;
			File	file(strDisplayName);
	
			if(!file.Open())
				return	false;
	
			IniFile	cfgFile;
			if(!cfgFile.LoadFileFromMemory(file.GetData()))
				return false;	
			DisplayParam&	dParam	=	GetGlobalSetting().m_DisplayParam;
			AString	str;
			str	=	cfgFile.Get("Display","Width");			dParam.iWidth		=	Converter::ToS32(str);
			str	=	cfgFile.Get("Display","Height");		dParam.iHeight		=	Converter::ToS32(str);
			str	=	cfgFile.Get("Display","Window");		dParam.bWindow		=	Converter::ToU1(str);
			str	=	cfgFile.Get("Display","MSAA");			dParam.iMSAAType	=	Converter::ToS32(str);
			str	=	cfgFile.Get("Display","MSAAQuality");	dParam.iMSAAQuality	=	Converter::ToS32(str);
	
			m_strWindowName	=	cfgFile.Get("Display","WindowName");
			return	true;
	
		}

		void System::BeforeSwitchSystem( Common::ISystemManager* pSystemMgr, Common::ISystem* pOldSys, Common::ISystem* pNewSystem ){

		}

		void System::OnSwitchSystem( Common::ISystemManager* pSystemMgr, Common::ISystem* pOldSys, Common::ISystem* pNewSystem ){

		}

		void System::AfterSwitchSystem( Common::ISystemManager* pSystemMgr, Common::ISystem* pOldSys, Common::ISystem* pNewSystem ){

		}

		Air::U1 System::CreateWin(){
			HWND& hWindow	=	GetGlobalSetting().m_EngineParam.hWnd;
			if(hWindow==NULL){
				U32	uiWidth		=	GetGlobalSetting().m_DisplayParam.iWidth	+	16;
				U32	uiHeight	=	GetGlobalSetting().m_DisplayParam.iHeight	+	38;
				hWindow	=	Common::NewWindow("AirEngine",uiWidth,uiHeight,WNDPROC(WndProc));
			}else{
				RECT r;
				GetClientRect(hWindow,&r);
				GetGlobalSetting().m_DisplayParam.iWidth	=	r.right		-	r.left;
				GetGlobalSetting().m_DisplayParam.iHeight	=	r.bottom	-	r.top;
			}
			return	true;
		}

		Pipeline* System::GetCurrentPipeline()
		{
			return m_pCurrentPipeline;
		}

		void System::SetCurrentPipeline( Pipeline* pPipeline )
		{
			m_pCurrentPipeline	=	pPipeline;
		}

	}
};