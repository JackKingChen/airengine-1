#ifndef ENGINE_HEAD_FILE
#define ENGINE_HEAD_FILE
	// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
	// ��ı�׼�������� DLL �е������ļ��������������϶���� ENGINE_EXPORTS
	// ���ű���ġ���ʹ�ô� DLL ��
	// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
	// ENGINE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
	// ������Ϊ�Ǳ������ġ�
	#ifndef ENGINE_EXPORT
		#ifdef ENGINE_IMPORT
			#define ENGINE_EXPORT __declspec(dllexport)
		#else
			#define ENGINE_EXPORT __declspec(dllimport)
		#endif
	#endif




namespace Client{

	
	


};
#endif // ENGINE_HEAD_FILE

