#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T23:58:28
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphite
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    gui/vertex.cpp \
    gui/edge.cpp

HEADERS  += \
    mainwindow.h \
    gui/edge.h \
    gui/vertex.h

FORMS    += \
    mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
