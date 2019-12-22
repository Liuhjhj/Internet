#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->info->isReadOnly();
    textSet();
    code = new class base64();
    send_email = new class sendEmail();
    connect(send_email, SIGNAL(info(QString)), this, SLOT(setInfo(QString)));
    connect(ui->sendEmail, SIGNAL(clicked()), this, SLOT(startThread()));
    connect(ui->exit, SIGNAL(clicked()), this, SLOT(back()));
    connect(send_email, SIGNAL(success(int)), this, SLOT(setButton(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setInfo(QString info)
{
    ui->info->append(info);
}

void Widget::startThread()
{
    QString Qstr = ui->fromEmail->text();
    QByteArray ba = Qstr.toLatin1();
    QString Qstr2 = ui->password->text();
    QByteArray ba2 = Qstr2.toLatin1();
    char* username = ba.data();
    char* password = ba2.data();
    string userEncode = code->encode(username);
    string passEncode = code->encode(password);
    send_email->username = userEncode;
    send_email->password = passEncode;
    send_email->fromEmail = ui->fromEmail->text().toStdString().append("@qq.com");
    send_email->toEmail = ui->toEmail->text().toStdString();
    send_email->subject = ui->subject->text().toStdString();
    send_email->context = ui->context->toPlainText().toStdString();
    send_email->start();
}

void Widget::textSet()
{
    ui->fromEmail->setText("2445342557");
    ui->toEmail->setText("liu2445342557@163.com");
    ui->subject->setText("hello");
    ui->context->setText("hello!!!!");
    ui->password->setText("yjpphajbotouebdj");

}

void Widget::setButton(int status)
{
    if (status)
    {
        ui->sendEmail->setEnabled(false);
        ui->sendEmail->setText("发送成功");
    }
}

void Widget::back()
{
    menu = new class mainmenu();
    menu->show();
    this->close();
}
