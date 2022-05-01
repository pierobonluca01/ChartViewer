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

QString Controller::getName() const {
    return model->getName();
}

unsigned int Controller::rowCount() const {
    return model->rowCount();
}

unsigned int Controller::columnCount() const {
    return model->columnCount();
}

QVariant Controller::data(const QModelIndex& index) const {
    return model->data(index);
}

QVariant Controller::headerData(int section, Qt::Orientation orientation) const {
    return model->headerData(section, orientation);
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

void Controller::editHLabel(int section) {
    EditLabelDialog* eld=new EditLabelDialog;
    if(eld->exec()==QDialog::Accepted) {
        model->setHeaderData(section, Qt::Horizontal, eld->getLabel());
    }
    delete eld;
}

void Controller::editVLabel(int section) {
    EditLabelDialog* eld=new EditLabelDialog;
    if(eld->exec()==QDialog::Accepted) {
        model->setHeaderData(section, Qt::Vertical, eld->getLabel());
    }
    delete eld;
}

void Controller::renewGraph() const {
    NewDialog* ng=new NewDialog;
    if(ng->exec()==QDialog::Accepted) {
        model->renewGraph(ng->getRows(), ng->getColumns(), ng->getName());
        view->setWindowTitle(QString("ChartViewer: ")+ng->getName());
    }
    delete ng;
}
