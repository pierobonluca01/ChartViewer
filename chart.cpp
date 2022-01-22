#include "chart.h"

Chart::Chart(QWidget* parent): QWidget(parent), chart(new QChart) {
    chart->setAnimationOptions(QChart::AllAnimations);
}

QChart* Chart::getChart() {
    return chart;
}

void Chart::setController(Controller* c) {
    controller=c;
}

BarChart::BarChart() {
    chart->setTitle("Bar Chart");
    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for(unsigned int i=0; i<controller->columnCount(); i++) {
//        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
//        for (const Data &data : m_dataTable[i])
//            *set << data.first.y();
//        series->append(set);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();
}

LineChart::LineChart() {
    chart->setTitle("Line Chart");
}

PieChart::PieChart() {
    chart->setTitle("Pie Chart");
}
