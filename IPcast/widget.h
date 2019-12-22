#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <ipcast.h>

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
    class ipcast *ip;

private slots:
    void getInfo(QString info);
    void set(QString data);
    void send();
    void recv();
};
#endif // WIDGET_H
