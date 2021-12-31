#include "graph.h"
#include "model.h"

#include <QApplication>
#include <QTableView>

#include <iostream>
using std::cout;
using std::endl;

void info(Graph* x) {
    cout<<endl<<x->getRows()<<" "<<x->getColumns()<<" "<<x->t.size()<<"x"<<x->t[0].size()<<" "<<x->t.capacity()<<"x"<<x->t[0].capacity()<<endl;
}

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QTableView tableView;
    Model model;

    model.newColumns(3);
    model.newRows(3);

    tableView.setModel(&model);
    tableView.show();

    return app.exec();
}
