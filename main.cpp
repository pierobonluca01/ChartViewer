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

    Model model(3, 3);
    View view;
    Controller controller;

    controller.setModel(&model);
    controller.setView(&view);
    view.setController(&controller);

    view.show();

    return app.exec();
}
