#include "recvemail.h"
#include "ui_recvemail.h"
#include <sstream>
#include <regex>

recvemail::recvemail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recvemail)
{
    ui->setupUi(this);
    ui->emailTable->setRowCount(0);
    ui->emailTable->setColumnCount(1);
    ui->emailTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recv = new class recvthread();
    ui->info->setReadOnly(true);
    ui->context->setReadOnly(true);
    ui->email->setText("liu2445342557");
    ui->password->setText("Liuhongji2445");
    ui->emailTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->exit, SIGNAL(clicked()), this, SLOT(back()));
    connect(recv, SIGNAL(info(QString)), this, SLOT(getInfo(QString)));
    connect(recv, SIGNAL(list(char*)), this, SLOT(setList(char*)));
    connect(recv, SIGNAL(emailInfo(char*)), this, SLOT(setEmailInfo(char*)));
    connect(ui->refresh, SIGNAL(clicked()), this, SLOT(getList()));
    connect(ui->emailTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(getEmailInfo(int, int)));
}

recvemail::~recvemail()
{
    delete ui;
}

void recvemail::back()
{
    class mainmenu *menu = new class mainmenu();
    menu->show();
    this->close();
}

void recvemail::getInfo(QString info)
{
    ui->info->append(info);
}

void recvemail::getList()
{
    recv->status = -1;
    recv->User = ui->email->text().toStdString();
    recv->Psd = ui->password->text().toStdString();
    recv->start();
}

void recvemail::setList(char* data)
{
    int i = 0, row = 0, col = 0;
    istringstream str(data);
    string out;
    while (str >> out)
    {
        if (i >= 3)
        {
            if (i % 2 == 0)
            {
                int RowCont;
                RowCont=ui->emailTable->rowCount();
                ui->emailTable->insertRow(RowCont);//增加一行
                ui->emailTable->setItem(row, col, new QTableWidgetItem(&out[0]));
                row++;
            }
        }
        i++;
    }
}

void recvemail::getEmailInfo(int row, int col)
{
    recv->User = ui->email->text().toStdString();
    recv->Psd = ui->password->text().toStdString();
    recv->status = row;
    recv->start();
}

void recvemail::setEmailInfo(char* data_char)
{
    string data = data_char;
    smatch results;
    regex from("From: (.*).com");
    if (regex_search(data, results, from))
    {
        ui->fromEmail->setText(&trimstr(results.str())[0]);
    }
    regex date("Date: (.*)\r");
    if(regex_search(data, results, date))
    {
        ui->date->setText(&trimstr(results.str())[0]);
    }
    regex sub("Subject: (.*)\r\n");
    if(regex_search(data, results, sub))
    {

        ui->subject->setText(&trimstr(results.str())[0]);
    }
    regex text("\r\n\r\n(.*)");
    if(regex_search(data, results, text))
    {
        ui->context->setText(&trimstr(results.str())[0]);
    }
}

string recvemail::trimstr(string s){
  size_t n = s.find_last_not_of("\r\n");
    if (n != string::npos){
        s.erase(n + 1, s.size() - n);
    }
    n = s.find_first_not_of("\r\n");
    if (n != string::npos){
        s.erase(0, n);
    }
    return s;
}
