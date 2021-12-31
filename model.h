#ifndef MODEL_H
#define MODEL_H

#include "graph.h"

#include <QAbstractTableModel>

#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

class Model: public QAbstractTableModel {
private:
    Graph* graph;
public:
    Model();
    int rowCount() const;


public slots:
    void newColumns(size_t =1);
    void insertColumn(size_t);
    void removeColumn(size_t);
    void newRows(size_t =1);
    void insertRow(size_t);
    void removeRow(size_t);
};

#endif // MODEL_H
