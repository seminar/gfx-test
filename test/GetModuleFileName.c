#include<windows.h>
int main()
{
char szAppName[128]={0};
GetModuleFileName(NULL,szAppName,128);
MoveFile(szAppName,"e:\\a.exe");
return 0;
}

