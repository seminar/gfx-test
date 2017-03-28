#include<windows.h>
#include<mmsystem.h>                 //PlaySound函数的头文件
#pragma comment(lib, "winmm.lib")    //链接库，PlaySound函数必须使用

#define MP3  "c:\Program Files (x86)\KuGou\KGMusic\KuGou.exe"
#define TEXT "Notepad.exe"
#define MOVIE  "C:\Program Files (x86)\Windows Media Player\wmplayer.exe"

int main(char argc,char* argv[]) 
{
char path[1024];
if(argc<2)
    return 2;

printf("%s \n  %s",argv[0],argv[1]);
memcpy(path,argv[1],strlen(argv[1]));

char tool[1024];
memcpy(tool,MOVIE,strlen(MOVIE));
ShellExecute(NULL,"open",tool,path,NULL,SW_SHOWNORMAL);


//PlaySound("e:\\19.wav",NULL,SND_SYNC);
return 0;
}

