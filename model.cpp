#include "model.h"

Model::Model(QObject* parent): QAbstractTableModel(parent), graph(new Graph()) {}

Model::~Model() {
    delete graph;
}

int Model::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return graph->getRows();
}

int Model::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return graph->getColumns();
}

QVariant Model::data(const QModelIndex& index, int role) const {
    if(role==Qt::DisplayRole)
       return graph->getData(index.row(), index.column());
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role==Qt::DisplayRole) {
        if(orientation==Qt::Horizontal)
            return QString::fromStdString(graph->getColumnLabel(section));
        else if(orientation==Qt::Vertical)
            return QString::fromStdString(graph->getRowLabel(section));
    }
    return QVariant();
}

void Model::newColumns(size_t nc) {
    graph->newColumns(nc);
}

void Model::insertColumn(size_t ic) {
    graph->insertColumn(ic);
}

void Model::removeColumn(size_t ic) {
    graph->removeColumn(ic);
}

void Model::newRows(size_t nr) {
    graph->newRows(nr);
}

void Model::insertRow(size_t ir) {
    graph->insertRow(ir);
}

void Model::removeRow(size_t ir) {
    graph->removeColumn(ir);
}
