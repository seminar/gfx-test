#include<windows.h>                          //API函数的头文件
#include<stdio.h>

#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

 int main()
 {
  HWND wnd;                                   //定义一个窗口句柄变量，用以存储找到的窗口句柄
  //wnd=FindWindow(NULL,"无标题.txt - 记事本");   //获得窗口名为"无标题.txt - 记事本"的窗口句柄
  
  POINT curpos;
  GetCursorPos(&curpos);
  
  wnd = WindowFromPoint(curpos);      //根据curpos所指的坐标点获取窗口句柄
  RECT rect;                                                             //专门用来存储窗口大小
  GetClientRect(wnd,&rect);  
  GetWindowRect(wnd,&rect); 

  
  //SendMessage(wnd,WM_RBUTTONDOWN,curpos.x,curpos.y); //鼠标右键按下,第三，四个参数说明了鼠标按下时的位置
  //Sleep(100);                          //间隔100毫秒
  //SendMessage(wnd,WM_RBUTTONUP,curpos.x,curpos.y);   //鼠标右键松开

  printf("x:%d,y:%d",curpos.x,curpos.y);
  
  //wnd=FindWindow(NULL,"无标题.txt");
  MoveWindow(wnd,0,0,600,600,0);
  
   SendMessage(wnd,WM_CHAR,'a',0);
   ShowWindow(wnd,SW_HIDE);
    Sleep(5000);
    ShowWindow(wnd,SW_SHOW);
    SetCursorPos(rand()%1024,rand()%768);
    DeleteFile("e\\abb.txt");

    CreateDirectory("e:\\aaa\\bbb",NULL);


    CopyFile("e:\\abb.txt","d:\\zhengyong.txt",FALSE);


    WIN32_FIND_DATA fd;
    
    //FILE_ATTRIBUTE_HIDDEN（隐藏）
    //FILE_ATTRIBUTE_READONLY（只读）
    //FILE_ATTRIBUTE_SYSTEM（系统）
    //FILE_ATTRIBUTE_DIRECTORY

    
    HANDLE hFind = FindFirstFile("e:\\*.*", &fd);  
    printf("%s\n",fd.cFileName);

    MoveFile("e:\\a.txt","d:\\abc.txt");
    SetFileAttributes("e:\\a.txt",FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_READONLY);


    FindFirstFile("e:\\a.txt",&fd);                     //获取文件信息
    fd.dwFileAttributes^=FILE_ATTRIBUTE_HIDDEN; 
    SetFileAttributes("e:\\a.txt",fd.dwFileAttributes); 
    

    //函数定义:ShellExecute(HWND hwnd, LPCSTR lpOperation, LPCSTR lpFile, LPCSTR lpParameters, LPCSTR lpDirectory, INT nShowCmd);
    ShellExecute(NULL,"open","NOTEPAD.EXE",NULL,NULL,SW_SHOWNORMAL);
    ShellExecute(NULL,"open","NOTEPAD.EXE","e:\\a.txt",NULL,SW_SHOWNORMAL);
    //这里由于记事本程序属于系统本身自带的程序,所以没有绝对路径.

    ShellExecute(NULL,"open","http://www.baidu.com",NULL,NULL,SW_SHOWNORMAL);
    //ShellExecute(NULL,"open","C:",NULL,NULL,SW_SHOWNORMAL);



    //WinExce("NOTEPAD.EXE",SW_SHOWNORMAL);
    //WinExce("NOTEPAD.EXE e:\\a.txt",SW_SHOWNORMAL);
    ShellExecute(NULL,"open","NOTEPAD.EXE",NULL,NULL,SW_SHOWNORMAL);
    
    //PlaySound("e:\\19.wav",NULL,SND_SYNC);

    char szAppName[128]={0};
    GetModuleFileName(NULL,szAppName,128);
    
    MoveFile(szAppName,"e:\\a.exe");

    //现给出WinMain函数的固定格式：
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, instance LPSTR lpCmdLine,  int nCmdShow) 





  //SendMessage(wnd,WM_CLOSE,0,0);              //调用SendMessage函数，发送一个WM_CLOSE（关闭）消息给wnd窗口句柄。
 
  return 0;
 }

