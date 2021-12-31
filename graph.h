#ifndef GRAPH_H
#define GRAPH_H

#include "table.h"
#include "labels.h"

#include <iostream>
//#include <cstdlib> //size_t gia' in iostream
#include <vector>
#include <string>
using std::vector;
using std::string;

class Graph: public Table {
public:
    std::string name;

    Labels lR;
    Labels lC;
public:
    Graph(size_t =0, size_t =0, std::string ="graph");

    std::string getName();

    void newColumns(size_t =1);
    void insertColumn(size_t);
    void removeColumn(size_t);
    void newRows(size_t =1);
    void insertRow(size_t);
    void removeRow(size_t);

    double getRowPercentage(size_t, size_t);
    double getColumnPercentage(size_t, size_t);

    //Console
    void printName();
    void printTable();
};

#endif // GRAPH_H
