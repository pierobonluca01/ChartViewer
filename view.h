#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QTableView>

class View: public QWidget {
//    Q_OBJECT

private:
    QMenu* file;

    QTableView* table;

    void addMenus(QVBoxLayout*);
    void addTable(QVBoxLayout*);

public:
    View(QWidget* =nullptr);
    ~View() =default;

    void setModel(QAbstractItemModel*); //test //TODO: da spostare nel Controller
};

#endif // VIEW_H
