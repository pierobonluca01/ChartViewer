#include "chart.h"
#include "controller.h"

Chart::Chart(QWidget* parent): QWidget(parent), chart(new QChart) {
    chart->setAnimationOptions(QChart::AllAnimations);
}

QChart* Chart::getChart() {
    return chart;
}

void Chart::setChartTheme(QChart::ChartTheme t) {
    chart->setTheme(t);
}

//void Chart::scrollEvent(QWheelEvent* e) {
//    //TODO: Implementare
//}

//void Chart::setController(Controller* c) {
//    controller=c;
//    build();
//}

BarChart::BarChart() {
    chart->setTitle("Bar Chart");
}

void /*Bar*/Chart::setModel(QAbstractItemModel* m) {
    model=m;
    build();
}

void BarChart::build() {
    series=new QBarSeries;
    mapper=new QVBarModelMapper/*(this)*/;
    mapper->setFirstBarSetColumn(0);
    mapper->setLastBarSetColumn(model->columnCount());
    mapper->setFirstRow(0);
    mapper->setRowCount(model->rowCount());
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);

    axis=new QBarCategoryAxis();
    updateChart();
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
}

void BarChart::updateChart() {
    mapper->setLastBarSetColumn(model->columnCount());
    QStringList rowLabels;
    for(int i=0; i<model->rowCount(); i++)
        rowLabels<<model->headerData(i, Qt::Vertical).toString();
    mapper->setRowCount(model->rowCount());
    axis->clear(); //TODO: Problema di sovrapposizione di QBarCategories
    axis->append(rowLabels);
}

LineChart::LineChart() {
    chart->setTitle("Line Chart");
}

PieChart::PieChart() {
    chart->setTitle("Pie Chart");
}
