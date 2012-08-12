/*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.


 \author    InfernalHell	Xinhe
 \date      2009/11/11
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceRegisterManager.h
 \note     
       
 \attention:
			ע�����������
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef INTERFACEREGISTERMANAGER_HEAD_FILE
#define INTERFACEREGISTERMANAGER_HEAD_FILE


//typedef SInt		Function;

#include "ScriptHeader.h"

namespace Air{
	
	
	namespace Client{
	
		
		namespace Script{
			/**	\brief	������
			*
			*	
			*
			***/
			enum ObjTypeFlags
			{
				OBJ_REF                   = 0x01,
				OBJ_VALUE                 = 0x02,
				OBJ_GC                    = 0x04,
				OBJ_POD                   = 0x08,
				OBJ_NOHANDLE              = 0x10,
				OBJ_SCOPED                = 0x20,
				OBJ_TEMPLATE              = 0x40,
				OBJ_APP_CLASS             = 0x100,
				OBJ_APP_CLASS_CONSTRUCTOR = 0x200,
				OBJ_APP_CLASS_DESTRUCTOR  = 0x400,
				OBJ_APP_CLASS_ASSIGNMENT  = 0x800,
				OBJ_APP_CLASS_C           = (OBJ_APP_CLASS + OBJ_APP_CLASS_CONSTRUCTOR),
				OBJ_APP_CLASS_CD          = (OBJ_APP_CLASS + OBJ_APP_CLASS_CONSTRUCTOR + OBJ_APP_CLASS_DESTRUCTOR),
				OBJ_APP_CLASS_CA          = (OBJ_APP_CLASS + OBJ_APP_CLASS_CONSTRUCTOR + OBJ_APP_CLASS_ASSIGNMENT),
				OBJ_APP_CLASS_CDA         = (OBJ_APP_CLASS + OBJ_APP_CLASS_CONSTRUCTOR + OBJ_APP_CLASS_DESTRUCTOR + OBJ_APP_CLASS_ASSIGNMENT),
				OBJ_APP_CLASS_D           = (OBJ_APP_CLASS + OBJ_APP_CLASS_DESTRUCTOR),
				OBJ_APP_CLASS_A           = (OBJ_APP_CLASS + OBJ_APP_CLASS_ASSIGNMENT),
				OBJ_APP_CLASS_DA          = (OBJ_APP_CLASS + OBJ_APP_CLASS_DESTRUCTOR + OBJ_APP_CLASS_ASSIGNMENT),
				OBJ_APP_PRIMITIVE         = 0x1000,
				OBJ_APP_FLOAT             = 0x2000,
				OBJ_MASK_VALID_FLAGS      = 0x3F7F,
				OBJ_SCRIPT_OBJECT         = 0x10000
			};
			/**	\brief	��������
			*
			*	�������� ������AngelScript
			*
			***/
			enum CallConvTypes
			{
				CALL_CDECL            = 0,
				CALL_STDCALL          = 1,
				CALL_THISCALL         = 2,
				CALL_CDECL_OBJLAST    = 3,
				CALL_CDECL_OBJFIRST   = 4,
				CALL_GENERIC          = 5
			};
			typedef void(*FUNCTION_t)();
			class UnknownClass;
			typedef void (UnknownClass::*METHOD_t)();
			const SInt sizeFunc = sizeof(METHOD_t);
			/**	\brief	����ָ����
			*
			*	����ָ���� �����ڽ�����ע�뵽AngelScript��
			*
			***/
			struct Function{
				//Method
	
				/**	\brief	�ຯ��
				*   
				*	@remarks 	�ຯ��
				*	@see		Function
				*	@return   	Client::Script::Function
				*	@param		T_Func fun
				*	@note
				*
				**/
				template<typename T_Func>
				inline static Function _Method(T_Func fun){
					Function rfun;
					memset(&rfun,0,sizeof(Function));
					memcpy(&rfun,&fun,sizeFunc);
					rfun.flag = 3;
					return rfun;
				};
				//Function
				/**	\brief	��ͨ����
				*   
				*	@remarks 	��ͨ����
				*	@see		Function
				*	@return   	Client::Script::Function
				*	@param		T_Func fun
				*	@note
				*
				**/
				template<typename T_Func>
				inline static Function _Function(T_Func fun){
					Function rfun;
					memset(&rfun,0,sizeof(Function));
					rfun.ptr.f.func = (FUNCTION_t)(UInt)fun;
					rfun.flag = 2;
					return rfun;
				};
				union{
					// The largest known method point is 20 bytes (MSVC 64bit),
					// but with 8byte alignment this becomes 24 bytes. So we need
					// to be able to store at least that much.
					char dummy[25]; 
					struct {METHOD_t   mthd; char dummy[25-sizeof(METHOD_t)];} m;
					struct {FUNCTION_t func; char dummy[25-sizeof(FUNCTION_t)];} f;
				} ptr;
				unsigned char flag; // 1 = generic, 2 = global func, 3 = method
			};
	
	#define METHOD(c,m)				Client::Script::Function::_Method((void (c::*)())(&c::m))
	#define METHODPR(c,m,p,r)		Client::Script::Function::_Method(static_cast<r (c::*)p>(&c::m))
	#define FUNCTION(f)				Client::Script::Function::_Function(f)
	#define FUNCYIONPR(f,p,r)		Client::Script::Function::_Function((void (*)())((r (*)p)(f))
	
	
			/**	\brief	��Ϊ
			*
			*	��AngelScript��asEBehaviours��ȡ���� �����������  �����ж
			*
			*	@see	asEBehaviours
			*
			***/
			enum Behaviours
			{
				// Value object memory management
				BEHAVE_CONSTRUCT,
				BEHAVE_DESTRUCT,
	
				// Reference object memory management
				BEHAVE_FACTORY,
				BEHAVE_ADDREF,
				BEHAVE_RELEASE,
	
				// Object operators
				BEHAVE_VALUE_CAST,
				BEHAVE_IMPLICIT_VALUE_CAST,
				BEHAVE_REF_CAST,
				BEHAVE_IMPLICIT_REF_CAST,
				BEHAVE_INDEX,
	
				// Garbage collection behaviours
				BEHAVE_FIRST_GC,
				BEHAVE_GETREFCOUNT = BEHAVE_FIRST_GC,
				BEHAVE_SETGCFLAG,
				BEHAVE_GETGCFLAG,
				BEHAVE_ENUMREFS,
				BEHAVE_RELEASEREFS,
				BEHAVE_LAST_GC = BEHAVE_RELEASEREFS,
				BEHAVE_MAX
			};
			/**	\brief	ע�����������
			*
			*	ע�������
			*
			***/
			class IRegisterManager{
			public:
				/**	\brief	ȫ�ֺ���
				*   
				*	@remarks 	ȫ�ֺ���
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  declaration
				*	@param		const Function & funcPointer
				*	@param		unsigned SInt callConv
				*	@note
				*
				**/
				virtual SInt RegisterGlobalFunction(const AChar *declaration, const Function &funcPointer, UInt callConv)=0;
	
				/**	\brief	ȫ�ֱ���
				*   
				*	@remarks 	ȫ�ֱ���
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  declaration
				*	@param		void * pointer
				*	@note
				*
				**/
				virtual SInt RegisterGlobalProperty(const AChar *declaration, void *pointer)=0;
	
				/**	\brief	�� ����
				*   
				*	@remarks 	ע��һ���ࣨ���ͣ�
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  obj
				*	@param		SInt byteSize
				*	@param		unsigned SInt flags
				*	@note
				*
				**/
				virtual SInt RegisterObjectType(const AChar *obj, SInt byteSize, UInt flags)=0;
				/**	\brief	ע��������
				*   
				*	@remarks 	ע��������
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  obj
				*	@param		const AChar*  declaration
				*	@param		SInt byteOffset
				*	@note
				*
				**/
				virtual SInt RegisterObjectProperty(const AChar *obj, const AChar *declaration, SInt byteOffset)=0;
				/**	\brief	ע���ຯ��
				*   
				*	@remarks 	ע���ຯ��
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  obj
				*	@param		const AChar*  declaration
				*	@param		const Function & funcPointer
				*	@param		unsigned SInt callConv
				*	@note
				*
				**/
				virtual SInt RegisterObjectMethod(const AChar *obj, const AChar *declaration, const Function &funcPointer, UInt callConv)=0;
				/**	\brief	ע������Ϊ
				*   
				*	@remarks 	ע������Ϊ
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  obj
				*	@param		Behaviours behaviour
				*	@param		const AChar*  declaration
				*	@param		const Function & funcPointer
				*	@param		unsigned SInt callConv
				*	@note
				*
				**/
				virtual SInt RegisterObjectBehaviour(const AChar *obj, Behaviours behaviour, const AChar *declaration, const Function &funcPointer, UInt callConv)=0;
				/**	\brief	ע��ӿ�
				*   
				*	@remarks 	ע��ӿ�
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  name
				*	@note
				*
				**/
				virtual SInt RegisterInterface(const AChar *name)=0;
				/**	\brief	ע��ӿڷ���
				*   
				*	@remarks 	ע��ӿڷ���
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  intf
				*	@param		const AChar*  declaration
				*	@note
				*
				**/
				virtual SInt RegisterInterfaceMethod(const AChar *intf, const AChar *declaration)=0;
				/**	\brief	ע���ַ�������
				*   
				*	@remarks 	ע���ַ�������
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  datatype
				*	@param		const Function & factoryFunc
				*	@param		unsigned SInt callConv
				*	@note
				*
				**/
				virtual SInt RegisterStringFactory(const AChar* datatype, const Function &factoryFunc, UInt callConv)=0;
	
				/**	\brief	ע��ö������
				*   
				*	@remarks 	ע��ö������
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  type
				*	@note
				*
				**/
				virtual SInt RegisterEnum(const AChar* type)=0;
				/**	\brief	ע��ö����������ֵ
				*   
				*	@remarks 	ע��ö����������ֵ
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  type
				*	@param		const AChar*  name
				*	@param		SInt value
				*	@note
				*
				**/
				virtual SInt RegisterEnumValue(const AChar* type, const AChar* name, SInt value)=0;
	
				/**	\brief	ע�����Ͷ���
				*   
				*	@remarks 	ע�����Ͷ���
				*	@see		CRegisterManager
				*	@return   	SInt
				*	@param		const AChar*  type
				*	@param		const AChar*  decl
				*	@note
				*
				**/
				virtual SInt RegisterTypedef(const AChar* type, const AChar* decl)=0;
			};
		}
	};
};

#endif // INTERFACEREGISTERMANAGER_HEAD_FILE