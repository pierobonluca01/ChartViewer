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

void Controller::newColumns(int nc) const {
    model->insertColumns(model->columnCount(), nc);
    view->updateChart();
}

void Controller::insertColumn(int ic) const {
    model->insertColumn(ic);
    view->updateChart();
}

void Controller::removeColumn(int ic) const {
    model->removeColumn(ic);
    view->updateChart();
}

void Controller::newRows(int nr) const {
    model->insertRows(model->rowCount(), nr);
    view->updateChart();
}

void Controller::insertRow(int ir) const{
    model->insertRow(ir);
    view->updateChart();
}

void Controller::removeRow(int ir) const {
    model->removeRow(ir);
    view->updateChart();
}

void Controller::editHLabel(int section) const {
    EditLabelDialog* eld=new EditLabelDialog(0, model->headerData(section, Qt::Horizontal).toString());
    if(eld->exec()==QDialog::Accepted)
        model->setHeaderData(section, Qt::Horizontal, eld->getLabel());
    delete eld;
}

void Controller::editVLabel(int section) const {
    EditLabelDialog* eld=new EditLabelDialog(1, model->headerData(section, Qt::Vertical).toString());
    if(eld->exec()==QDialog::Accepted)
        model->setHeaderData(section, Qt::Vertical, eld->getLabel());
    delete eld;
}

void Controller::addRC(int orientation) const {
    AddDialog* ad=new AddDialog(orientation);
    if(ad->exec()==QDialog::Accepted) {
        if(orientation)
            newRows(ad->getNum());
        else
            newColumns(ad->getNum());
    }
    delete ad;
}

void Controller::renewGraph() const {
    NewDialog* ng=new NewDialog;
    if(ng->exec()==QDialog::Accepted) {
        model->renewGraph(ng->getRows(), ng->getColumns(), ng->getName());
        view->updateChart();
        view->setWindowTitle(QString("ChartViewer: ")+ng->getName());
    }
    delete ng;
}
