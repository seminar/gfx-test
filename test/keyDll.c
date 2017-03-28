#include "stdafx.h"
#include<windows.h>


BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
      )
{
    return TRUE;
}
HMODULE WINAPI ModuleFromAddress(PVOID pv)                              //该函数根据内存地址，获得其所在的模块句柄
{
 MEMORY_BASIC_INFORMATION mbi;
 VirtualQuery(pv,&mbi,sizeof(mbi));
 return (HMODULE)mbi.AllocationBase;
}

LRESULT CALLBACK HookKey(int nCode,WPARAM wParam,LPARAM lParam)
{
 char sz[25];
 sprintf(sz,"%c",wParam);                                        //这个函数头文件#include<stdio.h>
 MessageBox(NULL,sz,sz,MB_OK);
 return FALSE;
}


 __declspec(dllexport) void SetHook(void)
{
 SetWindowsHookEx(WH_KEYBOARD,HookKey,ModuleFromAddress(HookKey),0);
}



