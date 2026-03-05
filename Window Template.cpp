//header file of the prototype of funcs , vars

//#define _UNICODE
#define UNICODE
#include <Windows.h>

// src code --> compile --> obj code + symbol table  --> linker --> .exe --> loader "static linked"
// api functions (dynamic link library) (load in memory not in .exe)
// compiler do stub


//                      handle of window that gets msg , msg
LRESULT WINAPI WndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp) // long param (x,y)(low ,high) , word param (status keyboard)
{
    HDC hdc;
    int x,y;
    switch (mcode)
    {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            x= LOWORD(lp),y= HIWORD(lp);
            Ellipse(hdc, x-100, y-100, x+500, y+400);
            ReleaseDC(hwnd, hdc);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd); break;
        case WM_DESTROY:
            PostQuitMessage(0); break;
        default: return DefWindowProc(hwnd, mcode, wp, lp);
    }
    return 0;
}




//Entry point (as int main) loader calls WinMain

// takes 4 parameters h->handle , N instance (variable to know some metadata about that instance )
//					  p -> previous instance (h, p linked as linkedlist)
//					  cmd (c) -> paramters that take it to open certain application (Long Pointer to String)
//					  nsh -> window maximized (how to appear window with that value)
// 	APIENTRY == WINAPI (Call Convention) pascal , c convention call push pop, standard call push

// to let a window appear --> any rectangular area

int APIENTRY WinMain(HINSTANCE h, HINSTANCE p, LPSTR c, int nsh)
{
    // my own window class
    WNDCLASS wc;//structure contains some fields

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // background , color of background
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);// mouse from os , id mouse "arrow"
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);//
    wc.hInstance = h;
    wc.lpfnWndProc = WndProc;//dispatch
    wc.lpszClassName = L"MyClass";// os view
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;//resizing->redraw


    RegisterClass(&wc);// save that class in your os
    HWND hwnd = CreateWindow(L"MyClass", L"Hello World",
                             WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, h, 0);
    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);
    MSG msg;
    // message --> os take the interrupt of the hw and put it in the msg
    // as clicks

    //semi understand
    // wndproc called by msg
    while (GetMessage(&msg, NULL, 0, 0) > 0) // wait msg
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);//target send msg to it
    }
    // pop paras , address
    return 0;


}