#include <QDebug>
#include <QApplication>
#include <QObject>
#include <QTextStream>
#include <algorithm>
#include <vector>

#include "lib/graph.hpp"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //    qWarning("Hello console!");

    //    QString msg("This is a qt string");
    //    int x = 20;

    //    QTextStream out(stdout);
    //    out.setFieldWidth(20);
    //    out.setPadChar('*');
    //    out << msg << x << "hotov";

    QApplication a(argc, argv);

    Graph *g = new Graph();
    Vertex *v1 = g->add_vertex(1);
    Vertex *v2 = g->add_vertex(2);
    Vertex *v3 = g->add_vertex(3);
    g->add_vertex(4);
    g->add_vertex(5);
    g->add_vertex(6);
    g->add_vertex(7);
    g->add_vertex(8);
    g->add_vertex(9);
    g->add_vertex(10);
    g->add_vertex(11);
    g->add_vertex(12);

    g->connect(1, 2);

    qDebug() << "is conn?" << g->is_connected(1, 2);
    g->disconnect(1, 2);
    qDebug() << "is conn?" << g->is_connected(1, 2);

    MainWindow w(g);

    w.show();

    return a.exec();
}
