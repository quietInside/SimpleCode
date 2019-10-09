#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int APIENTRY WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lp,int nC)
{
   MSG msg;
   HWND hWnd;
   hInst = hI;
   WNDCLASS wc;
   memset(&wc,0,sizeof(WNDCLASS));
   wc.lpfnWndProc = (WNDPROC)WndProc;
   wc.hInstance = hI;
   wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
   wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
   wc.lpszClassName = "W1";
   RegisterClass(&wc);
   hWnd=CreateWindowEx(WS_EX_PALETTEWINDOW,"W1","UDP 程序2 [端口:6000]",
                       WS_OVERLAPPEDWINDOW,400,200,200,100,NULL,NULL,hI,NULL);
    if(!hWnd)
        return FALSE;
    ShowWindow(hWnd,nC);

    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

WSADATA ws;
SOCKET s1,s2;
struct sockaddr_in Cs1A,Cs2A;
char sendBuf[200];
char recvBuf[200];
int len;
#define Cs1Post 6000
#define Cs2Post 8000
#define Cs1IP "127.0.0.1"
#define Cs2IP "127.0.0.1"

LRESULT CALLBACK WndProc(HWND hW,UINT msg,WPARAM wP,LPARAM lP)
{
    switch(msg)
    {
    case WM_DESTROY:  //关闭程序触发事件
        WSAAsyncSelect(s1,hW,0,0);
        closesocket(s1);
        WSACleanup();
        PostQuitMessage(0);
        break;
    case WM_CREATE:
        WSAStartup(0x0202,&ws);
        s1=socket(AF_INET,SOCK_DGRAM,0);
        Cs1A.sin_family=AF_INET;
        Cs1A.sin_port=htons(Cs1Post);
        Cs1A.sin_addr.s_addr=inet_addr(Cs1IP);
        len=bind(s1,(struct sockaddr*) &Cs1A,sizeof(Cs1A));

        Cs2A.sin_family=AF_INET;
        Cs2A.sin_port=htons(Cs2Post);
        Cs2A.sin_addr.s_addr=inet_addr(Cs2IP);

        WSAAsyncSelect(s1,hW,WM_USER+1,FD_READ);
        //Beep(2000,500);
        break;
    case WM_USER+1:
        switch(LOWORD(lP))
        {
        case FD_READ:
            len = recv(s1,recvBuf,sizeof(recvBuf),0);
            recvBuf[len] = 0;
            if(len!=-1)
                MessageBox(0,recvBuf,"UDP 程序2从UDP 程序1收到的数据",0);

            break;
        }
        break;
    case WM_LBUTTONDOWN:
        wsprintf(sendBuf,"Hello,UDP 程序1!");
        len = sizeof(Cs2A);
        sendto(s1,sendBuf,strlen(sendBuf),0,(struct sockaddr*) &Cs2A,len);
        break;
    }
    return DefWindowProc(hW,msg,wP,lP);
}
