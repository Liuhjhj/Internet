#ifndef THREAD_H
#define THREAD_H

#include "QThread"
#include "server.h"

class thread:public QThread
{
    Q_OBJECT

public:
    void run() override;
    SOCKET sockConn;

signals:
    void sendmess(char *data);

};

#endif // THREAD_H
