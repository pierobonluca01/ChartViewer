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

public:
    Graph* graph;

public:
    Model(size_t =0, size_t =0, QString ="senza_titolo", QObject* =nullptr);
    virtual ~Model() =default;

    QString getName() const;
    void setName(const QString&);

    int rowCount(const QModelIndex& =QModelIndex()) const override;
    int columnCount(const QModelIndex& =QModelIndex()) const override;

    QVariant data(const QModelIndex&, int =Qt::DisplayRole) const override;
    bool setData(const QModelIndex&, const QVariant&, int =Qt::EditRole) override;
    QVariant headerData(int, Qt::Orientation, int) const override;
    bool setHeaderData(int, Qt::Orientation, const QVariant&, int =Qt::EditRole) override; //TODO: Da aggiungere il signal relativo.

    Qt::ItemFlags flags(const QModelIndex&) const override;

    void newColumns(size_t =1);
    void insertColumn(size_t);
    void removeColumn(size_t);
    void newRows(size_t =1);
    void insertRow(size_t);
    void removeRow(size_t);
};

#endif // MODEL_H
