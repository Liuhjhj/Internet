#include "widget.h"
#include "./ui_widget.h"
#include "ping.h"
#include "iostream"
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    p = new class ping();
    ui->setupUi(this);
    setWindowTitle("Ping");
    initSignalSlots();
    ui->table->setRowCount(0);
    ui->table->setColumnCount(2);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->addr1->setText("14");
    ui->addr2->setText("215");
    ui->addr3->setText("177");
    ui->addr4->setText("38");
    ui->addr5->setText("39");
    ui->timeOut->setText("3000");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initSignalSlots()
{
    connect( ui->exit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(p, SIGNAL(setTable(int, int, char*)), this, SLOT(setTable(int,int,char*)));
    connect(ui->start, SIGNAL(clicked()), this, SLOT(startPing()));
    connect(ui->stop, SIGNAL(clicked()), this, SLOT(stopPing()));
}

void Widget::setTable(int row, int col, char *data)
{
    int RowCont;
    RowCont=ui->table->rowCount();
    ui->table->insertRow(RowCont);//增加一行
    ui->table->setItem(row,col, new QTableWidgetItem(data));
    col++;
    ui->table->setItem(row,col, new QTableWidgetItem("在线"));
    ui->table->show();
}

void Widget::startPing()
{
    ui->table->setRowCount(0);
    p->iTimeout = ui->timeOut->text().toInt();
    p->addr1 = ui->addr1->text().toInt();
    p->addr2 = ui->addr2->text().toInt();
    p->addr3 = ui->addr3->text().toInt();
    p->addr4 = ui->addr4->text().toInt();
    p->addr5 = ui->addr5->text().toInt();
    p->start();
}

void Widget::stopPing()
{
    p->terminate();
    p->wait();
}

