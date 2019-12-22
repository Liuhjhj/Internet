#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    s = new class server();
    connect(ui->server, SIGNAL(clicked()), this, SLOT(startServer()));
    connect(ui->exit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::startServer()
{
    ui->server->setEnabled(false);
    s->start();
}

