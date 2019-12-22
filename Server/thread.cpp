#include "thread.h"

void thread::run()
{
    while (1) {
        char recvBuf[50];
        int a = recv(sockConn, recvBuf, 50, 0);
        //printf("%s\n", recvBuf);
        emit sendmess(recvBuf);
        if (a <= 0) {
            closesocket(sockConn);
            break;
        }
    }
}
