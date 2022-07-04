#ifndef MODEL_H
#define MODEL_H

#include "graph.h"

#include <QAbstractTableModel>

#include <vector>
using std::vector;

class Model: public QAbstractTableModel {
    Q_OBJECT

private:
    Graph* graph;

public:
    Model(size_t =0, size_t =0, QString ="senza_titolo", QObject* =nullptr);
    virtual ~Model();

    QString getName() const;
    void setName(const QString&);

    int rowCount(const QModelIndex& =QModelIndex()) const override;
    int columnCount(const QModelIndex& =QModelIndex()) const override;

    QVariant data(const QModelIndex&, int =Qt::DisplayRole) const override;
    bool setData(const QModelIndex&, const QVariant&, int =Qt::EditRole) override;
    QVariant headerData(int, Qt::Orientation, int =Qt::DisplayRole) const override;
    bool setHeaderData(int, Qt::Orientation, const QVariant&, int =Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex&) const override;

    bool insertColumns(int, int =1, const QModelIndex& =QModelIndex()) override;
    bool insertColumn(int, const QModelIndex& =QModelIndex());
    bool removeColumn(int, const QModelIndex& =QModelIndex());
    bool insertRows(int, int =1, const QModelIndex& =QModelIndex()) override;
    bool insertRow(int, const QModelIndex& =QModelIndex());
    bool removeRow(int, const QModelIndex& =QModelIndex());

    void renewGraph(size_t =0, size_t =0, QString ="senza_titolo");
};

#endif // MODEL_H
