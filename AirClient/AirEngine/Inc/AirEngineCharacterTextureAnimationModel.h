#ifndef ENGINECHARACTERTEXTUREANIMATIONMODEL_HEAD_FILE
#define ENGINECHARACTERTEXTUREANIMATIONMODEL_HEAD_FILE

#include "AirEngineCharacterAnimationModel.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Render{
			class	ITexture;
		}
	
	
		namespace	Character{
			namespace	Animation{
				/**	\brief	���ڶ�������ʰȡ�Ķ���ģ����
				*
				*	���ڶ�������ʰȡ�Ķ���ģ����
				*
				***/
				class	TextureModel	:
					public	Model{
				public:
					TextureModel(CAString&	strName,Info* pInfo);
	
	
					/**	\brief	����
					*   
					*	@remarks 	����
					*	@see		Model
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1				Create();
					/**	\brief	�ݻ�
					*   
					*	@remarks 	�ݻ�
					*	@see		Model
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1				Destroy();
					/**	\brief	����
					*   
					*	@remarks 	����
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual void			Updata();
					/**	\brief	Ӳ����Ⱦ
					*   
					*	@remarks 	Ӳ����Ⱦ
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual	void			RenderHardWare();
				protected:
					Render::Texture*		m_pBoneTexture;		///<	������������
					Render::Texture*		m_pTempBoneTexture;	///<	����������������
				};
				/**	\brief	��������ʰȡ��ģ�͹���
				*
				*	��������ʰȡ��ģ�͹���
				*
				***/
				class	TextureModelFactory	:
					public	IFactory{
				public:
					TextureModelFactory();
	
					/**	\brief	������Ʒ
					*   
					*	@remarks 	������Ʒ
					*	@see		TextureModelFactory
					*	@return   	IProduct*
					*	@param		CAString& strName
					*	@param		IFactoryParamList * lstParam
					*	@note
					*
					**/
					virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
				};
			}
		}
	
	};
};
#endif // ENGINECHARACTERTEXTUREANIMATIONMODEL_HEAD_FILE