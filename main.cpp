#include "model.h"
#include "view.h"
#include "controller.h"

#include <QApplication>
#include <QTableView>

int main(int argc, char** argv) {

    QApplication app(argc, argv);

    Model model(1, 3);
    View view;
    Controller controller;

    controller.setModel(&model);
    controller.setView(&view);
    view.setController(&controller);

    view.show();

    return app.exec();
}
