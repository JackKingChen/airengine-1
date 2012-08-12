#ifndef COMMONXML_HEAD_FILE
#define COMMONXML_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

class	TiXmlDocument;
class	TiXmlNode;
class	TiXmlElement;
class	TiXmlHandle;
namespace Air{
	
	namespace Common{
	
		/**	\brief	Xml������
		*
		*	Xml������
		*
		***/
		class	COMMON_EXPORT	Xml{
		public:
			/**	\brief	Xml�ڵ���
			*
			*	�ڵ���
			*
			***/
			class	COMMON_EXPORT	Node{
			public:
				Node(TiXmlElement*	pNode	=	NULL);
				~Node();
	
				typedef		std::vector<Node>		NodeVector;
				typedef		NodeVector::iterator	NodeVectorItr;
	
				/**	\brief	��ȡ����ֵ
				*   
				*	@remarks 	��ȡ����ֵ
				*	@see		Node
				*	@return   	U1
				*	@param		AString strName
				*	@param		int * p
				*	@note
				*
				**/
				U1			GetAttribute(AString strName,int*	p);
				/**	\brief	��ȡ����ֵ
				*   
				*	@remarks 	��ȡ����ֵ
				*	@see		Node
				*	@return   	U1
				*	@param		AString strName
				*	@param		Real * p
				*	@note
				*
				**/
				U1			GetAttribute(AString strName,Real*	p);
				/**	\brief	��ȡ����ֵ
				*   
				*	@remarks 	��ȡ����ֵ
				*	@see		Node
				*	@return   	AString
				*	@param		AString strName
				*	@note
				*
				**/
				AString		GetAttribute(AString strName);
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		Node
				*	@return   	void
				*	@param		AString strName
				*	@param		AString strValue
				*	@note
				*
				**/
				void		SetAttribute(AString strName,AString	strValue);
	
				/**	\brief	��ȡ�ڵ��ֵ
				*   
				*	@remarks 	��ȡ�ڵ��ֵ
				*	@see		Node
				*	@return   	AString
				*	@note
				*
				**/
				AString		GetValue();
	
				/**	\brief	��ȡ�ڵ�����
				*   
				*	@remarks 	��ȡ�ڵ�����
				*	@see		Node
				*	@return   	AString
				*	@note
				*
				**/
				AString		GetName();
	
				/**	\brief	�Ƿ�Ϊ��
				*   
				*	@remarks 	�Ƿ�Ϊ��
				*	@see		Node
				*	@return   	U1
				*	@note
				*
				**/
				U1			IsNull(){
					return	m_pNode	==	NULL;
				}
	
	
				/**	\brief	���ҽڵ�
				*   
				*	@remarks 	���ҽڵ�
				*	@see		Xml
				*	@return   	Common::Xml::Node
				*	@param		AString strChildNode
				*	@note
				*
				**/
				Node	Find(AString	strChildNode);
				Node	FindPath(AString	strPath);
				Node	Next();
				//Node	FirstChild(AString	strChildName);
	
				NodeVector	FindNodeVector(AString	strChildNode);
				NodeVector	FindNodeVectorPath(AString	strPath);
	
				UInt	GetNodeCount();
			
				//TiXmlNode*	m_pNode;
				TiXmlElement*	m_pNode;	///<	�ڵ�ָ��
			};
	
	
			Xml();
			~Xml();
	
			/**	\brief	�����ļ�
			*   
			*	@remarks 	�����ļ�
			*	@see		Xml
			*	@return   	U1
			*	@param		AString strName
			*	@note
			*
			**/
			U1	LoadFromFile(AString	strName);
			U1	LoadFromMemory(U8* pData,UInt uiSize);
	
			/**	\brief	����
			*   
			*	@remarks 	����
			*	@see		Xml
			*	@return   	U1
			*	@note
			*
			**/
			U1	Save();
			U1	SaveAs(AString	strAnotherName);
	
	
	
			/**	\brief	��ȡ�ӽڵ�����
			*   
			*	@remarks 	��ȡ�ӽڵ�����
			*	@see		Xml
			*	@return   	AString
			*	@param		AString strName
			*	@param		AString strAttrubute
			*	@note
			*
			**/
			AString			GetAttribute(AString	strName,AString	strAttrubute);
	
			Node	GetRootNode();
	
			TiXmlDocument*	m_pDocument;	///<	�ĵ���ָ��
		};
	
	};
};
#endif // COMMONXML_HEAD_FILE