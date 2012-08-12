#include "AirGlobalSetting.h"
//#include "asm_math.h"

#include "AirRenderSystem.h"

namespace Air{
	
	namespace	Client{
		
		static	std::map<AString,U8>	g_StringKey;
		static	AString					g_KeyString[]	=	{
			//0x0*
			"No",	"Esc",	"1",	"2",	"3",	"4",	"5",	"6",	"7",	"8",	"9",	"0",	"-",	"=",	"Back",	"Tab",
			//0x1*
			"q",	"w",	"e",	"r",	"t",	"y",	"u",	"i",	"o",	"p",	"[",	"]",	"Return","LCtrl","a",	"s",
			//0x2*
			"d",	"f",	"g",	"h",	"j",	"k",	"l",	";",	"'",	"",		"LShift","",	"z",	"x",	"c",	"v",
			//0x3*
			"b",	"n",	"m",	"",		"",		"",		"RShift","",	"LAlt",	"Space","",		"F1",	"F2",	"F3",	"F4",	"F5",
			//0x4*
			"F6",	"F7",	"F8",	"F9",	"F10",	"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",
			//0x5*
			"",		"",		"",		"",		"",		"",		"",		"F11",	"F12",	"",		"",		"",		"",		"",		"",		"",
			//0x6*
			"",		"",		"",		"",		"F13",	"F14",	"F15",	"",		"",		"",		"",		"",		"",		"",		"",		"",
			//0x7*
			"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",
			//0x8*
			"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",
			//0x9*
			"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"RCtrl","",		"",
			//0xA*
			"Mute",	"",		"Play",	"",		"Stop",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"VDown","",
			//0xB*
			"VUp",	"",		"WHome","",		"",		"",		"",		"",		"RAlt",	"",		"",		"",		"",		"",		"",		"",
			//0xC*
			"",		"",		"",		"",		"",		"Pause","",		"Home",	"Up",	"PGUp",	"",		"Left",	"",		"Right","",		"End",
			//0xD*
			"Down",	"PGDown","Ins",	"Del",	"",		"",		"",		"",		"",		"",		"",		"LWin",	"RWin",	"App",	"Power","Sleep",
			//0xE*
			"",		"",		"",		"Wake",	"",		"WSreach","WFav","WRefresh","WStop","WFor","WBack","PC","Mail",	"",		"",		"",
			//0xF*
			"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		"",		""
	
		};
	
		void	InitStringKey(){
			for(UInt i=0;i<256;i++){
				if(g_KeyString[i].empty())
					continue;
				U8	k	=	i;
				g_StringKey.insert(std::map<AString,U8>::value_type(g_KeyString[i].c_str(),k));
			}
		}
	
		GlobalSetting::GlobalSetting(){
	
	
			m_pEngine			=	NULL;
			m_pRenderSystem		=	NULL;
			//m_pGameSystem		=	NULL;
			m_pInputSystem		=	NULL;
			m_pPhysicsSystem	=	NULL;
			m_pScriptSystem		=	NULL;
			m_pAudioSystem		=	NULL;
			m_pNetSystem		=	NULL;
			m_pResourceSystem	=	NULL;
			m_pParticleSystem	=	NULL;
	
			m_pDefaultFont		=	NULL;
	
			m_bQuit				=	false;
	
	
			//m_uiOrginTechnique		=	Render::IMaterial::enTECH_VERYHIGH;
			//m_uiCurrentTechnique	=	Render::IMaterial::enTECH_VERYHIGH;
	
			//Render::IMaterial::Technique::InitParamTypeMap();
	
			InitStringKey();
	
		//	OutputDebugStringA("===============GlobalSetting	Construct================\n");
		}
	
		GlobalSetting::~GlobalSetting(){
		}
	
	
	
	
		Ray GlobalSetting::GetCursorPostionRay(SInt x	/*=	-1*/,SInt y/* = -1*/){
	
			POINT point;
			if(x!=-1&&y!=-1){
				point.x	=	x;
				point.y	=	y;
			}else{
				GetCursorPos(&point);
				ScreenToClient(	m_EngineParam.hWnd, &point );
			}
	
			Common::Matrix mInverseView	=	m_ShaderParam.m_matView;
			mInverseView.Inverse();
	 
	 		// Compute the vector of the pick ray in screen space
	 		Float3 v;
	 		v.x = ( ( ( 2.0f * point.x ) / m_ShaderParam.m_iScreenWidth ) - 1 ) /m_ShaderParam.m_matProj.m00;
	 		v.y = -( ( ( 2.0f * point.y ) / m_ShaderParam.m_iScreenHeight ) - 1 ) /m_ShaderParam.m_matProj.m11;
			//�������������ϵ Z����Ϊ-1 ��������ϵΪ1 ����ע��
	 		v.z = 1;//-m_ShaderParam.m_matProj[3][2];
	 
	 		Ray ray;

	 		// Transform the screen space pick ray into 3D space
 	 		ray.m_vDirection.x = v.x * mInverseView.m00 + v.y * mInverseView.m10 + v.z * mInverseView.m20;
 	 		ray.m_vDirection.y = v.x * mInverseView.m01 + v.y * mInverseView.m11 + v.z * mInverseView.m21;
 	 		ray.m_vDirection.z = v.x * mInverseView.m02 + v.y * mInverseView.m12 + v.z * mInverseView.m22;
// 	 		//origin	=	m_vCurrentPosition;
 			ray.m_vStart	=	Float3(mInverseView.m30,mInverseView.m31,mInverseView.m32);
			//Ray ray;
			ray.m_vDirection.Normalize();
	
	// 		Float44 inverseVP = (m_matView	*	m_matProj).inverse();
	// 
	// 		Real nx = (2.0f * point.x/m_iScreenWidth) - 1.0f;
	// 		Real ny = 1.0f - (2.0f * point.y/m_iScreenHeight);
	// 		Float3 nearPoint(nx, ny, -1.f);
	// 		// Use midPoint rather than far point to avoid issues with infinite projection
	// 		Float3 midPoint (nx, ny,  1.0f);
	// 
	// 		// Get ray origin and ray target on near plane in world space
	// 		Float3 rayOrigin, rayTarget;
	// 
	// 		rayOrigin = inverseVP * nearPoint;
	// 		rayTarget = inverseVP * midPoint;
	// 
	// 		Float3 rayDirection = rayTarget - m_vCurrentPosition;
	// 		rayDirection.normalise();
	
			return ray;
		}
	
	
		U1 GlobalSetting::ParsePath( AString strName,AString* pStrPostfix,AString* pStrFileName /*= NULL*/,AString* pStrPath /*= NULL*/ ){
			if(strName.empty())
				return false;
			AChar	postfixChar	=	'.';
			AChar	pathChar	=	'\\';
			AChar	pathChar1	=	'/';
	
			AChar	postfixName[MAX_NAME],fileName[MAX_NAME],pathName[MAX_NAME];
			ZeroMemory(postfixName,MAX_NAME);
			ZeroMemory(fileName,MAX_NAME);
			ZeroMemory(pathName,MAX_NAME);
			UInt	uiSize	=	strName.size();
			UInt	uiPathPos=-1,uiPostfixPos=-1;
			for(UInt	i=uiSize-1;i>=0;i--){
				//�Ӻ���ǰ��ѯ	�ҵ���.���ؼ��ַ�
				if(strName[i] == postfixChar	&&	uiPostfixPos==-1){
					uiPostfixPos	=	i;
					continue;
				}
	
				//�Ӻ���ǰ�ҵ�"\""/"��2���ؼ��ַ�
				if(strName[i]==pathChar||strName[i]==pathChar1){
					uiPathPos	=	i;
					break;
				}
			}
	
			//��������ʱ�ַ�����
			if(uiPostfixPos!=-1){
				memcpy(postfixName,&strName[uiPostfixPos+1],uiSize-uiPostfixPos-1);	
				if(pStrPostfix!=NULL){
					*pStrPostfix	=	postfixName;
				}
				if(uiPathPos!=-1){
					memcpy(fileName,&strName[uiPathPos+1],uiPostfixPos-uiPathPos-1);
					if(pStrFileName!=NULL){
						*pStrFileName	=	fileName;
					}
					memcpy(pathName,&strName[0],uiPathPos);
					if(pStrPath!=NULL){
						*pStrPath	=	pathName;
					}
				}
				return true;
			}
			return false;
		}
	
	
	
	
	
		AString GlobalSetting::GetKeyString( U8 key ){
			return	g_KeyString[key];
		}
	
		U8 GlobalSetting::GetKey( AString& str ){
			std::map<AString,U8>::iterator	i	=	g_StringKey.find(str.c_str());
			if(i!=g_StringKey.end()){
				return	i->second;
			}else{
				return	0;
			}
		}
		//--------------------------------------------------------------------------------------
		// Given a ray origin (orig) and direction (dir), and three vertices of a triangle, this
		// function returns TRUE and the interpolated texture coordinates if the ray intersects 
		// the triangle
		//--------------------------------------------------------------------------------------
		bool IntersectTriangle( Ray&	ray,
								Float3& v0, 
								Float3& v1, 
								Float3& v2,
								Real* t, 
								Real* u/*	=	NULL*/, 
								Real* v/*	=	NULL*/ ){
			// Find vectors for two edges sharing vert0
// 			XMVECTOR edge1 = v1 - v0;
// 			XMVECTOR edge2 = v2 - v0;
// 			XMVECTOR	dir		=	ray.mDirection;
// 			XMVECTOR	orig	=	ray.getOrigin();
// 	
// 			// Begin calculating determinant - also used to calculate U parameter
// 			Float3 pvec	=	dir.crossProduct(edge2) ;
// 	
// 			// If determinant is near zero, ray lies in plane of triangle
// 			Real det = edge1.dotProduct(pvec );
// 	
// 			Float3 tvec;
// 			if( det > 0 )
// 			{
// 				tvec = orig - v0;
// 			}
// 			else
// 			{
// 				tvec = v0 - orig;
// 				det = -det;
// 			}
// 	
// 			if( det < 0.0001f )
// 				return false;
// 	
// 			// Calculate U parameter and test bounds
// 			Real	fu	= tvec.dotProduct( pvec );
// 			if( fu < 0.0f || fu > det )
// 					return false;
// 			
// 	
// 			// Prepare to test V parameter
// 			Float3 qvec	=	tvec.crossProduct( edge1 );
// 	
// 			// Calculate V parameter and test bounds
// 			Real	fv	= dir.dotProduct( qvec );
// 			if( fv < 0.0f || fu + fv > det )
// 				return false;
// 			
// 	
// 			// Calculate t, scale parameters, ray intersects triangle
// 			*t = edge2.dotProduct( qvec );
// 			Real fInvDet = 1.0f / det;
// 			*t	*= fInvDet;
// 			if(u!=NULL)
// 				*u = fu*fInvDet;
// 			if(v!=NULL)
// 				*v = fv*fInvDet;
	
			return true;
		}
	
		//�������ߡ�������붯̬������ڴ��У�ע�����������ߣ�һ��Ϊ�����ߣ�һ��Ϊ�������ߡ�
		//����inֵΪ������vertexCount, ������Ϣ����vertex, ���㷨�����飬���������������飬����������
		//���������飬 �������ߵ�����ָ�롣
		void CalculateTangentArray(	UInt		vertexCount, 
									Float3*	vertex,
									Float3*	normal,
									Float2*	texcoord,
									UInt	triangleCount,
									UInt*	triangle,
									Float3*	tangent)
		{
	
			//һ�������Ӧ�������ߣ���������tan1��������2����������3D�����ռ䡣
			//tan1Ϊ�����ߴ�ŵ�ַ���
			Float3 *tan1 = new Float3[vertexCount * 2];
	
			//tan2Ϊ�������ߴ�ŵ�ַ���
			Float3 *tan2 = tan1 + vertexCount;
	
			//���������ߴ�ſռ������
			ZeroMemory(tan1, vertexCount * sizeof(Float3) * 2);
	
			//����ÿ��������
			for (UInt a = 0; a < triangleCount; a++)
			{
	
				//��ȡ��a�������ε������������� i1, i2, i3��
				UInt i1 = triangle[a*3];
				UInt i2 = triangle[a*3+1];
				UInt i3 = triangle[a*3+2];
	
				//ͨ������������ȡ3����ʵ�����λ����Ϣ��
				const Float3& v1 = vertex[i1];
				const Float3& v2 = vertex[i2];
				const Float3& v3 = vertex[i3];
	
				//��ȡ���������������Ϣ��
				const Float2& w1 = texcoord[i1];
				const Float2& w2 = texcoord[i2];
				const Float2& w3 = texcoord[i3];
	
				//Ȼ������㷨����������
				float x1 = v2.x - v1.x;
				float x2 = v3.x - v1.x;
				float y1 = v2.y - v1.y;
				float y2 = v3.y - v1.y;
				float z1 = v2.z - v1.z;
				float z2 = v3.z - v1.z;
	
				float s1 = w2.x - w1.x;
				float s2 = w3.x - w1.x;
				float t1 = w2.y - w1.y;
				float t2 = w3.y - w1.y;
	
				float r = 1.0F / (s1 * t2 - s2 * t1);
	
				Float3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
	
				Float3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);
	
				//������ĵ�a�����3������������߱���
				tan1[i1] =	Float3(tan1[i1].x+sdir.x,tan1[i1].y+sdir.y,tan1[i1].z+sdir.z);//+= sdir;
				tan1[i2] =	Float3(tan1[i2].x+sdir.x,tan1[i2].y+sdir.y,tan1[i2].z+sdir.z);//+= sdir;
				tan1[i3]  =	Float3(tan1[i3].x+sdir.x,tan1[i3].y+sdir.y,tan1[i3].z+sdir.z);//+= sdir;
	
				//������ĵ�a�����3������Ķ������߱���
				tan2[i1]  =	Float3(tan2[i1].x+sdir.x,tan2[i1].y+sdir.y,tan2[i1].z+sdir.z);//+= sdir;
				tan2[i2]  =	Float3(tan2[i2].x+sdir.x,tan2[i2].y+sdir.y,tan2[i2].z+sdir.z);//+= sdir;
				tan2[i3]  =	Float3(tan2[i3].x+sdir.x,tan2[i3].y+sdir.y,tan2[i3].z+sdir.z);//+= sdir;
	
				//����һ��
				triangle++;
			}
	
			for (unsigned long a = 0; a < vertexCount; a++)
			{
				Common::Vector3& n = normal[a];
				Common::Vector3& t = tan1[a];
	
	
				// Gram-Schmidt orthogonalize
// 				XMVECTOR	xn	=	XMLoadFloat3(&n);
// 				XMVECTOR	xt	=	XMLoadFloat3(&t);
// 				XMVECTOR	v	=	XMVector3Dot(xn,xt);
// 				XMVECTOR	v1	=	XMVectorMultiply(xn,v);
// 				XMVECTOR	v2	=	XMVectorSubtract(xt,v1);
// 				
// 				XMStoreFloat3(&tangent[a],XMVector3Normalize(v2));//(t - n * n.dotProduct(t)).normalisedCopy();
	
				// ����ʹ������ϵ��������ϵ�����������wԪ���С�
				//tangent[a].w = (n.crossProduct(t).dotProduct(tan2[a]) < 0.0f) ? -1.0f : 1.0f;

				Float3	tempV	=	t-n*n.Dot(t);
				tangent[a]		=	tempV.Normalize();
			}
	
			delete[] tan1;
		};
	
	//�ο���ַ��http://www.1qidu.com/?action-viewnews-itemid-14485
	
		static	GlobalSetting			g_GlobalSetting;
		GlobalSetting& GetGlobalSetting(){
			
			return g_GlobalSetting;
		}
	}
};