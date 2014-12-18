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
    gui/edge.cpp \
    lib/bfs.cpp \
    lib/dfs.cpp \
    lib/edge.cpp \
    lib/graph.cpp \
    lib/store.cpp \
    lib/vertex.cpp

HEADERS  += \
    mainwindow.h \
    gui/edge.h \
    gui/vertex.h \
    lib/bfs.hpp \
    lib/dfs.hpp \
    lib/edge.hpp \
    lib/graph.hpp \
    lib/store.hpp \
    lib/vertex.hpp

FORMS    += \
    mainwindow.ui

QMAKE_CXXFLAGS += -std=c++1y -stdlib=libc++
