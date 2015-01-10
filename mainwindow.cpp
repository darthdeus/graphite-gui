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
    : QMainWindow(parent), ui(new Ui::MainWindow), graph_(graph)
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
    for (VertexGraphicsItem *vertex : vertices_) {
        for (EdgeGraphicsItem *edge : vertex->edges) {
            if (scene->items().contains(edge)) {
                scene->removeItem(edge);
            }
        }
        vertex->clearEdges();

        for (size_t i = 0; i < rand() % vertices_.size(); i++) {
            auto index = rand() % vertices_.size();
            auto v2 = vertices_[index];

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
    vertices_.clear();

    int i = 0;
    for	(std::unique_ptr<Vertex>& v : graph_->list) {
        // TODO - store the vertex value
        auto vgi = new VertexGraphicsItem(v.get());

        vgi->setBrush(QBrush(randomColor()));

        vgi->setX(80 * (i / 5 + 1) * std::cos(i));
        vgi->setY(80 * (i / 5 + 1) * std::sin(i));

        vertices_.push_back(vgi);
        scene->addItem(vgi);

        i++;
    }
}

void MainWindow::on_pushButton_clicked()
{
    auto v = graph_->add_vertex(10);

    auto vgi = new VertexGraphicsItem(v);

    vgi->setBrush(QBrush(randomColor()));

    vertices_.push_back(vgi);
    scene->addItem(vgi);
}
