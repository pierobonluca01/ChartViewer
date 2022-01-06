#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QtCharts>
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
    QChartView* chartView;

    void addMenus(QVBoxLayout*);
    void addTable(QHBoxLayout*);
    void addChart(QHBoxLayout*);

public:
    View(QWidget* =nullptr);
    virtual ~View() =default;

    void setModel(QAbstractItemModel*);
    void setController(Controller*);
};



#endif // VIEW_H
