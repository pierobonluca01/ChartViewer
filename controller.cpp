#include "controller.h"
#include "dialogs.h"

Controller::Controller(QObject* parent): QObject(parent), model(nullptr), view(nullptr) {}

void Controller::newColumns(size_t nc) const {
    model->newColumns(nc);
}

void Controller::insertColumn(size_t ic) const {
    model->insertColumn(ic);
}

void Controller::removeColumn(size_t ic) const {
    model->removeColumn(ic);
}

void Controller::newRows(size_t nr) const {
    model->newRows(nr);
}

void Controller::insertRow(size_t ir) const{
    model->insertRow(ir);
}

void Controller::removeRow(size_t ir) const {
    model->removeColumn(ir);
}

void Controller::setView(View* v) {
    view=v;
    if(model)
        view->setModel(model);
}

void Controller::setModel(Model* m) {
    model=m;
    if(view)
        view->setModel(model);
}

void Controller::newGraph() {
    NewDialog win;
    win.exec();
}
