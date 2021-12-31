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
    Q_OBJECT

private:
    Graph* graph;

public:
    Model(QObject* =nullptr);
    ~Model();

    int rowCount(const QModelIndex& =QModelIndex()) const override;
    int columnCount(const QModelIndex& =QModelIndex()) const override;
    QVariant data(const QModelIndex&, int =Qt::DisplayRole) const override;

public slots:
    void newColumns(size_t =1);
    void insertColumn(size_t);
    void removeColumn(size_t);
    void newRows(size_t =1);
    void insertRow(size_t);
    void removeRow(size_t);
};

#endif // MODEL_H
