#include "chart.h"
#include "controller.h"

Chart::Chart(QWidget* parent): QWidget(parent), chart(new QChart) {
    chart->setAnimationOptions(QChart::AllAnimations);
}

QChart* Chart::getChart() {
    return chart;
}

//void Chart::setController(Controller* c) {
//    controller=c;
//    build();
//}

BarChart::BarChart() {
    chart->setTitle("Bar Chart");
    chart->setTheme(QChart::ChartThemeBlueCerulean);
}

void BarChart::setModel(QAbstractItemModel* m) {
    model=m;
    build();
}

void BarChart::build() {
    series = new QBarSeries;
    mapper = new QVBarModelMapper/*(this)*/;
    mapper->setFirstBarSetColumn(0);
    mapper->setLastBarSetColumn(model->columnCount());
    mapper->setFirstRow(0);
    mapper->setRowCount(model->rowCount());
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);
//    QStackedBarSeries* series=new QStackedBarSeries(chart);
//    for(unsigned int i=0; i<controller->columnCount(); i++) {
//        QBarSet* set=new QBarSet(controller->headerData(i, Qt::Horizontal).toString());
//        for(unsigned int j=0; j<controller->columnCount(); j++)
//            *set<<2;
//        series->append(set);
//    }
//    chart->addSeries(series);
//    chart->createDefaultAxes();
}

LineChart::LineChart() {
    chart->setTitle("Line Chart");
}

PieChart::PieChart() {
    chart->setTitle("Pie Chart");
}
