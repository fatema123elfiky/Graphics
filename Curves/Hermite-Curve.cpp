//header file of the prototype of funcs , vars
#define UNICODE
#include <Windows.h>

/**
 * Plan as it goes
 * First get Four control points --> done
 * 2 points are used properly
 * 2 another points used to get the slope
 * then get the vector of that slope
 * then prepare H matrix ,  G matrix then assign vars
 * Now your equation is prepared
 * Finally loop to increment t by 0.0001
 * */

void DrawCurve(HDC hdc , int *pts_x , int * pts_y ,COLORREF c){

}


static int nums=0 , pts_x[4] , pts_y[2];
LRESULT WINAPI WndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp) // long param (x,y)(low ,high) , word param (status keyboard)
{
    HDC hdc;

    switch (mcode)
    {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            if(nums<4)
                pts_x[nums]= LOWORD(lp),pts_y[nums]= HIWORD(lp),nums++;
            else {
                DrawCurve(hdc,pts_x,pts_y,RGB(255,0,0));
                nums = 0;
            }
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