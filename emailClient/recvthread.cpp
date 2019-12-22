#include "recvthread.h"

void recvthread::getHostAddr()
{
    ptr=gethostbyname("pop.163.com");
    if(ptr==nullptr)
    cout<<"GetHostByName Error..."<<endl;
    //pop.163.com是一个不可用的地址，要将它转换成unsigned long形的变量
    //传递到servAddr.sin_Addr.s_addr中。
    memcpy(&addr,ptr->h_addr_list[0],sizeof(in_addr));
}

void recvthread::connectServer()
{
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 1);
    WSAStartup(wVersionRequested, &wsaData);
    if((ServMail=socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR)
    {
        emit info("ServMail ERROR...");
        WSACleanup();
        closesocket(ServMail);
    }

    getHostAddr();

    ServAddr.sin_family=AF_INET;
    ServAddr.sin_port=htons(110);
    ServAddr.sin_addr.s_addr=inet_addr(inet_ntoa(addr));

    int len=sizeof(SOCKADDR_IN);
    int ret;

    if((ret=::connect(ServMail,(LPSOCKADDR)&ServAddr,len))==INVALID_SOCKET)
    {
        emit info("Connect Error...");
        closesocket(ServMail);
        WSACleanup();
    }
    else
    {
        ZeroMemory(buf,2048);
        recv(ServMail,buf,2048,0);
        emit info("Connect Success...");
        emit info(buf);

    }
}

void recvthread::loginServer()
{
    Order = "USER ";
    Order.append(User).append("\r\n");
    send(ServMail, Order.c_str(), strlen(Order.c_str()), 0);
    buf[recv(ServMail, buf, 2048,  0)] = '\0';
    emit info(buf);
    Order = "PASS ";
    Order.append(Psd).append("\r\n");
    send(ServMail, Order.c_str(), strlen(Order.c_str()), 0);
    buf[recv(ServMail, buf, 2048,  0)] = '\0';
    emit info(buf);
}

void recvthread::getEmailList()
{
    Order = "LIST\r\n";
    send(ServMail, Order.c_str(), strlen(Order.c_str()), 0);
    buf[recv(ServMail, buf, 2048, 0)] = '\0';
    emit list(buf);
}

void recvthread::getEmailInfo(int num)
{
    Order = "retr ";
    char *numChar;
    Order.append(itoa(num, numChar, 10)).append("\r\n");
    send(ServMail, Order.c_str(), strlen(Order.c_str()), 0);
    recv(ServMail, (LPSTR)recvbuf,sizeof(recvbuf),  0);
    recv(ServMail, (LPSTR)recvbuf,sizeof(recvbuf),  0);
    emit emailInfo((LPSTR)recvbuf);
}

void recvthread::run()
{
    this->connectServer();
    this->loginServer();
    if(this->status == -1)
    {

        this->getEmailList();
    }
    else
    {
        this->getEmailInfo(status+1);
    }
    closesocket(ServMail);
    WSACleanup();
}
