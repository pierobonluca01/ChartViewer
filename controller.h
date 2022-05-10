#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "chart.h"
#include "view.h"
#include "dialogs.h"

class Controller: public QObject {
    Q_OBJECT

private:
    Model* model;
    View* view;

public:
    Controller(QObject* =nullptr);
    virtual ~Controller() =default;

    void setModel(Model*);
    void setView(View*);

    QString getName() const;
    unsigned int rowCount() const;
    unsigned int columnCount() const;
    QVariant data(const QModelIndex&) const;
    QVariant headerData(int, Qt::Orientation) const;



public slots:
    void newColumns(int =1) const;
    void insertColumn(int) const;
    void removeColumn(int) const;
    void newRows(int =1) const;
    void insertRow(int) const;
    void removeRow(int) const;

    void editHLabel(int) const;
    void editVLabel(int) const;

    void addRC(int) const;

    void renewGraph() const;
};

#endif // CONTROLLER_H
