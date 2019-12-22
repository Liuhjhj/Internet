#ifndef SERVER_H
#define SERVER_H

#include "QThread"
#include "winsock2.h"
#include <inaddr.h>

class server:public QThread
{
    Q_OBJECT

public:
    server();
    void init();
    SOCKET sockSrv;
    SOCKET sockGroup[5];
    int groupLen = 0;

private:
    void run() override;

public slots:
    void sendmess(char *data);
};

#endif // SERVER_H
