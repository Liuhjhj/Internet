#include "ipcast.h"
#define BUFSIZE 1024 //接收数据缓冲大小。
#define BUFSIZE 1024 //发送数据缓冲大小。

void ipcast::init()
{
    WSADATA wsd;
    if( WSAStartup( MAKEWORD(2,2),&wsd) != 0 )
    {
        emit info("初始化失败!");
        status = 0;
        return;
    }
    if((sock=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,
                           WSA_FLAG_MULTIPOINT_C_LEAF|WSA_FLAG_MULTIPOINT_D_LEAF|
                           WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
    {
        emit info("创建socket失败!");
        WSACleanup();
        status = 0;
        return;
    }
    local.sin_family = AF_INET;
    local.sin_port = htons(MCASTPORT);
    local.sin_addr.s_addr = INADDR_ANY;
    if( bind(sock,(struct sockaddr*)&local,sizeof(local)) == SOCKET_ERROR )
    {
        emit info("绑定端口失败!");
        closesocket(sock);
        WSACleanup();
        status = 0;
        return;
    }
    remote.sin_family = AF_INET;
    remote.sin_port = htons(MCASTPORT);
    remote.sin_addr.s_addr = inet_addr( MCASTADDR );
    if((sockM = WSAJoinLeaf(sock,(SOCKADDR*)&remote,
                             sizeof(remote),NULL,NULL,NULL,NULL,
                             JL_BOTH)) == INVALID_SOCKET)
    {
        emit info("加入多播组失败!");
        closesocket(sock);
        WSACleanup();
        status = 0;
        return;
    }
    status = 1;
}

void ipcast::send(QString data)
{
    QByteArray ba = data.toLatin1();
    char* sendbuf = ba.data();
    if( sendto(sockM,sendbuf,strlen(sendbuf),0,(struct sockaddr*)
                    &remote,sizeof(remote))==SOCKET_ERROR)
    {
        closesocket(sockM);
        closesocket(sock);
        WSACleanup();
        emit info("发送失败!");
        return;
    }
    emit info("发送成功!");
}

void ipcast::recv()
{
    char recvbuf[BUFSIZE];
    int ret;
    sockaddr_in from;
    int len = sizeof (sockaddr_in);
    while(1)
    {
        if(( ret = recvfrom(sock,recvbuf,BUFSIZE,0,
                            (struct sockaddr*)&from,&len)) == SOCKET_ERROR)
        {
            char* err;
            emit info(itoa(WSAGetLastError(), err, 10));
            closesocket(sockM);
            closesocket(sock);
            WSACleanup();
            emit info("发生错误!");
            return;
        }
        recvbuf[ret] = '\0';
        QString data = inet_ntoa(from.sin_addr);
        data.append(": ");
        data.append(recvbuf);
        emit get(data);
    }
}

void ipcast::disconnect()
{
    closesocket(sockM);
    closesocket(sock);
    WSACleanup();
}

void ipcast::run()
{
    this->recv();
}
