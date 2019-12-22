#ifndef IPCAST_H
#define IPCAST_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <QThread>
#include <iostream>
#include <string>
using namespace std;

class ipcast : public QThread
{
    Q_OBJECT

public:
    void init();
    int status = 0;
    void send(QString data);
    void recv();
    void disconnect();
    char *MCASTADDR;
    u_short MCASTPORT;

private:
    SOCKET sockM;
    SOCKET sock;
    sockaddr_in remote;
    sockaddr_in local;
    void run() override;

signals:
    void info(QString info);
    void get(QString data);
};

#endif // IPCAST_H
