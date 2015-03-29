#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QComboBox>

#include <cassert>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <utility>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/vertex_graphics_item.h"
#include "gui/edge_graphics_item.h"
#include "gui/edge_weight_text.h"
#include "lib/bfs.hpp"
#include "lib/dfs.hpp"
#include "lib/dijkstra.hpp"
#include "lib/euler.hpp"
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

/// Reload the whole UI based on the model. Everything is first removed,
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

    vertices_.clear();
    scene->clear();

    std::unordered_map<Vertex *, VertexGraphicsItem *> vgi_map;

    int i = 0;
    for (std::unique_ptr<Vertex> &v : graph_->list) {
        auto vgi = new VertexGraphicsItem(v.get());

        if (!vgi->hasCoordinates()) {
            vgi->setCoordinates(115 * (i / 5 + 1) * std::cos(i),
                                115 * (i / 5 + 1) * std::sin(i));
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
    case Qt::Key_0: setEdgeWeight(0); break;
    case Qt::Key_1: setEdgeWeight(1); break;
    case Qt::Key_2: setEdgeWeight(2); break;
    case Qt::Key_3: setEdgeWeight(3); break;
    case Qt::Key_4: setEdgeWeight(4); break;
    case Qt::Key_5: setEdgeWeight(5); break;
    case Qt::Key_6: setEdgeWeight(6); break;
    case Qt::Key_7: setEdgeWeight(7); break;
    case Qt::Key_8: setEdgeWeight(8); break;
    case Qt::Key_9: setEdgeWeight(9); break;
    case Qt::Key_B:
        graph_->updateBridges();
        reloadModel();
    default: QMainWindow::keyReleaseEvent(e);
    }
}

void MainWindow::on_actionDelete_triggered()
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

void MainWindow::on_actionNextStep_triggered()
{
    if (graph_->search_ready() && search_) {
        search_->step();
        reloadModel();
    } else {
        qDebug() << "Search isn't ready yet.";
    }
}

void MainWindow::on_actionRestartAlgorithm_triggered()
{
    if (graph_->search_ready()) {

        auto text = ui->algList->currentText();
        if (text == "BFS") {
            graph_->clear_metadata(false);
            search_ = new BFS(*graph_, graph_->start(), graph_->end());
        } else if (text == "DFS") {
            graph_->clear_metadata(false);
            search_ = new DFS(*graph_, graph_->start(), graph_->end());
        } else if (text == "Dijkstra") {
            graph_->clear_metadata(true);
            search_ = new Dijkstra(*graph_, graph_->start());
        } else if (text == "Euler") {
            graph_->clear_metadata(false);
            search_ = new Euler(*graph_, graph_->start());
        } else {
            QMessageBox box;
            box.setText("No algorithm was selected.");
            box.exec();
        }

        search_->start();
        reloadModel();
    }
}

void MainWindow::on_actionPrintGraphToStdout_triggered()
{
    std::stringstream ss;
    ss << *graph_;
    qDebug() << ss.str().c_str();
}

void MainWindow::on_actionRandomDirectedEdges_triggered()
{
    // We can use pairs since they already handle comparisons properly.
    std::set<std::pair<int, int>> edges;

    for (auto& v: graph_->list) {
        for (Edge& e: v->edges) {
            edges.insert(std::make_pair(e.from->value, e.to->value));
        }
    }

    for (auto pair : edges) {
        if (rand() % 2 == 0) {
            graph_->toggleEdge(pair.first, pair.second);
        }
    }

    reloadModel();
    log_event("Randomized edges");
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

void MainWindow::on_actionNew_triggered()
{
    graph_ = new Graph();
    connectionVertex_ = -1;
    reloadModel();
    log_event("New graph");
}


void MainWindow::on_actionRandomGraph_triggered()
{
    graph_ = new Graph();
    connectionVertex_ = -1;

    Vertex* prev = graph_->add_vertex();

    std::queue<Vertex*> queue;
    queue.push(prev);

    // Randomized edge count, between 10-15
    int count = rand() % 6 + 10;

    while (count-- ) {
        Vertex* next = graph_->add_vertex();
        queue.push(next);

        graph_->connect(prev->value, next->value);
        prev = next;
    }

    while (!queue.empty()) {
        Vertex* top = queue.front();
        queue.pop();

        int index = (rand() % (graph_->list.size() - 1)) + 1;
        int dice = rand() % 6;

        if (top->value != index && dice > 2) {
            graph_->connect(top->value, index);
        }
    }

    reloadModel();
}

void MainWindow::on_actionRandomEulerianGraph_triggered()
{
    graph_ = new Graph();
    connectionVertex_ = -1;
    graph_->add_vertex();

    int cycle_count = 5 + rand() % 3;

    for (int i = 0; i < cycle_count; i++) {
        // Pick a random vertex
        int index = rand() % graph_->list.size();
        auto it = graph_->list.begin();
        std::advance(it, index);

        Vertex* v = it->get();
        Vertex* prev = v;

        int cycle_length = 2 + rand() % 2;
        for (int j = 0; j < cycle_length; j++) {
            Vertex* v0 = graph_->add_vertex();
            graph_->connect(prev->value, v0->value);
            prev = v0;
        }

        graph_->connect(prev->value, v->value);
    }

    reloadModel();
}

void MainWindow::on_actionRandomEdgeWeights_triggered()
{
    for (auto& v: graph_->list) {
        for (auto& e: v->edges) {
            e.weight = 1 + rand() % 9;
        }
    }

    reloadModel();
    log_event("edge weights randomized");
}

void MainWindow::on_actionMakeUndirected_triggered()
{
    // We can use pairs since they already handle comparisons properly.
    std::set<std::pair<int, int>> edges;

    for (auto& v: graph_->list) {
        for (Edge& e: v->edges) {
            edges.insert(std::make_pair(e.from->value, e.to->value));
        }
    }

    for (auto pair : edges) {
        graph_->disconnect(pair.first, pair.second);
        graph_->connect(pair.first, pair.second);
    }

    reloadModel();
    log_event("Removed orientation");
}

void MainWindow::on_actionSave_triggered()
{
    log_event("Save");
}

void MainWindow::on_actionSave_as_triggered()
{
    auto file = QFileDialog::getSaveFileName();

    if (!file.isNull()) {
        std::ofstream fs(file.toStdString());
        fs << *graph_;
        log_event("Graph saved");
    } else {
        log_event("Dialog canceled"); }
}

void MainWindow::on_actionOpen_triggered()
{
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

void MainWindow::on_actionAddVertex_triggered()
{
    auto v = graph_->add_vertex();
    auto pos = ui->graphicsView->mapToScene(mapFromGlobal(QCursor::pos()));
    v->x = pos.x();
    v->y = pos.y();

    reloadModel();
}

void MainWindow::on_actionConnectWithEdge_triggered()
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

void MainWindow::setEdgeWeight(int value) {
    EdgeWeightText *ewt;
    if (scene->selectedItems().count() == 1 && (ewt = dynamic_cast<EdgeWeightText*>(scene->selectedItems().at(0)))) {
        ewt->edge->weight = value;
        log_event(QString("Set edge weight %1").arg(value).toStdString().c_str());
        reloadModel();
    }
}

/// Used to add a graphical edge between two vertices. Only ever call this from reloadModel.
void MainWindow::graphConnect(VertexGraphicsItem *v1, VertexGraphicsItem *v2, Edge* edge) {
    assert(reloading);
    auto egi = new EdgeGraphicsItem(v1, v2, edge);
    scene->addItem(egi);

    v1->edges.push_back(egi);
    v2->edges.push_back(egi);
}

void MainWindow::on_actionChangeOrientation_triggered()
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

void MainWindow::on_actionSearchFrom_triggered()
{
    searchToggle(true);
}

void MainWindow::on_actionSearchTo_triggered()
{
    searchToggle(false);
}
