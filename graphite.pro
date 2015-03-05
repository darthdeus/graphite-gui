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
    lib/store.cpp \
    lib/vertex.cpp \
    gui/edge_graphics_item.cpp \
    gui/vertex_graphics_item.cpp \
    gui/edge_weight_text.cpp \
    lib/dijkstra.cpp \
    lib/search.cpp \
    lib/euler.cpp

HEADERS  += \
    mainwindow.h \
    lib/logger.hpp \
    lib/dfs.hpp \
    lib/edge.hpp \
    lib/graph.hpp \
    lib/store.hpp \
    lib/vertex.hpp \
    lib/bfs.hpp \
    gui/vertex_graphics_item.h \
    gui/edge_graphics_item.h \
    gui/edge_weight_text.h \
    lib/dijkstra.hpp \
    lib/search.hpp \
    lib/euler.hpp

FORMS    += \
    mainwindow.ui

CONFIG += c++11

release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
