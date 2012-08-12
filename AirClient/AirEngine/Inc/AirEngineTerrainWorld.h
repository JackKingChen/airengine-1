#ifndef ENGINETERRAINWORLD_HEAD_FILE
#define ENGINETERRAINWORLD_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineTerrainCommon.h"
#include "AirEngineTerrainTitle.h"
namespace Air{
	
	namespace Client{
	
		
			namespace	Terrain{
	
				typedef	stdext::hash_map<UInt,Title*>	TitleMap;			///<	���ο������б�
				typedef	TitleMap::iterator				TitleMapItr;		///<	���ο������б������
				typedef	TitleMap::value_type			TitleMapPair;		///<	���ο������б�����
	
				typedef	std::list<Title*>				TitleList;			///<	���ο��б�
				typedef	TitleList::iterator				TitleListItr;		///<	���ο��б�
	
				typedef	std::vector<Title*>				TitleVector;
				typedef	TitleVector::iterator			TitleVectorItr;
	
				/**	\brief	����
				*
				*	����
				*
				***/
				class ENGINE_EXPORT	World	:	
					public	ILoadable{
				public:
					World();
					virtual	~World();
	
					/**	\brief	�����ͼ
					*   
					*	@remarks 	�����ͼ
					*	@see		World
					*	@return   	U1
					*	@param		AChar * strName
					*	@note
					*
					**/
					virtual U1	Load(AChar* strName );
					/**	\brief	���¼���
					*   
					*	@remarks 	���¼���
					*	@see		World
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1	ReLoad();
					virtual U1	New();
					virtual U1	UnLoad();
					virtual U1	Save();
	
					virtual U1	ChangePosition(Real x,Real y );
	
					virtual void	Updata();
					virtual	void	Render();
	
					virtual U1	GetHeight(Real	x,Real	y,	Real*	z	= NULL);
				private:
					U1	LoadInfo(AChar* strName);
	
					U1	LoadTitle(	ID	titleID);
					U1	UnLoadTitle(ID	titleID);
	
					/**	\brief	�л����ο�
					*   
					*	@remarks 	��Խ���ο�߽�
					*	@see		World
					*	@return   	U1
					*	@param		ID currentTitleID
					*	@note
					*
					**/
					U1	ChangeTitle(ID	currentTitleID);
					/**	\brief	���µ��ο�
					*   
					*	@remarks 	���µ��ο�
					*	@see		World
					*	@return   	U1
					*	@note
					*
					**/
					U1	UpdataTitle();
	
	
					U1	RenderSky();
					U1	RenderTerrain();
					U1	RenderObject();
					U1	RenderGrass();
					U1	RenderWater();
					U1	RenderAlphaObject();
	
					U1	UpdataIndex();
	
					MapInfo				m_Info;						///<	��ͼ��Ϣ
	
	
					TitleVector			m_TitleArray;				///<	������Ⱦ�ĵ��ο�����
					TitleMap			m_mapLoadedTitle;			///<	���ڲ�ѯ�ĵ��ο飨�Ѽ��ص��ڴ�����е��ο飩
					TitleList			m_lstLoadedTitle;			///<	����ж�ص��ο��б��Ѽ��ص��ڴ�����е��ο飩
	
				};
			}
	
	};
};
#endif // RENDERTERRAINWORLD_HEAD_FILE