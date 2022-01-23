#ifndef VIEW_H
#define VIEW_H

#include <chart.h>

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>

//class Controller; //forward declaration inclusa in chart.h

class View: public QWidget {
    Q_OBJECT

private:
    Controller* controller;

    QMenu* file;
    QMenu* view;
    QMenu* themes;

    Chart* chart;

    QSplitter* graphSplitter;
    QTableView* tableView;
    QChartView* chartView;

    void addMenus(QVBoxLayout*);
    void addToolBar(QVBoxLayout*);
    void addTable(QSplitter*);
    void addChart(QSplitter*);

public:
    View(QWidget* =nullptr);
    virtual ~View() =default;

    void setModel(QAbstractItemModel*);
    void setController(Controller*);

public slots:
    void setSplitter(int) const;
    void setWindowTheme(int);
};



#endif // VIEW_H
