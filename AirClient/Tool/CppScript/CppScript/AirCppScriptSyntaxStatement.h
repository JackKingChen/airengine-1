#ifndef AirCppScriptSyntaxStatement_h__
#define AirCppScriptSyntaxStatement_h__

#include "AirCppScriptSyntaxVariable.h"

namespace	Air{
	namespace	CppScript{
		enum	enumStatementType{
			enST_Unknown,
			enST_If,
			enST_Else,
			enST_ElseIf,
			enST_For,
			enST_While,
			enST_Switch,
			enST_New,
			enST_Delete,
			enST_Return,
			enST_Break,
			enST_Continue,

		};
		class	StatementNode	:	public	Node{
		public:
			StatementNode(){
				m_Type			=	enNT_Statement;
				m_sType			=	enST_Unknown;
			};
			virtual	enumSyntaxError	Parse(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError			ParseSubStatement(WordInfoVector& vecInfo,U32& idx);

			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			enumStatementType		m_sType;
		};
		class	ElseStatementNode	:	public	StatementNode{
		public:
			ElseStatementNode(){
				m_sType			=	enST_Else;
				m_strName		=	"Else";
				m_uiJump		=	0;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			U32		m_uiJump;
		};
		class	IfStatementNode	:	public	ElseStatementNode
		{
		public:
			IfStatementNode(){
				m_sType			=	enST_If;
				pConditionExp	=	NULL;
				m_strName		=	"If";
				m_uiEntry		=	0;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			Node*	pConditionExp;
			U32		m_uiEntry;
		};
		class	ElseIfStatementNode	:	public	ElseStatementNode
		{
		public:
			ElseIfStatementNode(){
				m_sType			=	enST_ElseIf;
				pConditionExp	=	NULL;
				m_strName		=	"ElseIf";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			Node*	pConditionExp;
		};

		class	ForStatementNode	:	public	StatementNode
		{
		public:
			ForStatementNode(){
				m_sType			=	enST_For;
				pInitExp		=	NULL;
				pConditionExp	=	NULL;
				pIterExp		=	NULL;
				m_strName		=	"For";
			};
			virtual	enumSyntaxError	Parse(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError	ParseCondition(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError	ParseCode(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError	ParseSubCondition_Init(WordInfoVector& vecInfo);
			enumSyntaxError	ParseSubCondition_Condition(WordInfoVector& vecInfo);
			enumSyntaxError	ParseSubCondition_Iter(WordInfoVector& vecInfo);

			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);

			Node*	pInitExp;
			Node*	pConditionExp;
			Node*	pIterExp;
		};
		class	WhileStatementNode	:	public	StatementNode
		{
		public:
			WhileStatementNode(){
				m_sType			=	enST_While;
			};
		};
		class	SwitchStatementNode	:	public	StatementNode
		{
		public:
			SwitchStatementNode(){
				m_sType			=	enST_Switch;
			};
		};
		class	NewStatementNode	:	public	StatementNode{
		public:
			NewStatementNode(){
				m_sType		=	enST_New;
				pObject		=	NULL;
				uiNewCount	=	1;
				m_strName		=	"New";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*							pObject;
			U32								uiNewCount;
		};
		class	DeleteStatementNode	:	public	StatementNode{
		public:
			DeleteStatementNode(){
				m_sType		=	enST_Delete;
				pObject		=	NULL;
				m_strName		=	"Delete";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			Node*							pObject;
		};
		class	ReturnStatementNode	:	public	StatementNode{
		public:
			ReturnStatementNode(){
				m_sType		=	enST_Return;
				pReturn		=	NULL;
				m_strName		=	"Return";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			Node*							pReturn;
			U32								m_uiJump;
		};

		class	BreakStatementNode	:public	StatementNode{
		public:
			BreakStatementNode(){
				m_sType			=	enST_Break;
				m_uiJump		=	0;
				m_strName		=	"Break";
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			U32								m_uiJump;
		};

		class	ContinueStatementNode	:public	BreakStatementNode{
		public:
			ContinueStatementNode(){
				m_sType			=	enST_Continue;
				m_strName		=	"Continue";
			};
		};
	}
}
#endif // AirCppScriptSyntaxStatement_h__
