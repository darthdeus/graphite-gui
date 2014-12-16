#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class QGraphicsLineItem;
class QGraphicsScene;

class Vertex;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void graphConnect(Vertex* v1, Vertex* v2);
private slots:
    void on_randomizeEdges_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsLineItem *arrow;
    QGraphicsScene *scene;

    std::vector<Vertex*> _vertices;
};

#endif // MAINWINDOW_H
