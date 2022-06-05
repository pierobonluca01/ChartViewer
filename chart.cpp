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

QChart::ChartTheme Chart::getChartTheme() {
    return chart->theme();
}

//void Chart::scrollEvent(QWheelEvent* e) {
//    //TODO: Implementare
//}

//void Chart::setController(Controller* c) {
//    controller=c;
//    build();
//}

void /*Bar*/Chart::setModel(QAbstractItemModel* m) {
    model=m;
    build();
}


BarChart::BarChart() {
    chart->setTitle("Bar Chart");
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
    axis->clear();
    axis->append(rowLabels);
}

LineChart::LineChart() {
    chart->setTitle("Line Chart");
}


PieChart::PieChart() {
    chart->setTitle("Pie Chart");
}

void PieChart::build() {
    series=new QPieSeries;
    mapper=new QVPieModelMapper;
    mapper->setFirstRow(0);
    mapper->setRowCount(model->rowCount());
    mapper->setValuesColumn(1);
    mapper->setLabelsColumn(0);
    mapper->setSeries(series);
    mapper->setModel(model);
    series->slices().at(0)->setLabel("Prova");


//    updateChart();
//    for(int i=0; i<model->columnCount(); ++i) {
//        qreal rowsum=0;
//        for(int j=0; j<model->rowCount(); ++j) {
//            QModelIndex index=model->index(0, j);
//            rowsum+=model->data(index).toDouble();
//        }
//        *series<<new QPieSlice(model->headerData(i, Qt::Horizontal).toString(), rowsum);
//    }
    chart->addSeries(series);
}

void PieChart::updateChart() {
    //mapper->setColumnCount(model->columnCount());
}
