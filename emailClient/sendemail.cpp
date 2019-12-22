#include "sendemail.h"


sendEmail::sendEmail()
{
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 1);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if(err != 0)
    {
        emit info("初始化失败,请重启软件!");
    }
    sockClient = socket(AF_INET, SOCK_STREAM, 0); //建立socket对象
    HOSTENT* pHostent;//hostent是host entry的缩写，该结构记录主机的信息，包括主机名、别名、地址类型、地址长度和地址列表

    pHostent = gethostbyname("smtp.qq.com"); //得到有关于域名的信息,链接到qq邮箱服务器

    addrServer.sin_addr.S_un.S_addr = *((DWORD *)pHostent->h_addr_list[0]); //得到smtp服务器的网络字节序的ip地址
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(25); //连接端口25
    emit info("初始化完成!");
}

void sendEmail::run()
{
    char buff[500];
    int err;
    string message;
    err = ::connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)); //向服务器发送请求
    if (err != 0)
    {
        char *a;
        stopThread(itoa(err, a, 10), "连接服务器失败!");
    }
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << buff << endl;
    if (atoi(buff) != 220)
    {
        stopThread(buff, "连接服务器失败!");
    }
    emit info("开始登录邮件服务器...");
    /*
    登录邮件服务器
    */
    message = "ehlo qq.com\r\n";
    send(sockClient, message.c_str(), message.length(), 0); //发送ehlo命令
    buff[recv(sockClient, buff, 500, 0)] = '\0';   //接收返回值
    cout << "ehlo:" << buff << endl;
    if(atoi(buff) != 250)
    {
        stopThread(buff, "ehlo命令失败!");
    }

    message = "auth login \r\n";
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "auth login:" << buff << endl;
    if(atoi(buff) != 334)
    {
        stopThread(buff, "登录服务器失败!");
    }
    /*
    发送base64加密的用户名、密码
    */
    message = username.append("\r\n");
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "username:" << buff << endl;
    if(atoi(buff) != 334)
    {
        stopThread(buff, "登录服务器失败!");
    }
    message = password.append("\r\n");
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "password:" << buff << endl;
    if(atoi(buff) != 235)
    {
        stopThread(buff, "登录服务器失败!");
    }
    emit info("登录成功,开始发送邮件!");
    /*
    使用 MAIL 命令指定发送者
    使用 RCPT 命令指定接收者，可以重复使用RCPT指定多个接收者
    */

    message = "MAIL FROM:<";
    message.append(fromEmail).append("> \r\nRCPT TO:<");
    message.append(toEmail);
    message.append("> \r\n");
    cout << "message=" << message;

    send(sockClient, message.c_str(), message.length(), 0);

    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "mail from: " << buff << endl;
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "rcpt to: " << buff << endl;
    /*
    使用 DATA 命令告诉服务器要发送邮件内容
    */
    message = "DATA\r\n";
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "data: " << buff << endl;
    message = "From: ";
    message.append(fromEmail);
    message.append("\r\nTo: ");
    message.append(toEmail);
    message.append("\r\nSubject: ");
    message.append(subject);
    message.append("\r\n\r\n");
    message.append(context);
    message.append("\r\n.\r\n");
    cout<<"message="<<message;

    /*message = "From: XXX@qq.com\r\n\
    To: XXX@163.com\r\n\
    subject: test\r\n\r\n\
    Just a test!\r\n\
    your friend\r\n\
    Ctt\r\n.\r\n"; //注意subject关键字与正文之间要有一个空行*/

    send(sockClient, message.c_str(), message.length(), 0);
    message = "QUIT\r\n";
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "QUIT:" << buff << endl;
    emit info("发送成功!");
    emit success(1);
    this->terminate();
    this->wait();
}

void sendEmail::stopThread(string buff, QString info)
{
    cout << buff << endl;
    emit this->info(info);
    this->terminate();
    this->wait();
}
