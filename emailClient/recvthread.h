#ifndef RECVTHREAD_H
#define RECVTHREAD_H
#include <QThread>
#include <winsock2.h>
#include <iostream>
using namespace std;

class recvthread : public QThread
{
    Q_OBJECT

public:
    int status;
    string User;
    string Psd;
    void connectServer();
    void loginServer();
    void getEmailList();
    void getEmailInfo(int num);

private:
    void run() override;
    void getHostAddr();
    hostent *ptr;
    in_addr addr;
    SOCKET ServMail;
    SOCKADDR_IN ServAddr;
    string Order;
    char buf[2048];
    char recvbuf[20000];

signals:
    void info(QString info);
    void list(char* data);
    void emailInfo(char* info);
};

#endif // RECVTHREAD_H
