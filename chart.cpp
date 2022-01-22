#include "chart.h"

Chart::Chart(QWidget* parent): QWidget(parent), chart(new QChart) {
    chart->setAnimationOptions(QChart::AllAnimations);
}

QChart* Chart::getChart() {
    return chart;
}

BarChart::BarChart() {
    chart->setTitle("Bar Chart");
}

LineChart::LineChart() {
    chart->setTitle("Line Chart");
}

PieChart::PieChart() {
    chart->setTitle("Pie Chart");
}
