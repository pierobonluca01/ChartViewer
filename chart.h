#ifndef CHART_H
#define CHART_H

#include <QtCharts>

class Controller;

class Chart: public QWidget {
    Q_OBJECT

protected:
    QChart* chart;
    Controller* controller;

public:
    Chart(QWidget* =nullptr);
    virtual ~Chart() =default;

    void setController(Controller*);

    //virtual void setData() =0;
    QChart* getChart();
};

class BarChart: public Chart {
public:
    BarChart();
    virtual ~BarChart() =default;

    //void setData() override {}
};

class LineChart: public Chart {
public:
    LineChart();
    virtual ~LineChart() =default;

    //void setData() override {}
};

class PieChart: public Chart {
public:
    PieChart();
    virtual ~PieChart() =default;

    //void setData() override {}
};

#endif // CHART_H
