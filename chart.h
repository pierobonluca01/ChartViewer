#ifndef CHART_H
#define CHART_H

#include <QtCharts>

class Controller;

class Chart: public QWidget {
    Q_OBJECT

private:
    Controller* controller;

protected:
    QChart* chart;

public:
    Chart(QWidget* =nullptr);
    virtual ~Chart() =default;

    void setController(Controller*);

    virtual void setData() =0;

    QChart* getChart();
};

class BarChart: public Chart {
public:
    BarChart();

    void setData();
};

class LineChart: public Chart {
public:
    LineChart();

    void setData();
};

class PieChart: public Chart {
public:
    PieChart();

    void setData();
};

#endif // CHART_H
