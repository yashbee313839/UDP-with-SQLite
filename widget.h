#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QUdpSocket;
class QTextEdit;

class Widget : public QWidget
{
Q_OBJECT

public:
Widget(QWidget *parent = 0);
~Widget();

private:
QUdpSocket *socket;
QTextEdit *trace;

public slots:
void datagramRecv();
};

#endif // WIDGET_H
