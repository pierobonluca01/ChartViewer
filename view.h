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

    //TEST
    QChart* chart;
    QBarSeries* series;
    QVBarModelMapper* chartMapper;
    QChartView* chartView;
    void addChart(QSplitter*);
    //ENDTEST

    void addMenus(QVBoxLayout*);
    void addTable(QSplitter*);

public:
    View(QWidget* =nullptr);
    virtual ~View() =default;

    void setModel(QAbstractItemModel*);
    void setController(Controller*);

public slots:
    void setSplitter(int) const;
};



#endif // VIEW_H
