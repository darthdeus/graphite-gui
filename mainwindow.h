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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void graphConnect(VertexGraphicsItem* v1, VertexGraphicsItem* v2);
private slots:
    void on_randomizeEdges_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsLineItem *arrow;
    QGraphicsScene *scene;


    std::vector<VertexGraphicsItem*> _vertices;
};

#endif // MAINWINDOW_H
