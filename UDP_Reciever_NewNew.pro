QT += core gui network sql

greaterThan(QT_MAJOR_VERSION,4):QT += widgets
TARGET = UDPReceiver
TEMPLATE = app

SOURCES += main.cpp \
    widget.cpp
widget.cpp

HEADERS += widget.h \
    widget.h
