#include "graph.h"

#include <iostream>
using std::cout;
using std::endl;

void info(Graph* x) {
    cout<<endl<<x->getRows()<<" "<<x->getColumns()<<" "<<x->t.size()<<"x"<<x->t[0].size()<<" "<<x->t.capacity()<<"x"<<x->t[0].capacity()<<endl;
}

int main() {

    Graph* x=new Graph(5, 8, "x di test");
    for(size_t i=0; i<5; ++i)
        for(size_t j=0; j<8; ++j)
            (*x)[i][j]=5;

    x->printName();
    info(x);
    x->printTable();
    cout<<endl;

    x->newColumns();

    x->printName();
    info(x);
    x->printTable();
    cout<<endl;

    x->newRows();

    x->printName();
    info(x);
    x->printTable();
    cout<<endl;

    x->insertColumn(3);

    x->printName();
    info(x);
    x->printTable();
    cout<<endl;

    x->insertRow(3);

    x->printName();
    info(x);
    x->printTable();
    cout<<endl;

    x->removeRow(3);

    x->printName();
    info(x);
    x->printTable();
    cout<<endl;

    x->removeColumn(3);
    x->removeColumn(8);
    x->removeRow(5);

    x->printName();
    info(x);
    x->printTable();
    cout<<endl;

    return 0;
}
