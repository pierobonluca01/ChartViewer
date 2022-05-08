#include "model.h"

Model::Model(size_t r, size_t c, QString n, QObject* parent): QAbstractTableModel(parent), graph(new Graph(r, c, n.toStdString())) {}

QString Model::getName() const {
    return QString::fromStdString(graph->getName());
}

void Model::setName(const QString& n) {
    graph->setName()=n.toStdString();
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
    if(index.isValid() && role==Qt::DisplayRole)
       return graph->getData(index.row(), index.column());
    return QVariant();
}

bool Model::setData(const QModelIndex& index, const QVariant& value, int role) {
    if(index.isValid() && role==Qt::EditRole) {
        graph->setData(index.row(), index.column())=value.toDouble();
        emit dataChanged(index, index);
        return true;
    }
    return false;
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

bool Model::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role) {
    if(role==Qt::EditRole) {
        if(orientation==Qt::Horizontal)
            graph->setColumnLabel(section)=value.toString().toStdString();
        else if(orientation==Qt::Vertical)
            graph->setRowLabel(section)=value.toString().toStdString();
        emit headerDataChanged(orientation, section, section);
    }
    return true;
}

Qt::ItemFlags Model::flags(const QModelIndex& index) const {
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

/*TEST*/

bool Model::insertColumns(int column, int count, const QModelIndex& parent) {
    beginInsertColumns(parent, column, column+count);
    graph->newColumns(count);
    endInsertColumns();
    return true;
}

bool Model::insertColumn(int column, const QModelIndex& parent) {
    beginInsertColumns(parent, column, column+1);
    graph->insertColumn(column);
    endInsertColumns();
    return true;
}

bool Model::removeColumn(int column, const QModelIndex& parent) {
    beginRemoveColumns(parent, column, column+1);
    graph->removeColumn(column);
    endRemoveColumns();
    return true;
}

bool Model::insertRows(int row, int count, const QModelIndex& parent) {
    beginInsertRows(parent, row, row+count);
    graph->newRows(count);
    endInsertRows();
    return true;
}

bool Model::insertRow(int row, const QModelIndex& parent) {
    beginInsertRows(parent, row, row+1);
    graph->insertRow(row);
    endInsertRows();
    return true;
}

bool Model::removeRow(int row, const QModelIndex& parent) {
    beginRemoveRows(parent, row, row+1);
    graph->removeRow(row);
    endRemoveRows();
    return true;
}

//TODO: Rimuovere

//void Model::newColumns(size_t nc) {
//    graph->newColumns(nc);
//}

//void Model::insertColumn(size_t ic) {
//    graph->insertColumn(ic);
//}

//void Model::removeColumn(size_t ic) {
//    graph->removeColumn(ic);
//}

//void Model::newRows(size_t nr) {
//    graph->newRows(nr);
//}

//void Model::insertRow(size_t ir) {
//    graph->insertRow(ir);
//}

//void Model::removeRow(size_t ir) {
//    graph->removeColumn(ir);
//}

void Model::renewGraph(size_t r, size_t c, QString n) {
    beginResetModel();
    Graph* temp=graph;
    graph=new Graph(r, c, n.toStdString());
    delete temp;
    endResetModel();
    /*TEST*/ graph->printTable();
}
