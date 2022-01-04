#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QTableView>

class Controller;

class View: public QWidget {
    Q_OBJECT

private:
    Controller* controller;

    QMenu* file;

    QTableView* tableView;

    void addMenus(QVBoxLayout*);
    void addTable(QVBoxLayout*);

public:
    View(QWidget* =nullptr);
    virtual ~View() =default;

    void setModel(QAbstractItemModel*);
    void setController(Controller*);
};



#endif // VIEW_H
