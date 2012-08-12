#ifndef INTERFACEALPHAOBJECTMANAGER_HEAD_FILE
#define INTERFACEALPHAOBJECTMANAGER_HEAD_FILE

#include "AirEngineHeader.h"

namespace Air{
	
	namespace Client{
		class	Renderable;
	
		/**	\brief	��͸������
		*
		*	��͸������
		*
		***/
		struct	AlphaObject{
			AlphaObject(){
				pRenderObj	=	NULL;
				fDistance	=	0;
			};
			Renderable*		pRenderObj;
			//Float44						mat;			///<	�������
			Float3						vPos;
			Real						fDistance;		///<	����
		};
		/**	\brief	��͸��������Ⱦ������
		*
		*	��͸��������Ⱦ����
		*
		***/
		class	IAlphaObjectManager{
		public:
			IAlphaObjectManager();
			/**	\brief	�����͸������
			*   
			*	@remarks 	�����͸��
			*	@see		IAlphaObjectManager
			*	@return   	void
			*	@param		AlphaObject obj
			*	@note
			*
			**/
			virtual	void	PushAlphaObject(AlphaObject	obj);
	
			/**	\brief	��Ⱦ���а�͸������
			*   
			*	@remarks 	��Ⱦ��͸������
			*	@see		IAlphaObjectManager
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	RenderAlphaObject();
	
			//typedef		std::list<AlphaObject>			AObjectList;
			//typedef		AObjectList::iterator			AObjectListItr;
			//typedef		AObjectList::reverse_iterator	AObjectListRItr;
	
			//AObjectList		m_lstAlphaObject;
			Float3*		m_pCameraPosition;
		};
	
	};
};
#endif // INTERFACEALPHAOBJECTMANAGER_HEAD_FILE