#ifndef GRAPH_H
#define GRAPH_H

#include "table.h"
#include "labels.h"

#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

class Graph: public Table {
private:
    std::string name;

    Labels lR;
    Labels lC;

public:
    Graph(size_t =0, size_t =0, std::string ="graph");
    Graph(const Graph&);
    ~Graph() =default;

    std::string getName() const;
    std::string& setName();

    void newColumns(size_t =1);
    void insertColumn(size_t);
    void removeColumn(size_t);
    void newRows(size_t =1);
    void insertRow(size_t);
    void removeRow(size_t);

    string getRowLabel(size_t) const;
    string getColumnLabel(size_t) const;
    string& setRowLabel(size_t);
    string& setColumnLabel(size_t);
};

#endif // GRAPH_H
