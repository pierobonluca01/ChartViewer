#include "graph.h"

using std::cout;
using std::endl;
using std::string;

Graph::Graph(size_t r, size_t c, std::string n): Table(r, c), name(n), lR(Labels(r)), lC(Labels(c)) {}

Graph::Graph(const Graph& g): Table(g.rows, g.columns), name(g.name), lR(g.lR), lC(g.lC) {}

std::string Graph::getName() {
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

double Graph::getRowPercentage(size_t r, size_t c) {
    double rSum=0;
    vector<vector<double>>::const_iterator itR=t.begin()+r;
    for(vector<double>::const_iterator itC=itR->begin(); itC!=itR->end(); ++itC)
        rSum+=*itC;
    return t[r][c]/rSum;
}

double Graph::getColumnPercentage(size_t r, size_t c) {
    double cSum=0;
    for(vector<vector<double>>::const_iterator itR=t.begin(); itR!=t.end(); ++itR)
        cSum+=*(itR->begin()+c);
    if(cSum==0)
        cSum=1;
    return t[r][c]/cSum;
}

//Console

void Graph::printName() {
    cout<<"Graph "<<name;
}

void Graph::printTable() {
    for(vector<vector<double>>::iterator itR=t.begin(); itR!=t.end(); ++itR) {
        cout<<lR[distance(t.begin(), itR)]<<" ";
        for(vector<double>::iterator itC=itR->begin(); itC!=itR->end(); ++itC)
            cout<<*itC;
        cout<<endl;
    }
}