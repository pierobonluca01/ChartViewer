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

#include <iostream>

//class Controller; //forward declaration inclusa in chart.h

class View: public QWidget {
    Q_OBJECT

private:
    Controller* controller;

    QMenuBar* menuBar;
    QMenu* file;
    QMenu* view;
    QMenu* chartType;
    QMenu* themes;

    QToolBar* toolBar;
    QComboBox* typeCombo;

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

    void setModel(QAbstractTableModel*);
    void setController(Controller*);

public slots:
    void setSplitter(int =0) const;
    void setChartZoom(int) const;
    void setChartType(int =0);
    void setGlobalTheme(int =1) const;
    void setTableTheme(int =1) const;

    void headerHMenu(QPoint);
    void headerVMenu(QPoint);

    void updateChart() const;
};



#endif // VIEW_H
