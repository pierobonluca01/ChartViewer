#include "model.h"
#include "view.h"
#include "controller.h"

#include <QApplication>
#include <QTableView>

#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char** argv) {

    QApplication app(argc, argv);

    Model model;
    View view;
    Controller controller;

    model.newRows(3);   //test
    model.newColumns(3); //test

    view.setModel(&model); //test
    view.show();

    return app.exec();
}
