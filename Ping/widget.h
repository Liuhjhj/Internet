#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <ping.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void startPing();
    void stopPing();
    void setTable(int row, int col, char *data);

private:
    Ui::Widget *ui;
    void initSignalSlots();
    class ping *p;
};
#endif // WIDGET_H
