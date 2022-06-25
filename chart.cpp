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



// BAR CHART

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



// LINE CHART

LineChart::LineChart() {
    chart->setTitle("Line Chart");
}



// PIE CHART

PieSlice::PieSlice(double val, QString p, QPieSeries *s): series(s), header(p) {
    setValue(val);
    updateLabel();
    setLabelVisible(true);
    setLabelPosition(QPieSlice::LabelInsideHorizontal);
    connect(this, &PieSlice::percentageChanged, this, &PieSlice::updateLabel);
    connect(this, &PieSlice::hovered, this, &PieSlice::showLabel);
    connect(this, &PieSlice::hovered, this, &PieSlice::setExploded);
}

void PieSlice::showLabel(bool show) {
    if(show)
        setLabelPosition(QPieSlice::LabelOutside);
    else
        setLabelPosition(QPieSlice::LabelInsideHorizontal);
}

QPieSeries* PieSlice::sliceSeries() const {
    return series;
}

void PieSlice::updateLabel() {
    QString label=header;
    label+=", ";
    label+=QString::number(this->value());
    label+=" | ";
    label+=QString::number(this->percentage()*100, 'f', 2);
    label+="%";
    setLabel(label);
}

PieChart::PieChart(): series(0) {
    chart->setTitle("Pie Chart");
    chart->legend()->setAlignment(Qt::AlignRight);
}

void PieChart::changeSeries(QPieSeries* s) {
    if(series)
        chart->removeSeries(series);
    series=s;
    chart->addSeries(s);
    chart->setTitle(series->name());
}

void PieChart::handleSliceClicked(QPieSlice *s) {
    PieSlice *slice=static_cast<PieSlice*>(s);
    changeSeries(slice->sliceSeries());
}

void PieChart::build() {
    QPieSeries* mainSeries=new QPieSeries;
    mainSeries->setName("PieChart");
    for(int i=0; i<model->columnCount(); ++i) {
        QPieSeries* subSeries=new QPieSeries;
        subSeries->setName("PieChart | "+model->headerData(i, Qt::Horizontal).toString());
        for(int j=0; j<model->rowCount(); ++j) {
            QModelIndex index=model->index(j, i);
            *subSeries<<new PieSlice(model->data(index).toDouble(), model->headerData(j, Qt::Vertical).toString(), mainSeries);
        }
        connect(subSeries, &QPieSeries::clicked, this, &PieChart::handleSliceClicked);
        *mainSeries<<new PieSlice(subSeries->sum(), model->headerData(i, Qt::Horizontal).toString(), subSeries);
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
