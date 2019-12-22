#include <client.h>

void client::init()
{
    WORD wVersionRequested;
    WSADATA wsadata;
    int err;

    wVersionRequested = MAKEWORD(1,1);

    err = WSAStartup(wVersionRequested, &wsadata);
    if(err != 0)
    {
        emit status("初始化失败!");
        return;
    }
    if (LOBYTE(wsadata.wVersion) != 1||HIBYTE(wsadata.wVersion) != 1)
    {
        WSACleanup();
        emit status("版本不兼容!");
        return;
    }
    emit status("初始化完成, 正在连接");
}

//连接客户端
int client::con()
{
    sockClient = socket(AF_INET, SOCK_STREAM, 0);
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    //0-成功  -1-失败
    //绑定信号槽的函数和socket类的connect方法重名
    //使用socket的connect方法要在前面加::
    if(::connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == 0)
    {
        //发送信号
        //信号与槽函数绑定之后,只要发送信号,会立即执行槽函数
        emit status("连接成功!");
        return 0;
    }
    else
    {
        //发送信号
        emit status("连接失败!");
        return -1;
    }
}

//发送消息
int client::send(char *data)
{
    //socket的send函数与其他函数重名
    //使用socket的send方法要在前面加::
    return ::send(sockClient, data, strlen(data)+1, 0);
}

//子线程的执行函数
//启动子线程后会执行这个函数
void client::run()
{
    while(1)
    {
        char recvBuf[50];
        //socket的recv函数与其他函数重名
        //使用socket的recv方法要在前面加::
        int a = ::recv(sockClient, recvBuf, 50, 0);
        emit messages(recvBuf);
        if (a <= 0) {
            closesocket(sockClient);
            break;
        }
    }
}

//断开与服务器的连接
void client::disconnect()
{
    closesocket(sockClient);
    WSACleanup();
}
