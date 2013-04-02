//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/08
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  EngineCharacterResource.h
 \note     
       
 \attention:
			ģ����Դ
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINECHARACTERRESOURCE_HEAD_FILE
#define ENGINECHARACTERRESOURCE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderBuffer.h"


class	CalCoreModel;
class	CalCoreMesh;
namespace Air{
	
	namespace Engine{
	
		namespace	Character{
			typedef	CalCoreModel	CoreMesh;
	
	
			struct	MeshHDBuffer{
				MeshHDBuffer(){
					pVertexBuff		=	NULL;
					pIndexBuff		=	NULL;
					pVertexDeclare	=	NULL;
				};
				/**	\brief	���ָ��
				*   
				*	@remarks 	���ָ��
				*	@see		MeshHDBuffer
				*	@return   	void
				*	@note
				*
				**/
				void	Clear(){
					pVertexBuff		=	NULL;
					pIndexBuff		=	NULL;
					pVertexDeclare	=	NULL;
				};
				Render::Buffer*		pVertexBuff;
				Render::Buffer*		pIndexBuff;
				Render::Vertex::IDeclare*	pVertexDeclare;
			};
			/**	\brief	ģ�Ͷ�����Դ
			*
			*	ģ�Ͷ�����Դ
			*
			***/
			class	ENGINE_EXPORT	Resource	:
				public	IProduct{
			public:
				/**	\brief	ģ�ͺͶ����ļ�������Ϣ
				*
				*	ģ�ͺͶ����ļ�������Ϣ
				*
				***/
				struct Info{
					Info(AString	name,UInt id	=	-1){
						strcpy_s(strName,MAX_NAME,name.c_str());
						uiID		=	id;
						uiRefCount	=	0;
						pUserData	=	NULL;
					};
					/**	\brief	�ж��Ƿ�Ϊ��
					*   
					*	@remarks 	�ж��Ƿ�Ϊ��
					*	@see		Info
					*	@return   	U1
					*	@note
					*
					**/
					U1	IsNull(){
						return (uiRefCount <=0 || uiID	== -1);
					}
					AChar	strName[MAX_NAME];		///<	����
					UInt	uiID;					///<	id
					UInt	uiRefCount;				///<	���ü���
					void*	pUserData;				///<	�Զ�������
				};
				typedef	stdext::hash_map<AString,Info>	InfoMap;
				typedef	InfoMap::iterator				InfoMapItr;
				typedef	InfoMap::value_type				InfoMapPair;
			public:
				Resource(CAString&	strName,AString*	strSkeleton);
				virtual ~Resource();
	
				/**	\brief	����ģ����Դ
				*   
				*	@remarks 	����ģ����Դ
				*	@see		Resource
				*	@return   	UInt
				*	@param		AString strName
				*	@param		MeshHDBuffer* pOutMeshBuff
				*	@note
				*
				**/
				SInt	LoadMesh(CAString&	strName,MeshHDBuffer*	pOutMeshBuff	=	NULL);
				/**	\brief	ж��ģ����Դ
				*   
				*	@remarks 	ж��ģ����Դ
				*	@see		Resource
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				U1		UnLoadMesh(CAString&	strName);
				/**	\brief	���붯����Դ
				*   
				*	@remarks 	���붯����Դ
				*	@see		Resource
				*	@return   	UInt
				*	@param		AString strName
				*	@note
				*
				**/
				SInt	LoadAnimation(CAString&	strName);
				/**	\brief	ж�ض�����Դ
				*   
				*	@remarks 	ж�ض�����Դ
				*	@see		Resource
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				U1		UnLoadAnimation(CAString&	strName);
	
				SInt	GetAnimationID(CAString&	strName);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		Resource
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Create();
				/**	\brief	�ݻ�
				*   
				*	@remarks 	�ݻ�
				*	@see		Resource
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();

			protected:
				U1			ParseConfig(CAString&	strConfig);
	
				/**	\brief	����Ӳ������
				*   
				*	@remarks 	����Ӳ������
				*	@see		Resource
				*	@return   	U1
				*	@param		MeshHDBuffer * pOutBuff
				*	@param		CalCoreMesh * pInMesh
				*	@note
				*
				**/
				U1			CreateHardwareBuff(MeshHDBuffer*	pOutBuff,CalCoreMesh*	pInMesh);
				/**	\brief	�ݻ�Ӳ������
				*   
				*	@remarks 	�ݻ�Ӳ������
				*	@see		Resource
				*	@return   	U1
				*	@param		MeshHDBuffer * pInBuff
				*	@note
				*
				**/
				U1			DestroyHardwareBuff(MeshHDBuffer*	pInBuff);
	
			public:
			protected:
				InfoMap		m_mapMeshInfo;				///<	ģ����Ϣ�б�
				InfoMap		m_mapAnimationInfo;			///<	�����б�
				AString		m_strSkeleton;				///<	����
			};

		}
	
	};
};
#endif // ENGINECHARACTERMESH_HEAD_FILE