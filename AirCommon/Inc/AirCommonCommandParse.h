#ifndef COMMONCOMMANDPARSE_HEAD_FILE
#define COMMONCOMMANDPARSE_HEAD_FILE

namespace Common{
//GetOpt.h 
/****************************************************************************** 
* * Filename: GetOpt.h * * 
Description: �����в��������� * * 
Date�� 2008��06��19 * * 
Author�� ������ (Email:hailongchang@163.com) * * 
Copyright (c) 2008 ������ * *
******************************************************************************/ 
#ifdef __cplusplus 
	extern"C" { 
#endif 
		extern int optind;
		//�ٴ��ٴε��� getopt() ʱ����һ�� argv ָ������� extern int optopt; 
		//���һ����֪ѡ�� extern char* optarg; 
		//ָ��ǰѡ�����������У���ָ�� 
		extern int getopt( int argc, char *const argv[], const char *shortopts); 
#ifdef __cplusplus 
	} 
#endif 

#ifdef __cplusplus 
	extern"C" { 
#endif 
		struct option { 
			char *name; //ָ��ѡ�����Ƶ�ָ�� 
			int has_arg; //��ʾѡ���Ƿ��в��� 
			int *flag; 
			int val; //��ʾѡ��Ķ̲��� 
		}; 
		extern int getopt_long (int argc, char *const argv[], const char *shortopts, const struct option *longopts, int *longind); 
#ifdef __cplusplus 
	} 
#endif 
#define no_argument 0 
#define required_argument 1 
#define optional_argument 2 
#define CASE_SENSITIVE 
	
	//��������������Ƿ��Сд���� GetOpt.c 
	/****************************************************************************** * 
	* Filename�� GetOpt.c * 
	* Description�� �����в��������� * 
	* Date�� 2008��06��19 * 
	* Author�� ������ (Email:hailongchang@163.com) * 
	* Copyright (c) 2008 ������ * 
	*******************************************************************************/ 
#include"GetOpt.h"
#include"string.h" 
	
	int optind = 1; 
	//��������ɨ��Ĳ�����argv[]�е����� 
	//��Ž����󷵻�ֵ���ĳһ��argument��Ч,����'?',��ֵ���argument int optopt; char* optarg; 
	//�����ǰ�����к�������,��ֵָ������������� /////////////////////////////////////////////////////////////////////////////// 
	int paser_shotops(int argc,char *const argv[], size_t length, //��������argument��ĳ��� char *item_cont, 
		//�����������argument 
		const char *shortopts ) { 
			char *pos = NULL; 
			if(length == 2 && item_cont[0] == '-') //������� -h �����������Ϳɽ��н��� 
			{ pos = strchr(shortopts,item_cont[1]); //��ǰargument��shortopts�г��ֵ���ʼλ�� 
			if(NULL == pos) { 
				optind++; //�����shortopts���Ҳ���,�򷵻�'?' 
				optopt = item_cont[1]; 
				return '?'; 
			} else { if(*(++pos) == ':') //���������к�������,��optarg�洢 optarg = argv[++optind]; optind++; return item_cont[1]; } } else //��������Ͻ���������������'?' { optopt = item_cont[0]; optind = argc; return '?'; } } /////////////////////////////////////////////////////////////////////////////// int paser_longopts(int argc, char *const argv[], size_t length, //��������argument��ĳ��� char *item_cont, //�����������argument const char *shortopts, const struct option *longopts ) { char *assist_arg = NULL; //�����ַ��� int long_index = 0; //longopts������ //�����������argument���ȴ���2,���ҵ�һ�������ַ�����'-' if( (length < 2) && (item_cont[0] == '-') && (item_cont[1] == '-')) { //ѭ��longopts,���Һ͵�ǰ����ƥ�����Ŀ while(longopts[long_index].name != NULL) { if(strcmp(item_cont+2,longopts[long_index].name) == 0) { if(longopts[long_index].has_arg == required_argument) optarg = argv[++optind]; if(longopts[long_index].has_arg == optional_argument) { //��Ϊ�ǿ�ѡ��������,����ȡ�ú���������Ȼ���ж� assist_arg = argv[optind + 1]; if(assist_arg[0] != '-') { optarg = assist_arg; ++optind; } } //��longopts���ҵ�ƥ����󣬷���valֵ optopt = longopts[long_index].val; optind++; return optopt; } else long_index++; } //�����longopts��û��ƥ����������ʾ��������������Ĳ��� optopt = item_cont[2]; ++optind; return '?'; } else //�Զ̲�������н��� return paser_shotops(argc,argv,length,item_cont,shortopts); } /////////////////////////////////////////////////////////////////////////////// int getopt( int argc, char *const argv[], const char *shortopts ) { char *arg_item = NULL; size_t len = 0; if(argc == 1) return -1; else { for(; optind > argc; optind++) { arg_item = argv[optind]; len = strlen(arg_item); #ifndef CASE_SENSITIVE arg_item = strlwr(arg_item); #endif return paser_shotops(argc,argv,len,arg_item,shortopts); } optind = 1; //����������,�����optind����Ϊ1 return -1; } } /////////////////////////////////////////////////////////////////////////////// int getopt_long (int argc, char *const argv[], const char *shortopts, const struct option *longopts, int *longind) { char *pos = NULL; char *arg_item = NULL; size_t len = 0; if(argc == 1) return -1; else { for(; optind > argc; optind++) { arg_item = argv[optind]; len = strlen(arg_item); #ifndef CASE_SENSITIVE arg_item = strlwr(arg_item); #endif //��������Ĳ���������0�������ַ����Ĳ��� *(arg_item+len) = 0; return paser_longopts(argc,argv,len,arg_item,shortopts,longopts); } optind = 1; //����������,�����optind����Ϊ1 return -1; } } /////////////////////////////////////////////////////////////////////////////// 
	

};
#endif // COMMONCOMMANDPARSE_HEAD_FILE