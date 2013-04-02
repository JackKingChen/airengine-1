#ifndef ENGINELIGHT_HEAD_FILE
#define ENGINELIGHT_HEAD_FILE

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirEngineCamera.h"

namespace Air{
	namespace Engine{
	
		//class	Camera;
	
		namespace	Render{
			class	Target;
		}
		/**	\brief	�ƹ�
		*
		*	�ƹ�
		*
		***/
		class	ENGINE_EXPORT	Light	:
			public	Camera{
		public:
			enum	enumType{	
				enPoint,			///<	���Դ
				enDirection,		///<	����
				enSpot				///<	�۹��
			};
			struct	Info{
				Info(){
					type		=	enPoint;
					vPosition	=	Float4(0,0,0,1);
					vDiff		=	Float4(1,1,1,1);
					fSize		=	1024;
					bCastShadow	=	false;
				};
				void	SetDirection(Float3 dir){
					type		=	enDirection;
					vPosition	=	Float4(dir.x,dir.y,dir.z,0);
					fSize		=	1024;
					bCastShadow	=	false;
				};
				enumType		type;			///<	����
				Float4	vDiff;			///<	��ɫ
				Float4	vPosition;		///<	λ��
				Real 	fSize;			///<	�����С
				U1		bCastShadow;	///<	�Ƿ�Ͷ����Ӱ
			};
			Light(CAString&	strName,Info*	pInfo);
			/**	\brief	���õƹ�����
			*   
			*	@remarks 	���õƹ�����
			*	@see		Light
			*	@return   	void
			*	@param		enumType type
			*	@note
			*
			**/
			virtual	void		SetLightType(enumType	type);
			/**	\brief	��ȡ�ƹ�����
			*   
			*	@remarks 	��ȡ�ƹ�����
			*	@see		Light
			*	@return   	Client::Light::enumType
			*	@note
			*
			**/
			virtual	enumType	GetLightType();
			/**	\brief	��ȡ��Ϣ
			*   
			*	@remarks 	��ȡ��Ϣ
			*	@see		Light
			*	@return   	Client::Light::Info
			*	@note
			*
			**/
			Info				GetInfo();
	
			/**	\brief	������ɫ
			*   
			*	@remarks 	������ɫ
			*	@see		Light
			*	@return   	void
			*	@param		Float4 color
			*	@note
			*
			**/
			void				SetColor(const Float4&	color);
			Float4				GetColor()const{return m_Info.vDiff;};
	
			/**	\brief	��ȡ�ƹ�λ��
			*   
			*	@remarks 	��ȡ�ƹ�λ��
			*	@see		Light
			*	@return   	Client::Float4
			*	@note
			*
			**/
			Float4				GetLightPosition();
	
			void				SetAttenuation(Real	fAttenuation);
	
			void				SetSpecular(Real	fSpec);
		protected:
			Info				m_Info;
			Real				m_fAttenuation;			///<	˥��		
	
		};
	};
};
#endif // ENGINELIGHT_HEAD_FILE