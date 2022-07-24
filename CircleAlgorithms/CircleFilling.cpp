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
    wincl.hbrBackground = (HBRUSH) WHITE_BRUSH;

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
               1000,                 /* The programs width */
               750,                 /* and height in pixels */
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
void LineMidpoint(HDC hdc,int x1,int y1,int x2,int y2,COLORREF color)
{
    double dx=x2-x1;
    double dy=y2-y1;
    double slope =dy/dx;
    if((abs(dy)<=abs(dx))&&(slope>=0))
    {
        if(x1>x2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        double d=(x2-x1)-2*(y2-y1);
        double change1=2*(x2-x1)-2*(y2-y1);
        double change2=-2*(y2-y1);
        int x=x1;
        int y=y1;
        SetPixel(hdc,x,y,color);
        while(x<=x2)
        {
            if(d<=0)
            {
                y++;
                d+=change1;
            }
            else
            {
                d+=change2;
            }
            x++;
            SetPixel(hdc,x,y,color);
        }
    }
    else if((abs(dy)>abs(dx))&&(slope>0))
    {
        if(y1>y2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        double d=2*(x2-x1)-(y2-y1);
        double change1=2*(x2-x1);
        double change2= 2*((x2-x1)-(y2-y1));
        int x=x1;
        int y=y1;
        SetPixel(hdc,x,y,color);
        while(y<=y2)
        {
            if(d<0)
            {
                d+=change1;
            }
            else
            {
                x++;
                d+=change2;
            }
            y++;
            SetPixel(hdc,x,y,color);
        }

    }
    else if((slope<0)&&(abs(dy)<=abs(dx)))
    {
        if(x1>x2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        int x=x1;
        int y=y1;
        double d=-(x2-x1)-2*(y2-y1);
        double change1=-2*(y2-y1);
        double change2=-2*((x2-x1)+(y2-y1));
        SetPixel(hdc,x,y,color);
        while(x<=x2)
        {
            if(d<0)
            {
                d+=change1;
            }
            else
            {
                y--;
                d+=change2;
            }
            x++;
            SetPixel(hdc,x,y,color);
        }

    }
    else
    {
        if(y1>y2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        int x=x1;
        int y=y1;
        double d=2*(x2-x1)+(y2-y1);
        double change1=2*(x2-x1);
        double change2=2*((x2-x1)+(y2-y1));
        SetPixel(hdc,x,y,color);
        while(y<=y2)
        {
            if(d>0)
            {
                d+=change1;
            }
            else
            {
                d+=change2;
                x--;
            }
            y++;
            SetPixel(hdc,x,y,color);
        }
    }
}
void Draw8Point(HDC hdc,int xc,int yc,int x,int y,COLORREF color,int q)
{
    SetPixel(hdc,xc+x,yc+y,color);
    SetPixel(hdc,xc-x,yc+y,color);
    SetPixel(hdc,xc-x,yc-y,color);
    SetPixel(hdc,xc+x,yc-y,color);
    SetPixel(hdc,xc+y,yc+x,color);
    SetPixel(hdc,xc-y,yc+x,color);
    SetPixel(hdc,xc-y,yc-x,color);
    SetPixel(hdc,xc+y,yc-x,color);
    if(q==1)LineMidpoint(hdc,xc,yc,xc+y,yc-x,color);
    else if(q==2)LineMidpoint(hdc,xc,yc,xc+x,yc-y,color);
    else if(q==3)LineMidpoint(hdc,xc,yc,xc+x,yc+y,color);
    else if(q==4)LineMidpoint(hdc,xc,yc,xc+y,yc+x,color);
    else if(q==5)LineMidpoint(hdc,xc,yc,xc-y,yc+x,color);
    else if(q==6)LineMidpoint(hdc,xc,yc,xc-x,yc+y,color);
    else if(q==7)LineMidpoint(hdc,xc,yc,xc-x,yc-y,color);
    else LineMidpoint(hdc,xc,yc,xc-y,yc-x,color);


}
void midpoint(HDC hdc,int xc,int yc,int r,COLORREF color,int q)
{
    int x=r;
    int y=0;
    Draw8Point(hdc,xc,yc,x,y,color,q);
    int d=1-r;
    int change1=5-2*r;;
    int change2=3;
    while(y<x)
    {
        if(d>=0)
        {
            d+=change1;
            change1+=4;
            x--;
        }
        else
        {
            d+=change2;
            change1+=2;
        }
        change2+=2;
        y++;
        Draw8Point(hdc,xc,yc,x,y,color,q);
    }

}
/*  This function is called by the Windows function DispatchMessage()  */
int xc,yc,xx,yy,r,q;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;

    case WM_LBUTTONDBLCLK:
        xc=LOWORD(lParam);
        yc=HIWORD(lParam);
        break;
    case WM_RBUTTONDBLCLK:
        xx=LOWORD(lParam);
        yy=HIWORD(lParam);
        r=sqrt(((xx-xc)*(xx-xc))+((yy-yc)*(yy-yc)));
        cout<<"Which quarter ?"<<endl;
        cin>>q;
        midpoint(hdc,xc,yc,r,RGB(0,0,255),q);
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
