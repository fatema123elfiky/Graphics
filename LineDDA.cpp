//header file of the prototype of funcs , vars

//#define _UNICODE
#define UNICODE
#include <Windows.h>

void swap(int& x1,int& y1 ,int& x2,int& y2){
    int tmp =x1;x1=x2;x2=tmp;
    tmp=y1;y1=y2;y2=tmp;

}

int Round(double x){

    return (int)(x+0.5);
}
void LineDDA(HDC hdc , int x1 ,int y1 , int x2 , int y2, COLORREF c){
    int dx =x2-x1,dy=y2-y1;
    if(abs(dx) >= abs(dy)){
         if(x1>x2)
             swap(x1,y1,x2,y2);
         int x =x1;double y =y1;
         SetPixel(hdc,x1,y1,c);
         double m = (double)dy/dx;
         while(x<x2){
             x++;
             y+=m;
             SetPixel(hdc,x,Round(y),c);
         }
    }else{
        if(y1>y2)
            swap(x1,y1,x2,y2);
        int y =y1;double x =x1;
        SetPixel(hdc,x1,y1,c);
        double m = (double)dx/dy;
        while(y<y2){
            y++;
            x+=m;
            SetPixel(hdc,Round(x),y,c);
        }
    }
}



LRESULT WINAPI WndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp) // long param (x,y)(low ,high) , word param (status keyboard)
{
    HDC hdc;
    static int x,y;
    switch (mcode)
    {
        case WM_LBUTTONDOWN:

            x= LOWORD(lp);
            y= HIWORD(lp);

            break;
        case WM_LBUTTONUP:
            hdc= GetDC(hwnd);
            LineDDA(hdc,x,y, LOWORD(lp), HIWORD(lp),RGB(255,0,0));
            ReleaseDC(hwnd,hdc);
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