// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
//��ı�׼�������� DLL �е������ļ��������������϶���� AUDIOCOM_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
//�κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ 
// AUDIOCOM_API ������Ϊ�ǴӴ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifndef AUDIO_HEAD_FILE
#define AUDIO_HEAD_FILE

#pragma once
#ifndef AUDIO_EXPORT
	#ifdef AUDIO_IMPORT
		#define AUDIO_EXPORT __declspec(dllexport)
	#else
		#define AUDIO_EXPORT __declspec(dllimport)
	#endif
#endif

#ifndef AUDIO_EXPORT



#endif


#endif