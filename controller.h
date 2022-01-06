#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
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

    void setView(View*);
    void setModel(Model*);

public slots:
    void newColumns(size_t =1) const;
    void insertColumn(size_t) const;
    void removeColumn(size_t) const;
    void newRows(size_t =1) const;
    void insertRow(size_t) const;
    void removeRow(size_t) const;

    void renewGraph() const;
};

#endif // CONTROLLER_H
