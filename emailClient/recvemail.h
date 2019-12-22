#ifndef RECVEMAIL_H
#define RECVEMAIL_H

#include <QWidget>
#include "mainmenu.h"
#include "recvthread.h"
#include "string"

namespace Ui {
class recvemail;
}

class recvemail : public QWidget
{
    Q_OBJECT

public:
    explicit recvemail(QWidget *parent = nullptr);
    ~recvemail();

private:
    Ui::recvemail *ui;
    class recvthread *recv;
    string trimstr(string s);

private slots:
    void back();
    void getList();
    void setList(char* data);
    void getEmailInfo(int row, int col);
    void getInfo(QString info);
    void setEmailInfo(char* data);
};

#endif // RECVEMAIL_H
