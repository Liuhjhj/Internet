#include "widget.h"
#include "./ui_widget.h"
using namespace std;
static int connect_status = -1;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    c = new class client();
    c->init();
    ui->setupUi(this);
    initSignalSlots();
    connect_status = c->con();
    c->start();
}

Widget::~Widget()
{
    delete ui;
}

//信号槽是一种通信机制,当某个组件发送信号时会执行与之绑定的槽函数
//与信号绑定的函数称为槽函数
//槽函数和自定义的信号需要在头文件里面声明
//初始化信号和槽函数
void Widget::initSignalSlots()
{
    //自定义的信号
    connect(c, SIGNAL(status(QString)), this, SLOT(setStatus(QString)));
    //按钮被点击就会发出点击信号
    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exit()));
    //点击信号
    connect(ui->send, SIGNAL(clicked()), this, SLOT(send()));
    //自定义的信号
    connect(c, SIGNAL(messages(QString)), this, SLOT(recv(QString)));
}

void Widget::setStatus(QString data)
{
    //设置界面中组件文本
    //该组件的名字为status
    //界面文件为工程里面的ui文件
    ui->status->setText(data);
}

//退出程序
void Widget::exit()
{
    //断开客户端与服务器的连接
    c->disconnect();
    //终止子线程c
    c->terminate();
    c->wait();
    //关闭主线程
    QApplication* app;
    app->exit();
}

//发送消息
void Widget::send()
{
    if(connect_status == -1)
    {
        //设置界面中组件文本
        ui->warn->setText("发送失败!");
        ui->status->setText("连接已断开!");
        return;
    }
    //获取界面中文本框的内容(返回内容的数据类型为QString)
    //利用QByteArray将QString转换为char*
    QByteArray q = ui->input_message->toPlainText().toLatin1();
    //将Qstring转换为char*
    char* data = q.data();
    if(c->send(data) != SOCKET_ERROR)
    {
        ui->warn->setText("发送成功!");
        //设置界面中组件文本
        ui->input_message->setText("");
    }
    else
    {
        //设置界面中组件文本
        ui->warn->setText("未能发送!");
    }
}

//收到消息
void Widget::recv(QString mess)
{
    //向界面的list组件添加条目
    ui->message->addItem(mess);
}
