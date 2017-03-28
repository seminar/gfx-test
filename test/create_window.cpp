#include "stdio.h"
#include  "winsock2.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#if 0
 typedef struct _WNDCLASS { 
      UINT style;            //描述类风格
      WNDPROC lpfnWndProc;   //窗口处理函数
      int cbClsExtra;        //表示窗口类结构之后分配的额外的字节数。系统将该值初始化为0
      int cbWndExtra;        //表示窗口实例之后分配的额外的字节数。系统将该值初始化为0
      HINSTANCE hInstance;   // 应用程序实例句柄由WinMain函数传进来 
      HICON hIcon;           //窗口图标句柄 
      HCURSOR hCursor;       //窗口光标句柄
      HBRUSH hbrBackground;  //画刷句柄
      LPCTSTR lpszMenuName;  //窗口菜单名
      LPCTSTR lpszClassName; //窗口类名
      } WNDCLASS, *PWNDCLASS; 
#endif


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
        return 0;


 }

/*
                      WinSunProc函数的四个参数，分别对应着SendMessage函数四个参数，详情参见SendMessage函数参数解释。
                      MSG类型解释 ：
                      结构定义：
                       typedef struct tagMSG 
                              {
                               HWND hwnd;    //hwnd表示消息将要发送给的窗口句柄
                              UINT message;  //消息类型，如WM_WMCLOSE,WM_CHAR,WM_LBUTTONDOWN,参见消息表
                              WPARAM wParam; //消息附带信息，取值的意思具体依据消息类型而定
                              LPARAM lParam; //消息附带信息，取值的意思具体依据消息类型而定
                              DWORD time;    //消息的发送时间，不常用
                              POINT pt;      //消息发送时，鼠标所在的位置，不常用
                              }MSG; 
                      大家试着把上面的例子运行一遍，然后关掉窗口，再运行一遍，是不是出错了，因为前一个程序虽然窗口关闭了，但进程还在运行，还记得那个循环语句吗？while(GetMessage(&msg,NULL,0,0))就是这个。只要条件成立，进程就会一直运行下去。如何让这个循环结束呢？用 PostQuitMessage(0); 这个语句就行了，参数0表示给自身窗口发送一个退出消息，当GetMessage函数接到PostQuitMessage函数发出的消息后，就会返回0值。
                      如在窗口过程函数中处理窗口关闭WM_CLOSE消息:if(uMsg==WM_CLOSE）PostQuitMessage(0); 这样只要一关闭窗口，它的进程也会结束。
                      接下来解释一下CreateWindow函数参数的意思,函数定义
                       HWND CreateWindow(LPCTSTR lpClassName, //窗口类名，应与WNDCLASS结构里的成员lpszClassName一致
                       LPCTSTR lpWindowName,,                 //窗口标题名
                       DWORD dwStyle，                        //窗口的风格，取值参见表Style
                       int x,
                       int y,                                 //x,y表示所创建窗口左上角位置
                       int nWidth,
                       int nHeight,                           //nWidth,nHeight表示窗口的宽高
                       HWND hWndParent,                       //父窗口句柄，如果不是子窗口，这里取值为NULL
                       HMENU hMenu,                           //菜单句柄，没菜单的话，取NULL值
                       HANDLE hlnstance,                      //对应着WinMain函数的第一个参数
                       LPVOID lpParam);                       //NULL
                      表Style：（参考：百度）
                      WS_BORDER：创建一个单边框的窗口。 　　
                      WS_CAPTION：创建一个有标题框的窗口（包括WS_BODER风格）。
                      WS_CHILD：创建一个子窗口。这个风格不能与WS_POPUP风格合用。
                      WS_CHLDWINDOW：与WS_CHILD相同。
                      WS_CLIPCHILDREN:当在父窗口内绘图时，排除子窗口区域。在创建父窗口时使用这个风格。 　　
                      WS_CLlPBLINGS；排除子窗口之间的相对区域，也就是，当一个特定的窗口接收到WM_PAINT消息时，WS_CLIPSIBLINGS 风格将所有层叠窗口排除在绘图之外，只重绘指定的子窗口。如果未指定WS_CLIPSIBLINGS风格，并且子窗口是层叠的，则在重绘子窗口的客户区时，就会重绘邻近的子窗口。
                      WS_DISABLED:创建一个初始状态为禁止的子窗口。一个禁止状态的窗口不能接受来自用户的输入信息.
                      WS_DLGFRAME:创建一个带对话框边框风格的窗口。这种风格的窗口不能带标题条。
                      WS_GROUP:指定一组控制的第一个控制。这个控制组由第一个控制和随后定义的控制组成，自第二个控制开始每个控制，具有WS_GROUP风格，每个组的第一个控制带有WS_TABSTOP风格，从而使用户可以在组间移动。用户随后可以使用光标在组内的控制间改变键盘焦点。 　　
                      WS_HSCROLL：创建一个有水平滚动条的窗口。 　　
                      WS_ICONIC：创建一个初始状态为最小化状态的窗口。
                      与WS_MINIMIZE风格相同。 　　
                      WS_MAXIMIZE：创建一个初始状态为最大化状态的窗口。 　　
                      WS_MAXIMIZEBOX：创建一个具有最大化按钮的窗口。该风格不能与WS_EX_CONTEXTHELP风格同时出现，同时必须指定WS_SYSMENU风格。 　　
                      WS_OVERLAPPED:产生一个层叠的窗口。一个层叠的窗口有一个标题条和一个边框。与WS_TILED风格相同。 　　WS_OVERLAPPEDWINDOW：创建一个具有WS_OVERLAPPED，WS_CAPTION，WS_SYSMENU WS_THICKFRAME，WS_MINIMIZEBOX，WS_MAXIMIZEBOX风格的层叠窗口，与WS_TILEDWINDOW风格相同。 　　WS_POPUP；创建一个弹出式窗口。该风格不能与WS_CHLD风格同时使用。 　　
                      WS_POPUWINDOW：创建一个具有WS_BORDER，WS_POPUP,WS_SYSMENU风格的窗口，WS_CAPTION和WS_POPUPWINDOW必须同时设定才能使窗口某单可见。 　　
                      WS_SIZEBOX：创建一个可调边框的窗口，与WS_THICKFRAME风格相同。 　　
                      WS_SYSMENU：创建一个在标题条上带有窗口菜单的窗口，必须同时设定WS_CAPTION风格。 　　
                      WS_TABSTOP：创建一个控制，这个控制在用户按下Tab键时可以获得键盘焦点。按下Tab键后使键盘焦点转移到下一具有WS_TABSTOP风格的控制。 　　
                      WS_THICKFRAME：创建一个具有可调边框的窗口，与WS_SIZEBOX风格相同。 　　
                      WS_TILED：产生一个层叠的窗口。一个层叠的窗口有一个标题和一个边框。
                      与WS_OVERLAPPED风格相同。 　　
                      WS_TILEDWINDOW:创建一个具有WS_OVERLAPPED，WS_CAPTION，WS_SYSMENU， WS_THICKFRAME，WS_MINIMIZEBOX，WS_MAXMIZEBOX风格的层叠窗口。与WS_OVERLAPPEDWINDOW风格相同。 　　
                      WS_VISIBLE创建一个初始状态为可见的窗口。 　　
                      WS_VSCROLL：创建一个有垂直滚动条的窗口。
*/
