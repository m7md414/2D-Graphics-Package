#include<iostream>
using namespace std;
#include<cmath>
#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
int Round(double x)
{
    return int(x+0.5);
}
bool clipping(int xc,int yc,int r,int x,int y)
{
    if((((x-xc)*(x-xc))+((y-yc)*(y-yc)))<=r*r)
        return true;
    else
        return false;
}
void Draw4Points(HDC hdc,int xcen,int ycen,int r,int xc,int yc,int x,int y,COLORREF color,int k)
{
    if(k==1)
    {
        if(clipping(xcen,ycen,r,xc+x,yc+y))
            color=RGB(0,0,255);
        else
            color=RGB(255,0,0);
        SetPixel(hdc,xc+x,yc+y,color);
        if(clipping(xcen,ycen,r,xc-x,yc+y))
            color=RGB(0,0,255);
        else
            color=RGB(255,0,0);
        SetPixel(hdc,xc-x,yc+y,color);
        if(clipping(xcen,ycen,r,xc+y,yc+x))
            color=RGB(0,0,255);
        else
            color=RGB(255,0,0);
        SetPixel(hdc,xc+y,yc+x,color);
        if(clipping(xcen,ycen,r,xc-y,yc+x))
            color=RGB(0,0,255);
        else
            color=RGB(255,0,0);
        SetPixel(hdc,xc-y,yc+x,color);
    }
    else
    {
        SetPixel(hdc,xc+x,yc+y,color);
        SetPixel(hdc,xc-x,yc+y,color);
        SetPixel(hdc,xc+y,yc+x,color);
        SetPixel(hdc,xc-y,yc+x,color);
    }
}
void LinePar(HDC hdc,int xc,int yc,int r,int x1,int y1,int x2,int y2,COLORREF color,int k)
{
    for(double t=0; t<=1; t+=0.001)
    {
        int x=Round(x1+(x2-x1)*t);
        int y=Round(y1+(y2-y1)*t);
        if(k==1)
        {
            if(clipping(xc,yc,r,x,y))
                color=RGB(0,0,255);
            else
                color=RGB(255,0,0);
        }
        SetPixel(hdc,x,y,color);
    }
}
void CirclePolar(HDC hdc,int xcen,int ycen,int R,int xc,int yc,int R2,COLORREF color,int k)
{
    double dtheta=1.0/R2;
    for(double theta=0; theta<6.28; theta+=dtheta)
    {
        int x=Round(xc+R2*cos(theta));
        int y=Round(yc+R2*sin(theta));
        if(k==1)
        {
            if(clipping(xcen,ycen,R,x,y))
                color=RGB(0,0,255);
            else
                color=RGB(255,0,0);
        }
        SetPixel(hdc,x,y,color);
    }
}
void CircleWindow(HDC hdc,int xc,int yc,int R,COLORREF color)
{
    double dtheta=1.0/R;
    for(double theta=0; theta<6.28; theta+=dtheta)
    {
        int x=Round(xc+R*cos(theta));
        int y=Round(yc+R*sin(theta));
        SetPixel(hdc,x,y,color);
    }
}

void HalfCircleMidpoint(HDC hdc,int xcen,int ycen,int r,int xc,int yc, int R,COLORREF color,int k)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    Draw4Points(hdc,xcen,ycen,r,xc,yc,x,y,color,k);
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {
            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        Draw4Points(hdc,xcen,ycen,r,xc,yc,x,y,color,k);
    }
}

/*  This function is called by the Windows function DispatchMessage()  */
int c,k=0;
int xs,xc,xe,ys,yc,ye,r,R;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {

    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    case WM_LBUTTONDBLCLK:
        cout<<"Enter your choice"<<endl;
        cout<<"1-Line"<<endl;
        cout<<"2-Circle"<<endl;
        cout<<"3-Curve"<<endl;
        cout<<"4-New window"<<endl;
        cout<<"5-Close window"<<endl;
        cin>>c;
    case WM_RBUTTONDOWN:
        xs=LOWORD(lParam);
        ys=HIWORD(lParam);
        break;
    case WM_LBUTTONDOWN:
        xe=LOWORD(lParam);
        ye=HIWORD(lParam);
        if(c==1)
        {
            LinePar(hdc,xc,yc,R,xs,ys,xe,ye,RGB(255,0,0),k);
        }
        else if(c==2)
        {
            r=sqrt(((xe-xs)*(xe-xs))+((ye-ys)*(ye-ys)));
            CirclePolar(hdc,xc,yc,R,xs,ys,r,RGB(255,0,0),k);
        }
        else if(c==3)
        {
            r=sqrt(((xe-xs)*(xe-xs))+((ye-ys)*(ye-ys)));
            HalfCircleMidpoint(hdc,xc,yc,R,xs,ys,r,RGB(255,0,0),k);
        }
        else if(c==4)
        {
            r=sqrt(((xe-xs)*(xe-xs))+((ye-ys)*(ye-ys)));
            R=r;
            xc=xs;
            yc=ys;
            CircleWindow(hdc,xs,ys,r,RGB(0,0,0));
            k=1;
        }
        else if(c==5)
            //SendMessage(hwnd,WM_CLOSE,0,0);
            DestroyWindow(hwnd);
        break;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
