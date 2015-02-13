#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include <cassert>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/vertex_graphics_item.h"
#include "gui/edge_graphics_item.h"
#include "lib/bfs.hpp"
#include "lib/logger.hpp"

MainWindow::MainWindow(Graph *graph, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), graph_(graph)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-1500, -1500, 3000, 3000);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    global_logger_logView_ = ui->txtLogView;

    reloadModel();
}

MainWindow::~MainWindow() { delete ui; }

static bool reloading = false;

/// Reloads the whole UI based on the model. Everything is first removed,
/// and then re-created in the same coordinates, so that the user notice anything.
void MainWindow::reloadModel()
{
    qDebug() << "Reloading model";
    reloading = true;

    int selectedVertexValue = -1;

    if (scene->selectedItems().size() == 1) {
        VertexGraphicsItem* selection = dynamic_cast<VertexGraphicsItem*>(scene->selectedItems().at(0));

        if (selection) {
            selectedVertexValue = selection->value();
        }
    }

    // TODO - promyslet
//    selectedVertex_ = nullptr;

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
            graphConnect(vgi, vgi_map[e.to], &e);
            vgi->repaintEdges();
        }
    }

    reloading = false;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_A:
        on_addVertex_clicked(); break;
    case Qt::Key_C:
        on_addEdge_clicked(); break;
    case Qt::Key_D:
        delete_selection(); break;
    case Qt::Key_F:
        searchToggle(true); break;
    case Qt::Key_N:
        searchStep(); break;
    case Qt::Key_O:
        changeOrientation(); break;
    case Qt::Key_T:
        searchToggle(false); break;
    case Qt::Key_P:
        printDebugInfo(); break;
    case Qt::Key_R:
        if (graph_->start() && graph_->end()) {
            graph_->clear_metadata();
            bfs_ = new BFS(*graph_, graph_->start(), graph_->end());
            reloadModel();
        }
        break;
    }
}

void MainWindow::delete_selection()
{
    if (scene->selectedItems().size() == 1) {
        QGraphicsItem *selectedItem = scene->selectedItems().at(0);

        if (VertexGraphicsItem *vgi = dynamic_cast<VertexGraphicsItem *>(selectedItem)) {
            if (connectionVertex_ == vgi->value()) {
                connectionVertex_ = -1; }

            graph_->removeVertex(vgi->vertex);

        } else if (EdgeGraphicsItem *egi = dynamic_cast<EdgeGraphicsItem *>(selectedItem)) {
            auto from = egi->from;
            auto to = egi->to;

            graph_->disconnect(from->vertex->value, to->vertex->value);
        } else { qDebug() << "Trying to delete something unknown"; }
    }

    reloadModel();
}

void MainWindow::on_addVertex_clicked()
{
    auto v = graph_->add_vertex();
    auto pos = ui->graphicsView->mapToScene(mapFromGlobal(QCursor::pos()));
    v->x = pos.x();
    v->y = pos.y();

    reloadModel();
}

void MainWindow::on_addEdge_clicked()
{
    VertexGraphicsItem* current = selectedVertex();
    if (current) {
        // If we already had one selected, revert the selection color
        if (connectionVertex_ != -1) {
            if (current->value() != connectionVertex_) {
                for	(VertexGraphicsItem* vgi : vertices_) {
                    if (vgi->value() == connectionVertex_) {
                        vgi->selected(false); } }

                graph_->connect(current->value(), connectionVertex_);

                // Reset the selection after we connect the vertices
                connectionVertex_ = -1;
                reloadModel();
                log_event("Edge added");
            }
        } else {
            current->selected(true);
            connectionVertex_ = current->value();
            reloadModel();
        }
    }
}

/// isStart - true for start vertex, false for end vertex
void MainWindow::searchToggle(bool isStart)
{
    VertexGraphicsItem* current = selectedVertex();
    if (current) {
        log_event(QString("searchToggle(%1) on vertex %2").arg(isStart).arg(current->vertex->value).toStdString().c_str());
        if (isStart) {
            graph_->set_start(current->vertex);
        } else {
            graph_->set_end(current->vertex); }

        reloadModel();

    } else {
        QMessageBox box;
        box.setText("Select a vertex to begin search.");
        box.exec();
    }
}

void MainWindow::searchStep()
{
    if (graph_->search_ready() && bfs_) {
        qDebug () << "Stepping search" << bfs_->step();
        reloadModel();
    } else {
        qDebug() << "Search isn't ready yet.";
    }
}

void MainWindow::changeOrientation()
{
    EdgeGraphicsItem* egi;
    if (scene->selectedItems().size() > 0 && (egi = dynamic_cast<EdgeGraphicsItem*>(scene->selectedItems().at(0)))) {
        graph_->toggleEdge(egi->from->value(), egi->to->value());
        reloadModel();
        log_event("Changed orientation");
    } else {
        log_event("Failed to change, it aint an edge");
    }
}

void MainWindow::printDebugInfo()
{
    std::stringstream ss;
    ss << *graph_;
    qDebug() << ss.str().c_str();
}

/// Returns a selected vertex if there is one, otherwise nullptr.
VertexGraphicsItem* MainWindow::selectedVertex() const
{
    VertexGraphicsItem* current = nullptr;

    if (scene->selectedItems().size() > 0) {
        current = dynamic_cast<VertexGraphicsItem*>(scene->selectedItems().at(0));
    }

    return current;
}

void MainWindow::on_actionNew_clicked()
{
    graph_ = new Graph();
    connectionVertex_ = -1;
    reloadModel();
    log_event("New graph");
}

void MainWindow::on_actionSave_clicked()
{
    log_event("Save");
}

void MainWindow::on_actionSaveAs_clicked()
{
    auto file = QFileDialog::getSaveFileName();

    if (!file.isNull()) {
        std::ofstream fs(file.toStdString());
        fs << *graph_;
        log_event("Graph saved");
    } else {
        log_event("Dialog canceled"); }
}

void MainWindow::on_actionOpen_clicked()
{
    // TODO - nastavit vsem streamum aby vyhazovaly vyjimky
    auto file = QFileDialog::getOpenFileName();

    if (!file.isNull()) {
        std::ifstream fs(file.toStdString());
        graph_ = Graph::parse_stream(fs);
        connectionVertex_ = -1;
        reloadModel();

        log_event("Graph loaded");
    } else {
        log_event("Dialog canceled"); }
}

/// Used to add a graphical edge between two vertices. Only ever call this from reloadModel.
void MainWindow::graphConnect(VertexGraphicsItem *v1, VertexGraphicsItem *v2, Edge* edge) {
    assert(reloading);
    auto egi = new EdgeGraphicsItem(v1, v2, edge);
    scene->addItem(egi);

    v1->edges.push_back(egi);
    v2->edges.push_back(egi);
}
