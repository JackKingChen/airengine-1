#ifndef COMMON_HEAD_FILE
#define COMMON_HEAD_FILE


// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� COMMON_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// COMMON_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifndef COMMON_EXPORT
	#ifdef COMMON_IMPORT
		#define COMMON_EXPORT __declspec(dllexport)
	#else
		#define COMMON_EXPORT __declspec(dllimport)
	#endif
#endif


namespace Air{

	namespace	Common{

	}

};
#endif // COMMON_HEAD_FILE




