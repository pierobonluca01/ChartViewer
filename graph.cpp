#include "graph.h"

using std::cout;
using std::endl;
using std::string;

Graph::Graph(size_t r, size_t c, std::string n): Table(r, c), name(n), lR(Labels(r)), lC(Labels(c)) {}

Graph::Graph(const Graph& g): Table(g.rows, g.columns), name(g.name), lR(g.lR), lC(g.lC) {}

std::string Graph::getName() const {
    return name;
}

std::string& Graph::setName() {
    return name;
}

void Graph::newColumns(size_t nc) {
    Table::newColumns(nc);
    lC.newLabels(nc);
}

void Graph::insertColumn(size_t ic) {
    Table::insertColumn(ic);
    lC.insertLabel(ic);
}

void Graph::removeColumn(size_t ic) {
    Table::removeColumn(ic);
    lC.removeLabel(ic);
}

void Graph::newRows(size_t nr) {
    Table::newRows(nr);
    lR.newLabels(nr);
}

void Graph::insertRow(size_t ir) {
    Table::insertRow(ir);
    lR.insertLabel(ir);
}

void Graph::removeRow(size_t ir) {
    Table::removeRow(ir);
    lR.removeLabel(ir);
}

string Graph::getRowLabel(size_t ir) const {
    return lR.getLabel(ir);
}

string Graph::getColumnLabel(size_t ic) const {
    return lC.getLabel(ic);
}

string& Graph::setRowLabel(size_t ir) {
    return lR.setLabel(ir);
}

string& Graph::setColumnLabel(size_t ic) {
    return lC.setLabel(ic);
}
