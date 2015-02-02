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
#include "lib/bfs.hpp"

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
    } else if (e->key() == Qt::Key_F) {
        searchToggle(true);
    } else if (e->key() == Qt::Key_T) {
        searchToggle(false);
    } else if (e->key() == Qt::Key_N) {
        searchStep();
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

            // TODO - check where else this needs to be done
            if (vgi == selectedVertex_) selectedVertex_ = nullptr;

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

    auto pos = ui->graphicsView->mapToScene(mapFromGlobal(QCursor::pos()));
    vgi->setCoordinates(pos.x(), pos.y());

    vertices_.push_back(vgi);
    scene->addItem(vgi);
}

void MainWindow::on_addEdge_clicked()
{
    VertexGraphicsItem* current = selectedVertex();
    if (current) {
        // If we already had one selected, revert the selection color
        if (selectedVertex_) {
            if (current != selectedVertex_) {
                selectedVertex_->vertex->color = vertex_color::white;

                graph_->connect(current->value(), selectedVertex_->value());
                reloadModel();

                // Reset the selection after we connect the vertices
                selectedVertex_ = nullptr;
            }
        } else {
            selectedVertex_ = static_cast<VertexGraphicsItem *>(scene->selectedItems().at(0));
            selectedVertex_->vertex->color = vertex_color::gray;
            selectedVertex_->update();
        }
    }
}

void MainWindow::graphConnect(VertexGraphicsItem *v1, VertexGraphicsItem *v2)
{
    auto edge = new EdgeGraphicsItem(v1, v2);
    scene->addItem(edge);

    v1->edges.push_back(edge);
    v2->edges.push_back(edge);
}

void MainWindow::searchToggle(bool isStart) // true for start vertex, false for end vertex
{
    VertexGraphicsItem* current = selectedVertex();
    if (current) {
        if (isStart) {
            graph_->set_start(current->vertex);
        } else {
            graph_->set_end(current->vertex);
        }
        reloadModel();
    } else {
        QMessageBox box;
        box.setText("Select a vertex to begin search.");
        box.exec();
    }
}

void MainWindow::searchStep()
{
    if (graph_->search_ready()) {
//        static BFS bfs = BFS(*graph_, graph_->start, graph_->end);
//        bfs.step();
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
