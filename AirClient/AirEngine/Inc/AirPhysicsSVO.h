#ifndef AirPhysicsSVO_h__
#define AirPhysicsSVO_h__

#include "AirPhysicsShape.h"

namespace	Air{
	namespace	Physics{
		class	SVO	:	public	Common::IProduct{
		public:
			SVO(CAString& strName);

			virtual	U1	Create();
			virtual	U1	Destroy();
			void		Updata(const STD_VECTOR<U32>& svoData,U32 uiDepth,float fScale);
			U1			CollisionDetect(PointShape* shape,Float3* pV=NULL);
		public:
			U1			IsIntersect(PointShape* shape,const BoundingBox& box);
		protected:
			STD_VECTOR<U32>		m_SVO;
			U32					m_uiDepth;
			BoundingBox			m_BoundingBox;
			Float3				m_vHalfSize;
			float				m_fScale;
		};
	}
}
#endif // AirPhysicsSVO_h__
