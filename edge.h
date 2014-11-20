#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>

class Vertex;

class Edge : public QGraphicsLineItem
{
public:
    Edge(Vertex* from, Vertex* to);

    void updatePosition();
private:
    Vertex* from;
    Vertex* to;
};

#endif // EDGE_H
