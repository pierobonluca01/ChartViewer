#include "chart.h"
//#include "controller.h"

Chart::Chart(QWidget* parent): QWidget(parent), chart(new QChart) {
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setParent(this);
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

void Chart::setModel(QAbstractItemModel* m) {
    model=m;
    build();
}



// BAR CHART

BarChart::BarChart() {
    chart->setTitle("Bar Chart");
}

void BarChart::build() {
    series=new QBarSeries(this);
    mapper=new QVBarModelMapper(this);
    mapper->setFirstBarSetColumn(0);
    mapper->setLastBarSetColumn(model->columnCount());
    mapper->setFirstRow(0);
    mapper->setRowCount(model->rowCount());
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);

    axis=new QBarCategoryAxis(this);
    updateChart();
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
}

void BarChart::updateChart() {
    mapper->setLastBarSetColumn(model->columnCount());
    QStringList rowLabels;
    for(int i=0; i<model->rowCount(); ++i)
        rowLabels<<model->headerData(i, Qt::Vertical).toString();
    mapper->setRowCount(model->rowCount());
    axis->clear();
    axis->append(rowLabels);
}

void BarChart::updateData(const QModelIndex& topLeft) {
    Q_UNUSED(topLeft);
    double max=0;
    for(int i=0; i<model->columnCount(); ++i)
        for(int j=0; j<model->rowCount(); ++j) {
            QModelIndex index=model->index(i, j);
            if(model->data(index)>max)
                max=model->data(index).toDouble();
        }
    chart->axisY()->setMax(max);
}



// BOX CHART

BoxChart::BoxChart() {
    chart->setTitle("Box Chart");
    chart->legend()->setVisible(false);
}

BoxChart::~BoxChart() {
    delete series;
}

void BoxChart::build() {
    series=new QBoxPlotSeries(this);
    for(int i=0; i<model->columnCount(); ++i) {
        QBoxSet* set=buildSet(i);
        series->append(set);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();
}

void BoxChart::updateChart() {
    delete series;
    build();
}

void BoxChart::updateData(const QModelIndex& topLeft) {
    series->remove(series->boxSets().at(topLeft.column()));
    QBoxSet* set=buildSet(topLeft.column());
    series->insert(topLeft.column(), set);

    double max=0;
    for(int i=0; i<model->columnCount(); ++i)
        for(int j=0; j<model->rowCount(); ++j) {
            QModelIndex index=model->index(i, j);
            if(model->data(index)>max)
                max=model->data(index).toDouble();
        }
    chart->axisY()->setMax(max);
}

QBoxSet* BoxChart::buildSet(int column) {
    int count=model->rowCount();
    sortedList.clear();
    for(int i=0; i<count; ++i)
        sortedList.append(model->data(model->index(i, column)).toDouble());
    qSort(sortedList.begin(), sortedList.end());
    QBoxSet* set=new QBoxSet(model->headerData(column, Qt::Horizontal).toString());
    set->setValue(QBoxSet::LowerExtreme, sortedList.first());
    set->setValue(QBoxSet::UpperExtreme, sortedList.last());
    set->setValue(QBoxSet::Median, median(0, count));
    set->setValue(QBoxSet::LowerQuartile, median(0, count/2));
    set->setValue(QBoxSet::UpperQuartile, median(count/2+(count%2), count));
    return set;
}

double BoxChart::median(int first, int last) {
    int count=last-first;
    if (count%2)
        return sortedList.at(count/2+first);
    else {
        qreal right=sortedList.at(count/2+first);
        qreal left=sortedList.at(count/2+first-1);
        return (right+left)/2;
    }
}



// PIE CHART

PieSlice::PieSlice(double val, QString p, QPieSeries *s): series(s), header(p) {
    setValue(val);
    updateLabel();
    setLabelVisible(true);
    setLabelPosition(QPieSlice::LabelInsideNormal);
    connect(this, &PieSlice::percentageChanged, this, &PieSlice::updateLabel);
    connect(this, &PieSlice::hovered, this, &PieSlice::showLabel);
    connect(this, &PieSlice::hovered, this, &PieSlice::setExploded);
}

void PieSlice::showLabel(bool show) {
    if(show)
        setLabelPosition(QPieSlice::LabelOutside);
    else
        setLabelPosition(QPieSlice::LabelInsideNormal);
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

PieChart::~PieChart() {
    delete series;
    delete subArray;
}

void PieChart::changeSeries(QPieSeries* s) {
    if(series)
        chart->removeSeries(series);
    series=s;
    chart->addSeries(s);
    chart->setTitle(series->name());
}

void PieChart::sliceClicked(QPieSlice *s) {
    PieSlice* slice=static_cast<PieSlice*>(s);
    changeSeries(slice->sliceSeries());
}

void PieChart::build() {
    mainSeries=new QPieSeries(this);
    mainSeries->setName("PieChart");
    subArray=new QPieSeries*[model->columnCount()];
    for(int i=0; i<model->columnCount(); ++i) {
        QPieSeries* subSeries=new QPieSeries(this);
        subArray[i]=subSeries;
        subSeries->setName("PieChart | "+model->headerData(i, Qt::Horizontal).toString());
        for(int j=0; j<model->rowCount(); ++j) {
            QModelIndex index=model->index(j, i);
            *subSeries<<new PieSlice(model->data(index).toDouble(), model->headerData(j, Qt::Vertical).toString(), mainSeries);
        }
        connect(subSeries, &QPieSeries::clicked, this, &PieChart::sliceClicked);
        *mainSeries<<new PieSlice(subSeries->sum(), model->headerData(i, Qt::Horizontal).toString(), subSeries);
    }
    connect(mainSeries, &QPieSeries::clicked, this, &PieChart::sliceClicked);
    changeSeries(mainSeries);
}

void PieChart::updateChart() {
    build();
}

void PieChart::updateData(const QModelIndex& topLeft) {
    subArray[topLeft.column()]->slices().at(topLeft.row())->setValue(model->data(topLeft).toDouble());
    mainSeries->slices().at(topLeft.column())->setValue(subArray[topLeft.column()]->sum());
}
