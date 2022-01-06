#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QtCharts>
#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>

class Controller;

class View: public QWidget {
    Q_OBJECT

private:
    Controller* controller;

    QMenu* file;
    QMenu* view;

    QSplitter* graphSplitter;
    QTableView* tableView;
    QChartView* chartView;

    void addMenus(QVBoxLayout*);
    void addTable(QSplitter*);
    void addChart(QSplitter*);

public:
    View(QWidget* =nullptr);
    virtual ~View() =default;

    void setModel(QAbstractItemModel*);
    void setController(Controller*);

public slots:
    void splitView(int) const;
};



#endif // VIEW_H
