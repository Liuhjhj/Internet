#ifndef PING_H
#define PING_H

#include <QThread>

class ping:public QThread
{
    Q_OBJECT

public:
    int addr1, addr2, addr3, addr4, addr5, iTimeout;

signals:
    void setTable(int row, int col, char *data);

protected:
    void run() override;

};

#endif // PING_H
