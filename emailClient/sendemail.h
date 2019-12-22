#ifndef SENDEMAIL_H
#define SENDEMAIL_H
#include <QThread>
#include <winsock2.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


class sendEmail : public QThread
{
    Q_OBJECT

public:
    sendEmail();
    string username;
    string password;
    string fromEmail;
    string toEmail;
    string subject;
    string context;

private:
    void run() override;
    void stopThread(string buff, QString info);
    SOCKET sockClient;
    SOCKADDR_IN addrServer;


signals:
    void info(QString info);
    void success(int status);
};

#endif // SENDEMAIL_H
