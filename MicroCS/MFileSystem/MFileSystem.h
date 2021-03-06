#ifndef MFileSystem_h__
#define MFileSystem_h__
#include "MFileSystemCommon.h"


class MFile;
class MClient;

class MFileSystem	:	
	public	Air::Common::IFactoryManager,
	public	Singleton<MFileSystem>
	
	
{
public:
	MFileSystem();
	virtual	~MFileSystem();

	U1				Initialization();
	U1				Release();
	void			Update(U32 uiTickTime);


	MFile*			CreateMFile(U64	id);

	void			ScanProcess(const TCHAR* strName);
	FileInfo&		GetFileInfo(U32 idx);
	U32				GetFileCount();

	void			OnDownloadComplate();
protected:
	void			LoadFileIndex();
protected:
	STD_MAP<U32,MClient*>	m_mapClient;
	Air::FileMapping*		m_pShareFileInfo;
	FileInfoMap				m_mapFileInfo;
	HANDLE					m_hFileSystemInit;
	Air::Common::Event		m_WaitDownload;
};
#endif // MFileSystem_h__
