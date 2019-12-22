#ifndef CLIENT_H
#define CLIENT_H
#include "QThread"
#include "stdio.h"
#include "winsock2.h"
#include "inaddr.h"


class client:public QThread
{
    Q_OBJECT

public:
    SOCKET  sockClient;
    SOCKADDR_IN addrSrv;
    char recvBuf[50];
    void init();
    int con();
    int send(char* data);
    int recv();
    void disconnect();
    void run() override;

//声明自定义信号
//槽函数有权限(public,protected和private),信号没有
//信号的返回值均为void,且只需要声明,不需要实现
signals:
    void status(QString status);
    void messages(QString mess);

};
#endif // CLIENT_H
