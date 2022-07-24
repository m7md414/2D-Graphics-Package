#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

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
    return (int) x+0.5;
}
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx=x2-x1, dy=y2-y1;
    double dt= 1.0/max(abs(dx),abs(dy));
    for(double t=0; t<=1; t+=dt)
    {
        int x=Round(x1+t*dx);
        int y=Round(y1+t*dy);
        SetPixel(hdc,x,y,c);
    }
}
union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)
        out.left=1;
    else if(x>xright)
        out.right=1;
    if(y<ytop)
        out.top=1;
    else if(y>ybottom)
        out.bottom=1;
    return out;
}
void leftIntersect(double xstart,double ystart,double xend,double yend,int x,double *xi,double *yi)
{
    *xi=x;
    *yi=ystart+(x-xstart)*(yend-ystart)/(xend-xstart);
}
void rightIntersect(double xstart,double ystart,double xend,double yend,int y,double *xi,double *yi)
{
    *yi=y;
    *xi=xstart+(y-ystart)*(xend-xstart)/(yend-ystart);
}

void CohenSuthLineClipping(HDC hdc,int x1,int y1,int x2,int y2,int xleft,int ytop,int xright,int ybottom,COLORREF c)
{
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                leftIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out1.top)
                rightIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out1.right)
                leftIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                rightIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x1=xi;
            y1=yi;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                leftIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out2.top)
                rightIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out2.right)
                leftIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                rightIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x2=xi;
            y2=yi;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
    {
        DrawLine(hdc,Round(x1),Round(y1),Round(x2),Round(y2),c);
    }
}
void DrawRect(HDC hdc, double x1, double y1, double x2, double y2, COLORREF c)
{
    DrawLine(hdc,x1,y1,x2,y1,c);

    DrawLine(hdc,x2,y1,x2,y2,c);

    DrawLine(hdc,x1,y2,x2,y2,c);

    DrawLine(hdc,x1,y1,x1,y2,c);
}
/*  This function is called by the Windows function DispatchMessage()  */
int  xx1eft,yyTop,xxRight,yybottom,xx1,xx2,yy1,yy2;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
    case WM_LBUTTONDBLCLK:
        xx1=LOWORD(lParam);
        yy1=HIWORD(lParam);
        xx1eft=xx1;
        yyTop=yy1;

        break;
    case WM_RBUTTONDBLCLK:
        xx2=LOWORD(lParam);
        yy2=HIWORD(lParam);
        xxRight=xx2;
        yybottom=yy2;
        DrawRect(hdc,xx1eft,yyTop,xxRight,yybottom,RGB(255,0,0));
        DrawLine(hdc,xx1,yy1,xx2,yy2,RGB(255,0,0));
        CohenSuthLineClipping(hdc,xx1,yy1,xx2,yy2,xx1eft,yyTop,xxRight,yybottom,RGB(150,80,255));
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
