#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vertex.h"
#include "edge.h"

static QColor randomColor() {
    auto r = 100 + rand() % 100;
    auto g = 100 + rand() % 100;
    auto b = 100 + rand() % 100;

    return QColor(r, g, b);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   

    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);

    auto v1 = new Vertex(0);
    v1->setBrush(QBrush(randomColor()));
    scene->addItem(v1);

    for (int i = 0; i < 20; i++) {
        auto v2 = new Vertex(0);
        v2->setBrush(QBrush(randomColor()));
        scene->addItem(v2);
        v2->setX(80 * (i / 5 + 1) * std::cos(i));
        v2->setY(80 * (i / 5 + 1) * std::sin(i));

        graphConnect(v1, v2);

        v1->repaintEdges();
        v2->repaintEdges();

        v1 = v2;
    }

    repaint();

//    connect(ui->exitButton, SIGNAL(clicked(), SLOT(close())));
//    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
//    connect(ui->exitButton, &QPushButton::clicked, this, [this]() { this->close(); });
}

void MainWindow::graphConnect(Vertex* v1, Vertex* v2) {
    Edge* edge = new Edge(v1, v2);
    scene->addItem(edge);

    v1->edges.push_back(edge);
    v2->edges.push_back(edge);
}

MainWindow::~MainWindow()
{
    delete ui;
}
