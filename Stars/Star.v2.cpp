//header file of the prototype of funcs , vars

//#define _UNICODE
#define UNICODE
#include <Windows.h>
#include <iostream>
#include <math.h>

using namespace std;

void Swap(int& x1,int& y1 ,int& x2,int& y2){
    int tmp =x1;x1=x2;x2=tmp;
    tmp=y1;y1=y2;y2=tmp;

}

int Round(double x){

    return (int)(x+0.5);
}

double getSlope(int x1 ,int y1,int x2,int y2){

    if(x2==x1)
        return 1e9;
    return double(y2-y1)/(x2-x1);
}

double getC(int x ,int y ,double m){
    return y - (m*x);
}
pair<int,int> getIntersection(double c1,double c2 ,double m1,double m2){
    double x = (c1-c2)/(m2-m1);
    double y = c1+ (m1*x);

    return {Round(x), Round(y)};
}

void LineDDA(HDC hdc , int x1 ,int y1 , int x2 , int y2, COLORREF c){
    int dx =x2-x1,dy=y2-y1;
    if(abs(dx) >= abs(dy)){
        if(x1>x2)
            Swap(x1,y1,x2,y2);
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
            Swap(x1,y1,x2,y2);
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
    HDC hdc = GetDC(hwnd);
    static int X[5],Y[5],idx=0;

    switch (mcode)
    {
        case WM_LBUTTONDOWN:

            if(idx<=4) {

                X[idx] = LOWORD(lp), Y[idx] = HIWORD(lp);
                SetPixel(hdc,X[idx],Y[idx],RGB(255,0,0));
            }
            if(idx==4){
                /*Try to sort it*/
                double cx = 0, cy = 0;

                for(int i = 0; i < 5; i++)
                    cx += X[i], cy += Y[i];

                cx /= 5,cy /= 5;
                double angle[5];

                for(int i = 0; i < 5; i++)
                    angle[i] = atan2(Y[i] - cy, X[i] - cx);

                for(int i = 0; i < 5; i++){
                    for(int j = i+1; j < 5; j++){
                        if(angle[i] > angle[j]){
                            swap(angle[i], angle[j]);
                            swap(X[i], X[j]);
                            swap(Y[i], Y[j]);
                        }
                    }
                }

                double IntersectionX [5] ,IntersectionY [5];

                //first intersection
                double m1 = getSlope(X[0],Y[0],X[2],Y[2]);
                double m2 = getSlope(X[1],Y[1],X[4],Y[4]);

                double c1 = getC(X[0],Y[0],m1);
                double c2 = getC(X[1],Y[1],m2);

                pair<int,int>point = getIntersection(c1,c2,m1,m2);
                IntersectionX[0]=point.first,IntersectionY[0]=point.second;


                //second intersection
                m1 = getSlope(X[0],Y[0],X[2],Y[2]);
                m2 = getSlope(X[1],Y[1],X[3],Y[3]);

                c1 = getC(X[0],Y[0],m1);
                c2 = getC(X[1],Y[1],m2);

                point = getIntersection(c1,c2,m1,m2);
                IntersectionX[1]=point.first,IntersectionY[1]=point.second;

                //third intersection
                m1 = getSlope(X[2],Y[2],X[4],Y[4]);
                m2 = getSlope(X[3],Y[3],X[1],Y[1]);

                c1 = getC(X[2],Y[2],m1);
                c2 = getC(X[1],Y[1],m2);

                point = getIntersection(c1,c2,m1,m2);
                IntersectionX[2]=point.first,IntersectionY[2]=point.second;


                //fourth intersection
                m1 = getSlope(X[2],Y[2],X[4],Y[4]);
                m2 = getSlope(X[3],Y[3],X[0],Y[0]);

                c1 = getC(X[2],Y[2],m1);
                c2 = getC(X[0],Y[0],m2);

                point = getIntersection(c1,c2,m1,m2);
                IntersectionX[3]=point.first,IntersectionY[3]=point.second;


                //fifth intersection
                m1 = getSlope(X[0],Y[0],X[3],Y[3]);
                m2 = getSlope(X[1],Y[1],X[4],Y[4]);

                c1 = getC(X[0],Y[0],m1);
                c2 = getC(X[1],Y[1],m2);

                point = getIntersection(c1,c2,m1,m2);
                IntersectionX[4]=point.first,IntersectionY[4]=point.second;


                // Now draw 10 lines
                LineDDA(hdc,X[0],Y[0],IntersectionX[0],IntersectionY[0], RGB(255,0,0));
                LineDDA(hdc,X[1],Y[1],IntersectionX[0],IntersectionY[0], RGB(0,255,0));

                LineDDA(hdc,X[1],Y[1],IntersectionX[1],IntersectionY[1], RGB(0,0,255));
                LineDDA(hdc,X[2],Y[2],IntersectionX[1],IntersectionY[1], RGB(255,255,0));

                LineDDA(hdc,X[2],Y[2],IntersectionX[2],IntersectionY[2], RGB(255,0,255));
                LineDDA(hdc,X[3],Y[3],IntersectionX[2],IntersectionY[2], RGB(0,255,255));

                LineDDA(hdc,X[3],Y[3],IntersectionX[3],IntersectionY[3], RGB(255,0,0));
                LineDDA(hdc,X[4],Y[4],IntersectionX[3],IntersectionY[3], RGB(0,255,0));

                LineDDA(hdc,X[4],Y[4],IntersectionX[4],IntersectionY[4], RGB(0,0,255));
                LineDDA(hdc,X[0],Y[0],IntersectionX[4],IntersectionY[4], RGB(255,255,0));



            }
            idx++;
            idx=idx%5;
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