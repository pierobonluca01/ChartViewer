#include "controller.h"

Controller::Controller(QObject* parent): QObject(parent), model(nullptr), view(nullptr) {}

void Controller::setModel(Model* m) {
    model=m;
    if(view)
        view->setModel(model);
}

void Controller::setView(View* v) {
    view=v;
    if(model)
        view->setModel(model);
}


/*slots*/

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

void Controller::renewGraph() const {
    NewDialog* ng=new NewDialog;
    if(ng->exec()==QDialog::Accepted) {
        model->renewGraph(ng->getRows(), ng->getColumns(), ng->getName());
        view->setWindowTitle(QString("ChartViewer: ")+ng->getName());
    }
    delete ng;
}
