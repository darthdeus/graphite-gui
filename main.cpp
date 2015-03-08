#include <QDebug>
#include <QApplication>
#include <QObject>
#include <QTextStream>
#include <algorithm>
#include <vector>

#include "lib/logger.hpp"
#include "lib/graph.hpp"
#include "mainwindow.h"

int app(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Graph *g = new Graph();
    Vertex *v1 = g->add_vertex();
    Vertex *v2 = g->add_vertex();
    Vertex *v3 = g->add_vertex();
    Vertex *v4 = g->add_vertex();
    Vertex *v5 = g->add_vertex();

    g->connect(v1->value, v2->value);
//    g->toggleEdge(v1->value, v2->value);
    g->connect(v2->value, v3->value);
    g->connect(v3->value, v4->value);
    g->connect(v4->value, v5->value);

    MainWindow w{g};

    w.show();

    return a.exec();
}

int main(int argc, char *argv[])
{
  return app(argc, argv);
}
