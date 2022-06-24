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




DrilldownSlice::DrilldownSlice(double val, QString p, QPieSeries *s): series(s), prefix(p) {
    setValue(val);
    updateLabel();
    connect(this, &DrilldownSlice::percentageChanged, this, &DrilldownSlice::updateLabel);
    connect(this, &DrilldownSlice::hovered, this, &DrilldownSlice::showHighlight);
}

QPieSeries* DrilldownSlice::drilldownSeries() const {
    return series;
}

void DrilldownSlice::updateLabel() {
    QString label=prefix;
    label += ", ";
    label += QString::number(this->value());
    label += " | ";
    label += QString::number(this->percentage() * 100, 'f', 1);
    label += "%";
    setLabel(label);
}

void DrilldownSlice::showHighlight(bool show) {
    setLabelVisible(show);
    setExploded(show);
}



PieChart::PieChart(): series(0) {
    chart->setTitle("Pie Chart");
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
}

void PieChart::changeSeries(QPieSeries* s) {
    if(series)
        chart->removeSeries(series);
    series=s;
    chart->addSeries(s);
    chart->setTitle(series->name());
}

void PieChart::handleSliceClicked(QPieSlice *slice) {
    DrilldownSlice *drilldownSlice = static_cast<DrilldownSlice *>(slice);
    changeSeries(drilldownSlice->drilldownSeries());
}

void PieChart::build() {
    QPieSeries* mainSeries=new QPieSeries;
    mainSeries->setName("PieChart");
    for(int i=0; i<model->columnCount(); ++i) {
        QPieSeries* subSeries=new QPieSeries;
        subSeries->setName("PieChart | "+model->headerData(i, Qt::Horizontal).toString());
        for(int j=0; j<model->rowCount(); ++j) {
            QModelIndex index=model->index(j, i);
            *subSeries<<new DrilldownSlice(model->data(index).toDouble(), model->headerData(j, Qt::Vertical).toString(), mainSeries);
        }
        connect(subSeries, &QPieSeries::clicked, this, &PieChart::handleSliceClicked);
        *mainSeries<<new DrilldownSlice(subSeries->sum(), model->headerData(i, Qt::Horizontal).toString(), subSeries);
    }
    connect(mainSeries, &QPieSeries::clicked, this, &PieChart::handleSliceClicked);
    changeSeries(mainSeries);
}

void PieChart::updateChart() {
    build();
}



/* TODO: Rimuovere perché ABBANDONATO

PieChart::PieChart() {
    chart->setTitle("Pie Chart");
}

void PieChart::build() {
    series=new QPieSeries;
//    mapper=new QVPieModelMapper;
//    mapper->setFirstRow(0);
//    mapper->setRowCount(model->rowCount());
//    mapper->setValuesColumn(1);
//    mapper->setLabelsColumn(0);
//    mapper->setSeries(series);
//    mapper->setModel(model);
//    series->slices().at(0)->setLabel("Prova");


//    updateChart();
    for(int i=0; i<model->columnCount(); ++i) {
        qreal rowsum=0;
        for(int j=0; j<model->rowCount(); ++j) {
            QModelIndex index=model->index(0, j);
            rowsum+=model->data(index).toDouble();
        }
        *series<<new QPieSlice(model->headerData(i, Qt::Horizontal).toString(), rowsum);
    }
    chart->addSeries(series);
}

void PieChart::updateChart() {
    //mapper->setColumnCount(model->columnCount());
}

*/
