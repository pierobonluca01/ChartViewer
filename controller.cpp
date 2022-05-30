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
    if(section<0)
        return;
    EditLabelDialog* eld=new EditLabelDialog(0, model->headerData(section, Qt::Horizontal).toString());
    if(eld->exec()==QDialog::Accepted)
        model->setHeaderData(section, Qt::Horizontal, eld->getLabel());
    delete eld;
}

void Controller::editVLabel(int section) const {
    if(section<0)
        return;
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
        view->setWindowTitle(ng->getName()+QString(" | ChartViewer"));
    }
    delete ng;
}

bool Controller::open() {
    QString tmp=QFileDialog::getOpenFileName(view, tr("Apri"), "", tr("JSON (*.json)"));
    if(tmp=="")
        return false;

    fileName=tmp;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject obj=QJsonDocument::fromJson(file.readAll()).object();

    QJsonObject row=obj["row"].toObject();
    QJsonObject column=obj["column"].toObject();

    QFileInfo info(fileName);
    model->renewGraph(row["count"].toInt(), column["count"].toInt(), info.baseName());
    view->updateChart();
    view->setWindowTitle(info.baseName()+tr(" | ChartViewer"));

    QJsonArray rowLabels=row["labels"].toArray();
    for(int i=0; i<model->rowCount(); ++i)
        model->setHeaderData(i, Qt::Vertical, rowLabels[i].toString());

    QJsonArray columnLabels=column["labels"].toArray();
    for(int i=0; i<model->columnCount(); ++i)
        model->setHeaderData(i, Qt::Horizontal, columnLabels[i].toString());

    QJsonArray data=obj["table"].toArray();
    for(int i=0; i<model->rowCount(); ++i) {
        QJsonArray rowData=data[i].toArray();
        for(int j=0; j<model->columnCount(); ++j) {
            QModelIndex index=model->index(i, j);
            model->setData(index, rowData[j].toDouble());
        }
    }

    return true;
}

void Controller::quickSave() {
    if(fileName=="")
        saveWithName();
    else
        save();
}

void Controller::saveWithName() {
    QString tmp=QFileDialog::getSaveFileName(view, tr("Salva con nome..."), "./"+model->getName()+".json", tr("JSON (*.json)"));
    if(tmp!="") {
        fileName=tmp;
        QFileInfo info(fileName);
        model->setName(info.baseName());
        view->setWindowTitle(info.baseName()+tr(" | ChartViewer"));
        save();
    }
}

bool Controller::save() {
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("\t[!] Impossibile aprire il file.");
        return false;
    }

    QJsonObject row;
    row["count"]=model->rowCount();
    QJsonArray rowLabels;
    for(int i=0; i<model->rowCount(); ++i)
        rowLabels.append(model->headerData(i, Qt::Vertical).toString());
    row["labels"]=rowLabels;

    QJsonObject column;
    column["count"]=model->columnCount();
    QJsonArray columnLabels;
    for(int i=0; i<model->columnCount(); ++i)
        columnLabels.append(model->headerData(i, Qt::Horizontal).toString());
    column["labels"]=columnLabels;

    QJsonArray data;
    for(int i=0; i<model->rowCount(); ++i) {
        QJsonArray rowData;
        for(int j=0; j<model->columnCount(); ++j) {
            QModelIndex index=model->index(i, j);
            rowData.append(model->data(index).toDouble());
        }
        data.append(rowData);
    }


    QJsonObject obj;
    obj["name"]=model->getName();
    obj["row"]=row;
    obj["column"]=column;
    obj["table"]=data;

    QJsonDocument doc(obj);
    file.write(doc.toJson());

    return true;
}
