#ifndef INTERFACEUIIMAGE_HEAD_FILE
#define INTERFACEUIIMAGE_HEAD_FILE

#include "AirInterfaceUICommon.h"
namespace Air{
	
	namespace Engine{
		namespace	Render{
			class	ITexture;
		}
	
		namespace	UI{
			/**	\brief	UIͼƬ��
			*
			*	UIͼƬ��
			*
			***/
	// 		class	IImage{
	// 		public:
	// 			IImage(AString	strName,Float4	vUV){
	// 				m_strName			=	strName;
	// 				m_UVPositionSize	=	vUV;
	// 			};
	// 			AString				m_strName;				///<	ͼƬ����
	// 			Float4				m_UVPositionSize;		///<	������������
	// 		};
			//typedef		Float4		Image;	
	
	
			/**	\brief	ͼƬ��
			*
			*	ͼƬ��
			*
			***/
			class	ENGINE_EXPORT	IImageSet	:
				public	IProduct{
			public:
				typedef	std::map<AString,Float4>	ImageMap;
				typedef	ImageMap::iterator			ImageMapItr;
				typedef	ImageMap::value_type		ImageMapPair;
	
				/**	\brief	������Ϣ
				*
				*	������Ϣ
				*
				***/
				struct	Info{
					Float2	vTextureSize;
				};
			public:
				IImageSet(AString	strName,Info*	pInfo);
	
				/**	\brief	����
				*   
				*	@remarks 	����
				*	@see		IImageSet
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	�ݻ�ͼƬ��
				*   
				*	@remarks 	�ݻ�ͼƬ��
				*	@see		IImageSet
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
				/**	\brief	��ȡͼƬ����
				*   
				*	@remarks 	��ȡͼƬ����
				*	@see		Float4
				*	@return   	Float4
				*	@param		AString strName
				*	@note
				*
				**/
				Float4	GetImage(AString	strName,Float4*	pVectorInt	=	NULL);
				/**	\brief	��ȡ��������
				*   
				*	@remarks 	��ȡͼƬ����
				*	@see		IImageSet
				*	@return   	UInt
				*	@note
				*
				**/
				inline	UInt	GetImageCount(){
					return	m_mapImage.size();
				};
				/**	\brief	��ȡ����ߴ�
				*   
				*	@remarks 	��ȡ����ߴ�
				*	@see		IImageSet
				*	@return   	Float2
				*	@note
				*
				**/
				Float2				GetTextureSize();
			protected:
				ImageMap			m_mapImage;
				//Render::ITexture*	m_pTexture;
				Float2				m_vTextureSize;
			};
		}
	
	};
};
#endif // INTERFACEUIIMAGE_HEAD_FILE