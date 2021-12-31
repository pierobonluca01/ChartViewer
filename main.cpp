#include "graph.h"
#include "model.h"

#include <QApplication>
#include <QTableView>

#include <iostream>
using std::cout;
using std::endl;

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
