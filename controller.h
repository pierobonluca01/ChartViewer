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
    void newColumns(size_t =1) const;
    void insertColumn(size_t) const;
    void removeColumn(size_t) const;
    void newRows(size_t =1) const;
    void insertRow(size_t) const;
    void removeRow(size_t) const;

    void editHLabel(int);
    void editVLabel(int);

    void renewGraph();
};

#endif // CONTROLLER_H
