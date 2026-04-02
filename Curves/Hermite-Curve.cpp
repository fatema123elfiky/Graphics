//header file of the prototype of funcs , vars
#define UNICODE
#include <Windows.h>
#include <math.h>
using namespace std;


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

int** calc(int x1,int x2,int y1,int y2 ,int u1 ,int u2 , int v1 , int v2){

    int ** params = new int * [4];
    for (int i = 0; i < 4; ++i)
        params[i] = new int [2];

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 2; ++j)
            params[i][j] = 0;

    int H [4][4] {{2,1,-2,1},{-3,-2,3,-1},{0,1,0,0},{1,0,0,0}};
    int G [4][2] {{x1,y1},{u1,v1},{x2,y2},{u2,v2}};

    for (int i = 0; i < 4; ++i) // loop for first row H
        for (int j = 0; j < 2; ++j) // loop for columns
            for (int k = 0; k < 4 ; ++k)  // loop for vals
                params [i][j] = params [i][j] + (H[i][k]*G[k][j]);

    return params;
}

void DrawCurve(HDC hdc , int * X , int * Y ,COLORREF c){
    int x1 = X[0], x2 = X[3];
    int y1 = Y[0], y2 = Y[3];


    int u1 = X[1]-X[0] , v1 = Y[1]-Y[0];
    int u2 = X[3]-X[2] , v2 = Y[3]-Y[2];

    u1*=3,u2*=3,v1*=3,v2*=3;
    int ** params = calc(x1,x2,y1,y2,u1,u2,v1,v2);

    double delta = 0.00001;


    for (double t = 0; t <= 1 ; t+=delta) {
        double x = params[0][0]*t*t*t + params[1][0]*t*t + params[2][0]*t + params[3][0];
        double y = params[0][1]*t*t*t + params[1][1]*t*t + params[2][1]*t + params[3][1];
        SetPixel(hdc , round(x),round(y),c);
    }

    for (int i = 0; i < 4; ++i)
        delete[] params[i];
    delete[] params;
}


static int nums=0 , pts_x[4] , pts_y[4];
LRESULT WINAPI WndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp) // long param (x,y)(low ,high) , word param (status keyboard)
{
    HDC hdc;

    switch (mcode)
    {
        case WM_LBUTTONDOWN:
            hdc = GetDC(hwnd);
            if(nums<4) {// 0 1 2
                SetPixel(hdc,LOWORD(lp),HIWORD(lp),RGB(255,0,0));
                pts_x[nums] = LOWORD(lp), pts_y[nums] = HIWORD(lp), nums++;
            }
            if(nums==4){
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