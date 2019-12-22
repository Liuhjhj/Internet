#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <client.h>
#include "iostream"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

//声明公共函数,变量和类
public:
    //声明构造方法
    Widget(QWidget *parent = nullptr);
    //我也不知道这是干啥的
    ~Widget();
    //声明公共类
    class client *c;

//声明私有方法
private:
    //声明私有类
    Ui::Widget *ui;
    //声明私有方法
    void initSignalSlots();

//声明公共槽函数
//使用槽函数和自定义信号之前必须在头文件声明
public slots:
    void setStatus(QString data);
    void exit();
    void send();
    void recv(QString mess);
};
#endif // WIDGET_H
