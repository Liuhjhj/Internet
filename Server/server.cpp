#include "server.h"
#include "thread.h"

server::server()
{
    WORD wVersionRequested;
    WSADATA wsadata;
    int err;

    wVersionRequested = MAKEWORD(1,1);

    err = WSAStartup(wVersionRequested, &wsadata);
    if(err != 0)
    {
        return;
    }

    if(LOBYTE(wsadata.wVersion) != 1 || HIBYTE(wsadata.wVersion) != 1)
    {
        WSACleanup();
        return;
    }
    sockSrv = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);

    bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

    listen(sockSrv, 5);
}

void server::run()
{
    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    while (1) {
        SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
        sockGroup[groupLen] = sockConn;
        groupLen++;
        class thread *t = new class thread();
        t->sockConn = sockConn;
        //绑定信号和槽函数,不是socket的连接函数
        connect(t, SIGNAL(sendmess(char*)), this, SLOT(sendmess(char*)));
        t->start();

    }
}

void server::sendmess(char *data)
{
    for (int i=0; i < groupLen; i++)
    {
        printf("%s\n", data);
        ::send(sockGroup[i], data, strlen(data)+1, 0);
    }
}

