#ifndef TABLE_H
#define TABLE_H

#include "labels.h"

#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

class Table {
protected:
    size_t rows;
    size_t columns;

    vector<vector<double>> t;

public:
    Table(size_t =0, size_t =0);
    Table(const Table&);
    ~Table() =default;

    int getRows() const;
    int getColumns() const;

    double getData(size_t, size_t) const;
    double& setData(size_t, size_t);

    void newColumns(size_t =1);
    void insertColumn(size_t);
    void removeColumn(size_t);
    void newRows(size_t =1);
    void insertRow(size_t);
    void removeRow(size_t);

    vector<double>& operator [](size_t);
};

#endif // TABLE_H
