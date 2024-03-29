#include <stdio.h>
#include <stdlib.h>
#include <Winsock2.h>

#define DEFAULT_PORT 5050
void main()
{
    int iPort = DEFAULT_PORT;
    WSADATA wsaData;
    SOCKET sListen, sAccept;
    int iLen;
    int iSend;
    char buf[]="I am a server.";

    struct sockaddr_in ser, cli;
    printf("-----------------------\n");
    printf("Server waiting\n");
    printf("-----------------------\n");
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        printf("Failed to load Winsock.\n");
        return;
    }
    sListen=socket(AF_INET,SOCK_STREAM,0);
    if(sListen==INVALID_SOCKET)
    {
        printf("sock()Failed:%d\n",WSAGetLastError());
    }

    ser.sin_family=AF_INET;
    ser.sin_port=htons(iPort);
    ser.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(sListen,(LPSOCKADDR)&ser,sizeof(ser))==SOCKET_ERROR)
    {
        printf("bind()Failed:%d\n",WSAGetLastError());
        return;
    }

    if(listen(sListen,5)==SOCKET_ERROR)
    {
        printf("listen()Failed:%d\n",WSAGetLastError());
        return;
    }
    iLen=sizeof(cli);
    while(1)
    {
        sAccept=accept(sListen,(struct sockaddr*)&cli,&iLen);
        if(sAccept==INVALID_SOCKET)
        {
            printf("accept()Failed:%d\n",WSAGetLastError());
            break;
        }

        printf("Accepted client IP:[%s],post:[%d]\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
        iSend=send(sAccept,buf,sizeof(buf),0);
        if(iSend==SOCKET_ERROR)
        {
            printf("send()Failed:%d\n",WSAGetLastError());
            break;
        }
        else
        {
            if(iSend==0)
                break;
            else{
                printf("send()byte:%d\n",iSend);
                printf("-----------------------\n");
            }
        }
        closesocket(sAccept);
    }
    closesocket(sListen);
    WSACleanup();
}
