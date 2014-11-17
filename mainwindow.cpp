#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vertex.h"

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

    auto scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    auto r1 = new Vertex(0);
    r1->setRect(-5, 10, 50, 50);
    r1->setBrush(QBrush(Qt::red));

    scene->addItem(r1);

    auto r2 = new Vertex(0);
    r2->setRect(50, 10, 50, 50);
    r2->setBrush(QBrush(Qt::blue));

    scene->addItem(r2);


//    arrow = new Arrow(r1, r2, this);
//    ui->graphicsView->setScene(&scene);
//    ui->graphicsView->show();

//    connect(ui->exitButton, SIGNAL(clicked(), SLOT(close())));
//    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
//    connect(ui->exitButton, &QPushButton::clicked, this, [this]() { this->close(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
