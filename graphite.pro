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
    lib/logger.cpp \
    lib/bfs.cpp \
    lib/dfs.cpp \
    lib/edge.cpp \
    lib/graph.cpp \
    lib/vertex.cpp \
    lib/dijkstra.cpp \
    lib/search.cpp \
    lib/euler.cpp \
    lib/jarnik.cpp \
    gui/edge_graphics_item.cpp \
    gui/vertex_graphics_item.cpp \
    gui/edge_weight_text.cpp \

HEADERS  += \
    mainwindow.h \
    include/logger.h \
    include/dfs.h \
    include/edge.h \
    include/graph.h \
    include/vertex.h \
    include/bfs.h \
    include/dijkstra.h \
    include/search.h \
    include/euler.h \
    include/jarnik.h \
    include/utils.h \
    gui/vertex_graphics_item.h \
    gui/edge_graphics_item.h \
    gui/edge_weight_text.h \

FORMS    += \
    mainwindow.ui

CONFIG += c++11

release: DESTDIR = build/release
debug:   DESTDIR = build/debug

INCLUDEPATH += $$PWD/include

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
