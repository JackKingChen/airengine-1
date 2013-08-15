#ifndef AirCppScriptSyntaxNode_h__
#define AirCppScriptSyntaxNode_h__


#include "AirCppScriptDefineType.h"

namespace	Air{
	namespace	CppScript{
		enum enumNodeType{
			enNT_Unknown,
			enNT_Global,
			enNT_NameSpace,
			enNT_ImportFunction,
			enNT_Variable,
			enNT_Constant,
			enNT_Function,
			enNT_Object,
			enNT_Parameter,
			enNT_Statement,
			enNT_VariableStatement,
			enNT_IfStatement,
			enNT_ForStatement,
			enNT_WhileStatement,
			enNT_SwitchStatement,
			enNT_Expression,
			enNT_FunctionCall_Expression,
			enNT_New_Object_Expression,
			enNT_Delete_Object_Expression,
			enNT_Return_Object_Expression,
			enNT_Break_Object_Expression,
			enNT_Continue_Object_Expression,
			enNT_Block,

		};
		enum	enumSyntaxError{
			enSE_OK,
			enSE_UnexpectedEnd,
			enSE_PreDeclare_Must_Fallow_A_CppKeyword,
			enSE_PreDeclare_Fallow_Unknown,
			enSE_Include_Must_Fallow_A_String,
			enSE_Define_Cant_Fallow_A_Number,
			enSE_Define_Cant_Fallow_A_String,
			enSE_Define_Cant_Fallow_A_CppKeyword,
			enSE_Define_Cant_Fallow_A_Operator,
			enSE_Define_Cant_Fallow_A_Delimiter,
			enSE_Unrecognized_Operator,
			enSE_Unrecognized_Delimiter,
			enSE_NameSpace_Cant_Fallow_A_Number,
			enSE_NameSpace_Cant_Fallow_A_String,
			enSE_NameSpace_Cant_Fallow_A_CppKeyword,
			enSE_NameSpace_Cant_Fallow_A_Operator,
			enSE_NameSpace_Cant_Fallow_A_Delimiter,
			enSE_Unsigned_Not_Match_Void,
			enSE_Unsigned_Not_Match_Bool,
			enSE_Unsigned_Not_Match_Float,
			enSE_Unsigned_Not_Match_Double,
			enSE_Unrecognized_Variable_Type,
			enSE_Miss_Variable_Name,
			enSE_Variable_Name_Cant_Be_A_Number,
			enSE_Variable_Name_Cant_Be_A_CppKeyword,
			enSE_Variable_Name_Cant_Be_A_String,
			enSE_Illegal_Variable_Name,
			enSE_Variable_Name_Already_Declaration,
			enSE_Unsigned_Object_Cant_Be_A_Negative_Value,
			enSE_Bool_Object_Cant_Be_A_Negative_Value,
			enSE_Void_Cant_Be_Unsigned,
			enSE_Bool_Cant_Be_Unsigned,
			enSE_Float_Cant_Be_Unsigned,
			enSE_Variable_Miss_Delimiter_End_Of_Statement,
			enSE_Unrecognized_Variable_Init_Value,
			enSE_Unrecognized_Variable,
			enSE_Int_Variable_Need_A_Int_Init_Value,
			enSE_Float_Variable_Need_A_Float_Init_Value,
			enSE_CharPtr_Variable_Need_A_String_Init_Value,
			enSE_Function_Declare_Must_Fallow_Parameter,
			enSE_Unrecognized_Parameter,
			enSE_Function_Parameter_Name_Already_Exist,
			enSE_Illegal_Class_Or_Struct_Name,
			enSE_Class_Or_Struct_Name_Already_Exist,
			enSE_Unrecognized_Inherit_Type,
			enSE_Unrecognized_Inherit_Object,
			enSE_Unrecognized_Class_Or_Struct_Word,
			enSE_Public_Private_Protected_Must_Fallow_Colon,
			enSE_Variable_Array_Count_Must_Be_Int_Number,
			enSE_Variable_Array_Count_Must_Greater_Than_Zero,
			enSE_Miss_End_Of_SquareBracket,


			enSE_Unknown_Error	=	0xffffffff
		};

		template<typename T>
		void	DeleteAllElement(T& t){
			T::iterator i = t.begin();
			for(;i!=t.end();i++){
				delete *i;
				*i=NULL;
			}
			t.clear();
		}

		void	Print(const char* str);
		class	Node;
		typedef std::list<Node*>	NodeList;
		class	Node{
		public:
			Node();
			virtual	~Node();

			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParsePreDeclare(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseInclude(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		AddInclude(CAString& strName);
			virtual	enumSyntaxError		ParseDefine(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		AddDefine(CAString& strName);
			virtual	enumSyntaxError		ParseCppKeyword(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				IsVariableDeclare(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				IsFunctionDeclare(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				IsFunction(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				ParseObjectType(WordInfoVector& vecInfo,U32& idx,ObjectType& t,Node** pObjectNode	=	NULL);
			enumSyntaxError				ParseVariableName(WordInfoVector& vecInfo,U32& idx,AString& strName,U1 bCheckExist	=	true);


			enumSyntaxError				FindBlock(WordInfoVector& vecInfo,U32& idx,WordInfoVector& outInfo,U32 uiKeyBegin,U32 uiKeyEnd);
			enumSyntaxError				FindStatementEnd(WordInfoVector& vecInfo,U32& idx,WordInfoVector& outInfo);
			enumSyntaxError				ParseExpression(WordInfoVector& vecInfo,U32& idx);

			enumNodeType	GetType()const{return m_Type;};
			CAString&		GetName()const{return m_strName;};
			void			SetType(enumNodeType t){m_Type=t;};
			void			SetName(CAString& str){m_strName=str;};
			Node*			GetParent(){return m_pParent;};
			void			SetParent(Node* p){m_pParent=p;};
			U32				GetChildCount(){return m_lstChild.size();};
			void			AddChild(Node* p);
			void			RemoveChild(Node* p);
			Node*			GetRootNode();
			Node*			FindNode(CAString& strName,enumNodeType type = enNT_Unknown,U1 bFindParent = true);
		protected:
			enumNodeType	m_Type;
			AString			m_strName;
			NodeList		m_lstChild;
			Node*			m_pParent;
		};
	}
}
#endif // AirCppScriptSyntaxNode_h__
