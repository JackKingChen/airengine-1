#ifndef RENDER_HEAD_FILE
#define RENDER_HEAD_FILE

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� RENDER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// RENDER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifndef	RENDER_EXPORT
	#ifdef RENDER_IMPORT
		#define RENDER_EXPORT __declspec(dllexport)
	#else
		#define RENDER_EXPORT __declspec(dllimport)
	#endif
#endif

#endif // RENDER_HEAD_FILE


