#include <QDebug>
#include <QApplication>
#include "lib/logger.hpp"
#include "lib/graph.hpp"
#include "mainwindow.h"

#include "lib/adjacency_list.h"

int app(int argc, char *argv[]) {

    QApplication a(argc, argv);

    Graph* g = new Graph;
    Vertex& v1 = g->add_vertex();
    Vertex& v2 = g->add_vertex();
    Vertex& v3 = g->add_vertex();
    Vertex& v4 = g->add_vertex();
    Vertex& v5 = g->add_vertex();

    g->connect(v1, v2);
//    g->toggleEdge(v1->value, v2->value);
    g->connect(v2, v3);
    g->connect(v3, v4);
    g->connect(v4, v5);

    MainWindow w{g};

    w.show();

    return a.exec();
}

int main(int argc, char *argv[])
{
  return app(argc, argv);
}
