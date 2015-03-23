#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "lib/bfs.hpp"
#include "lib/dfs.hpp"
#include "lib/dijkstra.hpp"
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

    VertexGraphicsItem *selectedVertex() const;
    Ui::MainWindow *ui;

public slots:
private slots:
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionOpen_triggered();

    void on_actionAddVertex_triggered();
    void on_actionConnectWithEdge_triggered();
    void on_actionDelete_triggered();
    void on_actionChangeOrientation_triggered();

    void on_actionSearchFrom_triggered();
    void on_actionSearchTo_triggered();
    void on_actionNextStep_triggered();
    void on_actionRestartAlgorithm_triggered();
    void on_actionPrintGraphToStdout_triggered();

    void on_actionRandomDirectedEdges_triggered();
    void on_actionRandomGraph_triggered();
    void on_actionRandomEulerianGraph_triggered();
    void on_actionRandomEdgeWeights_triggered();

    void on_actionMakeUndirected_triggered();
    void on_actionExportGraphvizDotFile_triggered();

private:
    void graphConnect(VertexGraphicsItem* v1, VertexGraphicsItem* v2, Edge* edge);
    void searchToggle(bool start);
    void searchStep();
    void setEdgeWeight(int value);

    QGraphicsScene *scene;
    Search* search_ = nullptr;

    Graph* graph_;
    std::vector<VertexGraphicsItem*> vertices_;

    /// Used for adding an edge, should be always nullified afterwards
    int connectionVertex_ = -1;
};

#endif // MAINWINDOW_H
