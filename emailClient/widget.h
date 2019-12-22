#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <sendemail.h>
#include <base64.h>
#include <mainmenu.h>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    class sendEmail *send_email;
    class base64 *code;
    void textSet();
    class mainmenu *menu;

private slots:
    void setInfo(QString info);
    void startThread();
    void setButton(int status);
    void back();
};
#endif // WIDGET_H
