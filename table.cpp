#include "table.h"

using std::cout;
using std::endl;
using std::string;

Table::Table(size_t r, size_t c): rows(r), columns(c), t(r, vector<double>(c, 3 /*TEST*/)) {}

Table::Table(const Table& t): rows(t.rows), columns(t.columns), t(t.t) {}

int Table::getRows() const {
    return rows;
}

int Table::getColumns() const {
    return columns;
}

double& Table::setData(size_t ir, size_t ic) {
    return t[ir][ic];
}

double Table::getData(size_t ir, size_t ic) const {
    return t[ir][ic];
}

void Table::newColumns(size_t nc) {
    for(vector<vector<double>>::iterator itR=t.begin(); itR!=t.end(); ++itR)
        for(size_t i=0; i<nc; ++i)
            itR->push_back(0);
    columns+=nc;
}

void Table::insertColumn(size_t ic) {
    for(vector<vector<double>>::iterator itR=t.begin(); itR!=t.end(); ++itR)
        itR->insert(itR->begin()+ic, 0);
    columns++;
}

void Table::removeColumn(size_t ic) {
    for(vector<vector<double>>::iterator itR=t.begin(); itR!=t.end(); ++itR)
        itR->erase(itR->begin()+ic);
    columns--;
}

void Table::newRows(size_t nr) {
    for(size_t i=0; i<nr; ++i)
        t.push_back(vector<double>(columns, 0));
    rows+=nr;
}

void Table::insertRow(size_t ir) {
    t.insert(t.begin()+ir, vector<double>(columns, 0));
    rows++;
}

void Table::removeRow(size_t ir) {
    t.erase(t.begin()+ir);
    rows--;
}

vector<double>& Table::operator [](size_t ir) {
    try {
        if(ir>t.size() /*|| ir<0 size_t unsigned*/)
            throw 0;
        return t[ir];
    } catch(int err) {
        switch(err) {
        case 0:
            std::cerr<<"\n [!] Indice fuori range.\n     Ritornato l'ultimo elemento.\n";
            return t[0];
            break;
        default:
            std::cerr<<"\n [!] Errore generico. \n";
            abort();
        }
    }
}
