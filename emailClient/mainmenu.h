#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <widget.h>
#include <recvemail.h>

namespace Ui {
class mainmenu;
}

class mainmenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainmenu(QWidget *parent = nullptr);
    ~mainmenu();

private:
    Ui::mainmenu *ui;
    class Widget *widget;
    class recvemail *recv;

private slots:
    void sendEmail();
    void recvEmail();
};

#endif // MAINMENU_H
