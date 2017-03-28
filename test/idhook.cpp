#include "stdio.h"
#include  "winsock2.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

LRESULT CALLBACK WinSunProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
if(uMsg==WM_LBUTTONDOWN) MessageBox(NULL,"ffs","test",MB_OK);  //处理鼠标按下消息，弹出消息框
return DefWindowProc(hwnd,uMsg,wParam,lParam);                         //未处理的消息通过DefWindowProc函数交给系统处理
}

  int APIENTRY WinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR     lpCmdLine,
                      int       nCmdShow)
 {
     WNDCLASS wndcls;                                           //定义一个存储窗口信息WNDCLASS变量
        wndcls.cbClsExtra=0;                                       //默认为0
        wndcls.cbWndExtra=0;                                       //默认为0
        //wndcls.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH);   //背景画刷
        wndcls.hCursor=LoadCursor(NULL,IDC_ARROW);                 //光标
        wndcls.hIcon=LoadIcon(NULL,IDI_ERROR);                     //窗口图标
        wndcls.hInstance=hInstance;                                //应用程序实例句柄由WinMain函数传进来 
        wndcls.lpfnWndProc=WinSunProc;                             //窗口消息处理函数
        wndcls.lpszClassName="windowclass";                        //窗口类名
        wndcls.lpszMenuName=NULL;                                  //窗口菜单名，没有菜单，为NULL
        wndcls.style=CS_HREDRAW | CS_VREDRAW;                      //窗口类型，CS_HREDRAW和CS_VERDRAW 表明
      //当窗口水平方向垂直方向的宽度变化时重绘整个窗口
        RegisterClass(&wndcls);                                    //把窗口信息提交给系统，注册窗口类
        HWND hwnd;                                                 //用以存储CreateWindow函数所创建的窗口句柄
         hwnd=CreateWindow("windowclass","first windows", 
        WS_OVERLAPPEDWINDOW,0,0,600,400,NULL,NULL,hInstance,NULL); //创建窗口
         ShowWindow(hwnd,SW_SHOWNORMAL);                           //窗口创建完了，显示它
         UpdateWindow(hwnd);                                       //更新窗口，让窗口毫无延迟的显示
         MSG msg;                                                  //消息结构类型
         while(GetMessage(&msg,NULL,0,0))                          //获取消息
         {
          //TranslateMessage(&msg);                                //此函数用于把键盘消息(WM_KEYDOWN,WM_KEYUP)转换成字符消息WM_CHAR
          DispatchMessage(&msg);                                   //这个函数调用窗口过程处理函数，并把MSG里的信息处理后传给过程函数的四个参数
       }


         
         HMODULE hMod=LoadLibrary("KeyDll.dll");
         typedef void(*pSetHook)(void);
         pSetHook SetHook=(pSetHook)GetProcAddress(hMod,"SetHook");
         SetHook();
         while(1)
         {
          Sleep(1000);                                                  //避免程序结束，自动释放动态链接库
         }

        return 0;


 }
