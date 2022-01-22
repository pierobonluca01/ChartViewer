#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts>

class ChartView: public QWidget {
    Q_OBJECT

private:
    QChart* chart;

public:
    ChartView(QWidget*);
    virtual ~ChartView() =default;
};

#endif // CHARTVIEW_H
