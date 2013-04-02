/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/08/20
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  AirEngineStreamReader.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRENGINESTREAMREADER_HEAD_FILE
#define AIRENGINESTREAMREADER_HEAD_FILE

#include "AirInterfaceResourceStream.h"
#include "AirCommonStreamIO.h"

namespace	Air{
	namespace Engine{
	
		class	ENGINE_EXPORT	ResourceReader	:
			public	Common::StreamReader{
		public:
			ResourceReader(Resource::IStream&	stream);
			~ResourceReader();
			/**	\brief	�ж�Stream�Ƿ���Ч
			*   
			*	@remarks 	�ж�Stream�Ƿ���Ч
			*	@see		StreamReader
			*	@return   	Air::U1
			*	@note
			*
			**/
			U1		IsStreamValid();
			/**	\brief	���³�ʼ��
			*   
			*	@remarks 	���³�ʼ��	������������
			*	@see		ResourceReader
			*	@return   	Air::U1
			*	@note
			*
			**/
			U1		ReInit();

			Resource::IStream&	m_Stream;
		};
		
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRENGINESTREAMREADER_HEAD_FILE