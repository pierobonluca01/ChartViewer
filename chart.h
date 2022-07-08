#ifndef CHART_H
#define CHART_H

#include <QtCharts>

class Chart: public QWidget {
    Q_OBJECT

protected:
    QAbstractItemModel* model;

    QChart* chart;

public:
    Chart(QWidget* =nullptr);
    virtual ~Chart() =default;

    void setModel(QAbstractItemModel*);

    virtual void build() =0;
    virtual void updateChart() =0;
    virtual void updateData(const QModelIndex&) =0;

    QChart* getChart();
    void setChartTheme(QChart::ChartTheme);
    QChart::ChartTheme getChartTheme();
};



class BarChart: public Chart {
    Q_OBJECT

private:
    QBarSeries* series;
    QVBarModelMapper* mapper;
    QBarCategoryAxis* axis;

public:
    BarChart();
    virtual ~BarChart() =default;

    void build() override;
    void updateChart() override;
    void updateData(const QModelIndex&) override;
};



class BoxChart: public Chart {
    Q_OBJECT

private:
    QBoxPlotSeries* series;
    QList<double> sortedList;

public:
    BoxChart();
    virtual ~BoxChart() =default;

    void build() override;
    void updateChart() override;
    void updateData(const QModelIndex&) override;

    QBoxSet* buildSet(int);
    double median(int, int);
};



class PieSlice: public QPieSlice {
    Q_OBJECT

private:
    QPieSeries *series;
    QString header;

public:
    PieSlice(double value, QString prefix, QPieSeries *sliceSeries);
    virtual ~PieSlice() =default;

    QPieSeries *sliceSeries() const;

public slots:
    void updateLabel();
    void showLabel(bool);
};

class PieChart: public Chart {
    Q_OBJECT

private:
    QPieSeries* series;
    QPieSeries* mainSeries;
    QPieSeries** subArray;

public:
    PieChart();
    virtual ~PieChart();

    void build() override;
    void updateChart() override;
    void updateData(const QModelIndex&) override;
    void changeSeries(QPieSeries*);

public slots:
    void sliceClicked(QPieSlice*);
};

#endif // CHART_H
