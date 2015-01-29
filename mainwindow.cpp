#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

#include <cmath>
#include <vector>
#include <unordered_map>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/vertex_graphics_item.h"
#include "gui/edge_graphics_item.h"

static QColor randomColor()
{
//    auto r = 100 + rand() % 100;
//    auto g = 100 + rand() % 100;
//    auto b = 100 + rand() % 100;

    return QColor(120, 150, 130);
//    return QColor(r, g, b);
}

MainWindow::MainWindow(Graph *graph, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), graph_(graph)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-1500, -1500, 3000, 3000);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    reloadModel();
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::reloadModel()
{
    int selectedVertexValue = -1;

    if (scene->selectedItems().size() == 1) {
        VertexGraphicsItem* selection = dynamic_cast<VertexGraphicsItem*>(scene->selectedItems().at(0));

        if (selection) {
            selectedVertexValue = selection->value();
        }
    }

    vertices_.clear();
    scene->clear();


    std::unordered_map<Vertex *, VertexGraphicsItem *> vgi_map;

    int i = 0;
    for (std::unique_ptr<Vertex> &v : graph_->list) {
        auto vgi = new VertexGraphicsItem(v.get());

        vgi->setBrush(QBrush(randomColor()));
        if (!vgi->hasCoordinates()) {
            vgi->setCoordinates(80 * (i / 5 + 1) * std::cos(i),
                                80 * (i / 5 + 1) * std::sin(i));
        }

        vertices_.push_back(vgi);
        scene->addItem(vgi);

        if (v->value == selectedVertexValue) {
            vgi->setSelected(true);
        }

        vgi_map[v.get()] = vgi;

        i++;
    }

    for (std::unique_ptr<Vertex> &v : graph_->list) {
        Vertex *vertex = v.get();

        VertexGraphicsItem *vgi = vgi_map[vertex];
        for (Edge &e : vertex->edges) {
            graphConnect(vgi, vgi_map[e.to]);
            vgi->repaintEdges();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_A) {
        on_addVertex_clicked();
    } else if (e->key() == Qt::Key_C) {
        on_addEdge_clicked();
    } else if (e->key() == Qt::Key_D) {
        delete_selection();
        reloadModel();
    } else if (e->key() == Qt::Key_S) {
        toggleSearch();
    }
}

void MainWindow::delete_selection()
{
    if (scene->selectedItems().size() == 1) {
        QGraphicsItem *selectedItem = scene->selectedItems().at(0);

        if (VertexGraphicsItem *vgi = dynamic_cast<VertexGraphicsItem *>(selectedItem)) {
            if (selectedVertex_ == vgi) {
                selectedVertex_ = nullptr;
            }

            graph_->removeVertex(vgi->vertex);
        } else if (EdgeGraphicsItem *egi = dynamic_cast<EdgeGraphicsItem *>(selectedItem)) {
            auto from = egi->from;
            auto to = egi->to;

            graph_->disconnect(from->vertex->value, to->vertex->value);

        } else {
            qDebug() << "Trying to delete something unknown";
        }
    }
}

void MainWindow::on_addVertex_clicked()
{
    auto v = graph_->add_vertex();

    auto vgi = new VertexGraphicsItem(v);
    vgi->setBrush(QBrush(randomColor()));

    auto pos = ui->graphicsView->mapToScene(mapFromGlobal(QCursor::pos()));
    vgi->setCoordinates(pos.x(), pos.y());

    vertices_.push_back(vgi);
    scene->addItem(vgi);
}

void MainWindow::on_addEdge_clicked()
{
    if (scene->selectedItems().size() > 0) {
        VertexGraphicsItem* current = dynamic_cast<VertexGraphicsItem *>(scene->selectedItems().at(0));

        if (!current) return;

        // If we already had one selected, revert the selection color
        if (selectedVertex_) {
            if (current != selectedVertex_) {
                selectedVertex_->setBrush(QBrush(randomColor()));

                graph_->connect(current->value(), selectedVertex_->value());
                reloadModel();

                // Reset the selection after we connect the vertices
                selectedVertex_ = nullptr;
            }
        } else {
            selectedVertex_ = static_cast<VertexGraphicsItem *>(scene->selectedItems().at(0));
            selectedVertex_->setBrush(QBrush(QColor(0, 0, 0)));
        }
    }
}

void MainWindow::graphConnect(VertexGraphicsItem *v1, VertexGraphicsItem *v2)
{
    auto edge = new EdgeGraphicsItem(v1, v2);
    scene->addItem(edge);

    //    graph_->connect(v1->vertex->value, v2->vertex->value);
    v1->edges.push_back(edge);
    v2->edges.push_back(edge);
}

void MainWindow::toggleSearch()
{
    VertexGraphicsItem* current = selectedVertex();
    if (current) {

    } else {
        QMessageBox box;
        box.setText("Select a vertex to begin search.");
        box.exec();
    }
}

/// Returns a selected vertex if there is one, otherwise nullptr.
VertexGraphicsItem *MainWindow::selectedVertex()
{
    VertexGraphicsItem* current = nullptr;
    if (scene->selectedItems().size() > 0) {
        current = dynamic_cast<VertexGraphicsItem*>(scene->selectedItems().at(0));
    }

    return current;
}
