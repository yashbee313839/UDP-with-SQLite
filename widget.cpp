#include "widget.h"

#include <QtNetwork>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QDebug>
#include <QtSql>
#include<QFileInfo>
#include <QString>

Widget::Widget(QWidget *parent)
: QWidget(parent)
{
setWindowTitle("UDP Receiver");

socket=new QUdpSocket(this);
socket->bind(QHostAddress::Any, 5000);
connect(socket, SIGNAL(readyRead()), this, SLOT(datagramRecv()));

QVBoxLayout *layout=new QVBoxLayout(this);

trace=new QTextEdit(this);
trace->setReadOnly(true);
trace->append("UDP Trace:");
layout->addWidget(trace);
}

Widget::~Widget(){}

void Widget::datagramRecv(){
QByteArray data;
QHostAddress host;
quint16 port;

while(socket->hasPendingDatagrams()){
    data.resize(socket->pendingDatagramSize());
    socket->readDatagram(data.data(), data.size(), &host, &port);

    QString portStr;
    portStr.setNum(ulong(port));
    QString splitData(data);
    QStringList ex=splitData.split(' ');

    trace->append(QString("%1:%2 -> %3").arg(host.toString(), portStr, data));

    QSqlDatabase  mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/cfast/database3.db");
    mydb.open();
    QSqlQuery* qry=new QSqlQuery(mydb);
    qry->prepare("create table if not exists "+ex[0]+"(ID varchar(10),Range varchar(10),Azimuth varchar(10),Height varchar(10),Speed varchar(10),Time varchar(10))");
    if(qry->exec())
        qDebug()<<"Created";
    else
        qDebug() << "Not created";
    qry->prepare("insert into "+ex[0]+" values('"+ex[0]+"','"+ex[1]+"','"+ex[2]+"','"+ex[3]+"','"+ex[4]+"','"+ex[5]+"')");
    if(qry->exec())
        qDebug() << "Inserted";
    else
        qDebug() <<"Not Inserted"       ;
    mydb.close();


}
}
