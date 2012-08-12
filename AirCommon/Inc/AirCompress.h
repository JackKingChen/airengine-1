//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Compress.h
 \note     
       
 \attention:
			ѹ����ѹ��
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMPRESS_HEAD_FILE
#define COMPRESS_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
namespace Air{
	
	namespace Common{
		/**	\brief	����ѹ��
		*
		*	����ѹ��
		*
		***/
		class Compress{
		public:
			/**	\brief	��ʼ��ѹ��
			*   
			*	@remarks 	��ʼ��
			*	@see		Compress
			*	@return   	bool
			*	@note
			*
			**/
			static bool Init();
			/**	\brief	�ͷ�
			*   
			*	@remarks 	�ͷ�
			*	@see		Compress
			*	@return   	bool
			*	@note
			*
			**/
			static bool Release();
	
			
			/**	\brief	ѹ��
			*   
			*	@remarks 	ѹ��
			*	@see		Compress
			*	@return   	bool
			*	@param		U8 * pSrcData
			*	@param		UInt uiSrcSize
			*	@param		U8 * pDstData
			*	@param		U32 * uiDstSize
			*	@note
			*
			**/
			static bool ToLZO(	U8*		pSrcData,
								UInt	uiSrcSize,
								U8*		pDstData,
								U32*	uiDstSize);
			/**	\brief	��ѹ��
			*   
			*	@remarks 	��ѹ��
			*	@see		Compress
			*	@return   	bool
			*	@param		U8 * pSrcData
			*	@param		UInt uiSrcSize
			*	@param		U8 * pDstData
			*	@param		U32 * uiDstSize
			*	@note
			*
			**/
			static bool FromLZO(U8*		pSrcData,
								UInt	uiSrcSize,
								U8*		pDstData,
								U32*	uiDstSize);
		};
		
	
	};
};
#endif // COMPRESS_HEAD_FILE