#ifndef CHART_H
#define CHART_H

#include <QtCharts>

class Controller; //TODO: Rimuovere i commenti relativi al Controller

class Chart: public QWidget {
    Q_OBJECT

protected:
    QAbstractItemModel* model;

    QChart* chart;
    //Controller* controller;

public:
    Chart(QWidget* =nullptr);
    virtual ~Chart() =default;

    /*virtual*/ void setModel(QAbstractItemModel*) /*=0*/;
    //void setController(Controller*);

    virtual void build() =0;
    virtual void updateChart() =0;
    virtual void updateData(const QModelIndex&) =0;

    QChart* getChart();
    void setChartTheme(QChart::ChartTheme);
    QChart::ChartTheme getChartTheme();
    //void scrollEvent(QWheelEvent*); //TODO: Implementare
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

    //void setModel(QAbstractItemModel*) override;

    void build() override;
    void updateChart() override;
    void updateData(const QModelIndex&) override;
};

class LineChart: public Chart {
    Q_OBJECT

public:
    LineChart();
    virtual ~LineChart() =default;

    //void setModel(QAbstractItemModel*) override {}

    void build() override {}
    void updateChart() override {}
    void updateData(const QModelIndex&) override {}
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
    virtual ~PieChart() =default;

    //void setModel(QAbstractItemModel*) override {}

    void build() override;
    void updateChart() override;
    void updateData(const QModelIndex&) override;
    void changeSeries(QPieSeries*);

public slots:
    void sliceClicked(QPieSlice*);
};

#endif // CHART_H
