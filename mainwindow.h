#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "lib/graph.hpp"

class QGraphicsLineItem;
class QGraphicsScene;

class VertexGraphicsItem;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Graph* graph, QWidget *parent = 0);
    ~MainWindow();

    void graphConnect(VertexGraphicsItem* v1, VertexGraphicsItem* v2);

    void randomizeVertices();

    void keyReleaseEvent(QKeyEvent *);
private slots:
    void on_randomizeEdges_clicked();
    void on_addVertex_clicked();
    void on_addEdge_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsLineItem *arrow;
    QGraphicsScene *scene;

    Graph* graph_;
    std::vector<VertexGraphicsItem*> vertices_;

    // Used for adding an edge, should be always cleared
    VertexGraphicsItem* selectedVertex_ = nullptr;
};

#endif // MAINWINDOW_H
