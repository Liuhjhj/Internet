#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->IP->setText("233.0.0.1");
    ui->port->setText("5150");
    ip = new class ipcast();
    connect(ip, SIGNAL(info(QString)), this, SLOT(getInfo(QString)));
    connect(ip, SIGNAL(get(QString)), this, SLOT(set(QString)));
    connect(ui->send, SIGNAL(clicked()), this, SLOT(send()));
    connect(ui->recv, SIGNAL(clicked()), this, SLOT(recv()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getInfo(QString info)
{
    ui->info->setText(info);
}

//收到消息加载到界面上
void Widget::set(QString data)
{
    ui->recvText->append(data);
}

void Widget::send()
{
    QByteArray ba = ui->IP->text().toLatin1();
    ip->MCASTADDR = ba.data();
    ip->MCASTPORT = ui->port->text().toUShort();
    if(ip->status == 0)
        ip->init();
    ip->send(ui->sendText->text());
    ui->sendText->setText("");
}

void Widget::recv()
{

    QByteArray ba = ui->IP->text().toLatin1();
    ip->MCASTADDR = ba.data();
    ip->MCASTPORT = ui->port->text().toUShort();
    if (ip->status == 0)
        ip->init();
    ip->start();
    ui->recv->setEnabled(false);
}
