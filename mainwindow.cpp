#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <cmath>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/vertex_graphics_item.h"
#include "gui/edge_graphics_item.h"

static QColor randomColor()
{
    auto r = 100 + rand() % 100;
    auto g = 100 + rand() % 100;
    auto b = 100 + rand() % 100;

    return QColor(r, g, b);
}

MainWindow::MainWindow(Graph *graph, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), graph(graph)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);

    randomizeVertices();
    //    connect(ui->exitButton, SIGNAL(clicked(), SLOT(close())));
    //    connect(ui->exitButton, &QPushButton::clicked, this,
    //    &MainWindow::close);
    //    connect(ui->exitButton, &QPushButton::clicked, this, [this]() {
    //    this->close(); });
}

void MainWindow::graphConnect(VertexGraphicsItem *v1, VertexGraphicsItem *v2)
{
    auto edge = new EdgeGraphicsItem(v1, v2);
    scene->addItem(edge);

    v1->edges.push_back(edge);
    v2->edges.push_back(edge);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_randomizeEdges_clicked()
{
    for (VertexGraphicsItem *vertex : _vertices) {
        for (EdgeGraphicsItem *edge : vertex->edges) {
            if (scene->items().contains(edge)) {
                scene->removeItem(edge);
            }
        }
        vertex->clearEdges();

        for (int i = 0; i < rand() % 3; i++) {
            auto index = rand() % _vertices.size();
            auto v2 = _vertices[index];

            if (v2 != vertex) {
                graphConnect(vertex, v2);
            }
        }

        vertex->repaintEdges();
    }

    ui->graphicsView->repaint();
}

void MainWindow::randomizeVertices()
{
    _vertices.clear();

    int i = 0;
    for	(std::unique_ptr<Vertex>& v : graph->list) {
        // TODO - store the vertex value
        auto vgi = new VertexGraphicsItem(v.get());

        vgi->setBrush(QBrush(randomColor()));

        vgi->setX(80 * (i / 5 + 1) * std::cos(i));
        vgi->setY(80 * (i / 5 + 1) * std::sin(i));

        _vertices.push_back(vgi);
        scene->addItem(vgi);

        i++;
    }

//    auto v1 = new VertexGraphicsItem(0);
//    v1->setBrush(QBrush(randomColor()));
//    scene->addItem(v1);

//    _vertices.push_back(v1);

//    for (int i = 0; i < 20; i++) {
//        auto v2 = new VertexGraphicsItem(0);
//        v2->setBrush(QBrush(randomColor()));
//        scene->addItem(v2);
//        v2->setX(80 * (i / 5 + 1) * std::cos(i));
//        v2->setY(80 * (i / 5 + 1) * std::sin(i));

//        _vertices.push_back(v2);

//        graphConnect(v1, v2);

//        v1->repaintEdges();
//        v2->repaintEdges();

//        v1 = v2;
//    }
}
