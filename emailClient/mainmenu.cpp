#include "mainmenu.h"
#include "ui_mainmenu.h"

mainmenu::mainmenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainmenu)
{
    ui->setupUi(this);
    connect(ui->sendMail, SIGNAL(clicked()), this, SLOT(sendEmail()));
    connect(ui->recvMail, SIGNAL(clicked()), this, SLOT(recvEmail()));
}

mainmenu::~mainmenu()
{
    delete ui;
}

void mainmenu::sendEmail()
{
    widget = new class Widget();
    widget->show();
    this->close();
}

void mainmenu::recvEmail()
{
    recv = new class recvemail();
    recv->show();
    this->close();
}
