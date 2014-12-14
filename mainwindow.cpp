#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vertex.h"
#include "edge.h"

//class Arrow : public QGraphicsLineItem {
//    QGraphicsRectItem* from;
//    QGraphicsRectItem* to;

//    Arrow(QGraphicsRectItem* from, QGraphicsRectItem* to, QGraphicsItem *parent):
//        from(from), to(to), parent(parent)
//    {
//        setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//    }

//    void updatePosition() {
//        QLineF line(mapFromItem(from, 0, 0), mapFromItem(to, 0, 0));
//        setLine(line);
//    }

////    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
////    }
//};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    auto v1 = new Vertex(0);
    v1->setBrush(QBrush(Qt::red));
    scene->addItem(v1);

    for (int i = 0; i < 20; i++) {
        auto v2 = new Vertex(0);
        v2->setBrush(QBrush(Qt::blue));
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
