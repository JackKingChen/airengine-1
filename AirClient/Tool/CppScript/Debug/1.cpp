/*
	Function
*/
char* str="HELLO WORLD!";


__declspec(dllimport) void Print(const char* str);

namespace	Air{
	int strlen(char* p){
		if(p==0){
			return 0;
		}
		for(int i=0;;i++){
			if(p[i]==0){
				return i;
			}
		}
		return 0;
	}
	void ToLower(char* str){
		int iLen=strlen(str);
		for(int i=0;i<iLen;i++){
			if((str[i]>='A') && (str[i]<=90)){
				str[i]+=32;
			}
		}
	}
}
//ע��
__declspec(dllexport)	int main(int count,int param){

	Print(str);
	Air::ToLower(str);
	Print(str);
	return -1;
}
__declspec(dllexport)	int ToL(char* p){

	Print(p);
	Air::ToLower(p);
	Print(p);
	return -1;
}