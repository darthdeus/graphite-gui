#include <QDebug>
#include <QApplication>
#include "include/logger.h"
#include "include/graph.h"
#include "mainwindow.h"

int app(int argc, char* argv[]) {
  QApplication a(argc, argv);

  Graph* g = new Graph;
  Vertex& v1 = g->add_vertex();
  Vertex& v2 = g->add_vertex();
  Vertex& v3 = g->add_vertex();
  Vertex& v4 = g->add_vertex();
  Vertex& v5 = g->add_vertex();

  g->connect(v1, v2);
  g->connect(v2, v3);
  g->connect(v3, v4);
  g->connect(v4, v5);

  MainWindow w{g};

  w.show();

  return a.exec();
}

int main(int argc, char* argv[]) { return app(argc, argv); }
