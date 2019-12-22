#ifndef SENDTHREAD_H
#define SENDTHREAD_H
#include "QThread"
#include "server.h"

class sendThread : public QThread
{
    Q_OBJECT
    
public:
    SOCKET sockConn[5];
    char recvBuf[50];
    
private:
    void run() override;
};

#endif // SENDTHREAD_H
