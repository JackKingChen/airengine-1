#include "AirResourceZipPackage.h"
#include "ZZip/zzip.h"
#include "zzip/file.h"
namespace Air{
	
	namespace Engine {
	
		namespace	Resource{
			
			/// Utility method to format out zzip errors
			AString getZzipErrorDescription(zzip_error_t zzipError) 
			{
				AString errorMsg;
				switch (zzipError)
				{
				case ZZIP_NO_ERROR:
					break;
				case ZZIP_OUTOFMEM:
					errorMsg = "Out of memory.";
					break;            
				case ZZIP_DIR_OPEN:
				case ZZIP_DIR_STAT: 
				case ZZIP_DIR_SEEK:
				case ZZIP_DIR_READ:
					errorMsg = "Unable to read zip file.";
					break;            
				case ZZIP_UNSUPP_COMPR:
					errorMsg = "Unsupported compression format.";
					break;            
				case ZZIP_CORRUPTED:
					errorMsg = "Corrupted archive.";
					break;            
				default:
					errorMsg = "Unknown error.";
					break;            
				};
	
				return errorMsg;
			}
			//-----------------------------------------------------------------------
			AString ZipPackage::ProductTypeName="zip";
			ZipPackage::ZipPackage(CAString& strName):
				Package(strName),
				mZzipDir(0)
			{
			}
			//-----------------------------------------------------------------------
			U1	ZipPackage::Create()
			{
				if (!mZzipDir)
				{
					zzip_error_t zzipError;
					mZzipDir = zzip_dir_open(m_strProductName.c_str(), &zzipError);
					checkZzipError(zzipError, "opening archive");
	
					// Cache names
					ZZIP_DIRENT zzipEntry;
					while (zzip_dir_read(mZzipDir, &zzipEntry))
					{
						FileInfo info;
						AString	str = zzipEntry.d_name;
						//×ª»¯ÎªÐ¡Ð´
						Converter::ToLowerCase(str);
						// Get sizes
						info.compressedSize = static_cast<size_t>(zzipEntry.d_csize);
						info.uncompressedSize = static_cast<size_t>(zzipEntry.st_size);
	
						m_mapFileInfo[str.c_str()]	=	info;
					}
	
				}
				return	true;
			}
			//-----------------------------------------------------------------------
			U1 ZipPackage::Destroy()
			{
				if (mZzipDir)
				{
					zzip_dir_close(mZzipDir);
					mZzipDir = 0;
					m_mapFileInfo.clear();
				}
				return	true;
			}
			//-----------------------------------------------------------------------
			U32	ZipPackage::Find(CAString& filename,Data&	data)
			{
	
				// Format not used here (always binary)
				ZZIP_FILE* zzipFile = 
					zzip_file_open(mZzipDir, filename.c_str(), ZZIP_ONLYZIP | ZZIP_CASELESS);
				if (!zzipFile)
				{
					int zerr = zzip_error(mZzipDir);
					AString zzDesc = getZzipErrorDescription((zzip_error_t)zerr);
					// return null pointer
					return	NULL;
				}
	
				// Get uncompressed size too
				ZZIP_STAT zstat;
				zzip_dir_stat(mZzipDir, filename.c_str(), &zstat, ZZIP_CASEINSENSITIVE);
	
	
				
				U32 uiSize	=	zzipFile->usize;
				if(uiSize	!=	0){
					data.ReSize(uiSize);
					zzip_ssize_t r = zzip_file_read(zzipFile, (char*)data.buff, uiSize);
				}
				
				zzip_file_close(zzipFile);
				// Construct & return stream
				return uiSize;//DataStreamPtr(OGRE_NEW ZipDataStream(filename, zzipFile, static_cast<size_t>(zstat.st_size)));
	
			}
			//-----------------------------------------------------------------------
			void ZipPackage::checkZzipError(int zzipError, const AString& operation) const
			{
				if (zzipError != ZZIP_NO_ERROR)
				{
					AString errorMsg = getZzipErrorDescription(static_cast<zzip_error_t>(zzipError));
	
				}
			}
	
			void ZipPackage::FindWithPostfix( CAString& strPostfix,FindFileCallback* pListener ){
	
			}
	
	
		}
	
	}
};

