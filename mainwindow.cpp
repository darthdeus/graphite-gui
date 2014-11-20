#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

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

//    QGraphicsScene scene;

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    auto r1 = new Vertex(0);
    r1->setBrush(QBrush(Qt::red));
    scene->addItem(r1);

    auto r2 = new Vertex(0);
    r2->setBrush(QBrush(Qt::blue));
    scene->addItem(r2);

    auto r3 = new Vertex(0);
    r3->setBrush(QBrush(Qt::blue));
    scene->addItem(r3);

    auto r4 = new Vertex(0);
    r4->setBrush(QBrush(Qt::blue));
    scene->addItem(r4);

    graphConnect(r1, r2);
    graphConnect(r2, r3);
    graphConnect(r4, r3);

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
