/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/20
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  AirCommonData.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRCOMMONDATA_HEAD_FILE
#define AIRCOMMONDATA_HEAD_FILE

#include "AirCommonHeader.h"
namespace	Air{
	namespace Common{
	
		/**	\brief	������
		*
		*	������
		*
		***/
		class	Data{
		public:
			Data():buff(0),size(0){};
			Data(U8* b,U32 s){
				if(b==NULL || s == 0){
					_ZERO(size);
					_ZERO(buff);
				}else{
					size	=	s;
					buff	=	new	U8[size];
					memcpy(buff,b,size);
				}
			};
			template	<typename	T_Type>
			Data(T_Type*	p){
				if(p!=NULL){
					size	=	sizeof(T_Type);
					buff	=	new	U8[size];
					memcpy(buff,p,size);
				}else{
					_ZERO(size);
					_ZERO(buff);
				}
			};
			~Data(){
				SAF_DA(buff);
				_ZERO(size);
			};

			Data*	Clone(){
				if(IsNull())
					return	NULL;
				return	new	Data(buff,size);
			};
			/**	\brief	�Ƿ�Ϊ��
			*   
			*	@remarks 	�Ƿ�Ϊ��
			*	@see		Data
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		IsNull(){return	(buff==NULL || size	== 0);};
			/**	\brief	��ȡ���ݳ���
			*   
			*	@remarks 	��ȡ���ݳ���
			*	@see		Data
			*	@return   	Size
			*	@note
			*
			**/
			inline	U32	GetSize(){return	size;};
			/**	\brief	��ȡ����
			*   
			*	@remarks 	��ȡ����
			*	@see		Data
			*	@return   	Common::File::Data::Buff
			*	@note
			*
			**/
			inline	U8*	GetBuff(){return	buff;};

			/**	\brief	��������ռ�
			*   
			*	@remarks 	��������ռ�
			*	@see		Data
			*	@return   	Air::Common::File::Data::Buff
			*	@param		U32 s
			*	@note
			*
			**/
			inline	U8*	ReSize(U32	s){

				SAF_DA(buff);
				size	= s;
				//���S==0����Ϊ���
				if(s==0)
					return	NULL;

				buff	=	new	U8[size];
				return buff;
			}
			inline	void	Clear(){
				SAF_DA(buff);
				_ZERO(size);
			}
			U8*				buff;					///<	����
			U32				size;					///<	��С
		};

		typedef	std::list<Data*>			DataList;
		typedef	DataList::iterator			DataListItr;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRCOMMONDATA_HEAD_FILE