#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "lib/bfs.hpp"
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

    void reloadModel();
    void keyReleaseEvent(QKeyEvent *);
    void delete_selection();

    VertexGraphicsItem *selectedVertex() const;
    Ui::MainWindow *ui;

public slots:
    void on_actionNew_clicked();
    void on_actionSave_clicked();
    void on_actionSaveAs_clicked();
    void on_actionOpen_clicked();

private:
    void on_addVertex_clicked();
    void on_addEdge_clicked();
    void graphConnect(VertexGraphicsItem* v1, VertexGraphicsItem* v2, Edge* edge);
    void searchToggle(bool start);
    void searchStep();
    void changeOrientation();
    void printDebugInfo();

    QGraphicsScene *scene;
    BFS* bfs_ = nullptr;

    Graph* graph_;
    std::vector<VertexGraphicsItem*> vertices_;

    /// Used for adding an edge, should be always nullified afterwards
    int connectionVertex_ = -1;
};

#endif // MAINWINDOW_H
