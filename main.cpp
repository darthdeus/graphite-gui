#include <QDebug>
#include <QApplication>
#include <QObject>
#include <QTextStream>
#include <algorithm>
#include <vector>
#include <utility>

#include "lib/logger.hpp"
#include "lib/graph.hpp"
#include "mainwindow.h"

#include "lib/adjacency_list.h"

int app(int argc, char *argv[]) {

    QApplication a(argc, argv);

	adjacency_list graph;
	auto& v1 = graph.add();
	auto& v2 = graph.add();
	auto& v3 = graph.add();
	auto& v4 = graph.add();
	auto& v5 = graph.add();

	graph.connect(v1, v2);
	graph.connect(v2, v3);
	graph.connect(v3, v4);
	graph.connect(v4, v5);

    MainWindow w{&graph};
    w.show();

	for (auto it = graph.dfs_begin(); it != graph.dfs_end(); ++it) {
		std::string m = std::to_string(it->id());
		log_event(m.c_str());
	}
	log_event("hehe");

    return a.exec();
}

int main(int argc, char *argv[])
{
  return app(argc, argv);
}
