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

//void Chart::setController(Controller* c) {
//    controller=c;
//    build();
//}

BarChart::BarChart() {
    chart->setTitle("Bar Chart");
}

void BarChart::setModel(QAbstractItemModel* m) {
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
    QStringList rowLabels; //TODO: Sistemare la QStringList che di base rimuove i duplicati
    for(int i=0; i<model->rowCount(); i++)
        rowLabels<<model->headerData(i, Qt::Vertical).toString();
    QBarCategoryAxis* axis=new QBarCategoryAxis();
    axis->append(rowLabels);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
}

LineChart::LineChart() {
    chart->setTitle("Line Chart");
}

PieChart::PieChart() {
    chart->setTitle("Pie Chart");
}
