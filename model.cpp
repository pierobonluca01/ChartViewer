#include "model.h"

Model::Model(): graph(new Graph()) {}

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

