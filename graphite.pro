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
    src/logger.cpp \
    src/bfs.cpp \
    src/dfs.cpp \
    src/edge.cpp \
    src/graph.cpp \
    src/vertex.cpp \
    src/dijkstra.cpp \
    src/search.cpp \
    src/euler.cpp \
    src/jarnik.cpp \
    src/gui/edge_graphics_item.cpp \
    src/gui/vertex_graphics_item.cpp \
    src/gui/edge_weight_text.cpp \

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
    include/gui/vertex_graphics_item.h \
    include/gui/edge_graphics_item.h \
    include/gui/edge_weight_text.h \

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
