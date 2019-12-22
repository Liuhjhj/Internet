#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    class server *s;

private:
    Ui::Widget *ui;

private slots:
    void startServer();

};
#endif // WIDGET_H
