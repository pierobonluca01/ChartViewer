#include "view.h"
#include "controller.h"

View::View(QWidget* parent): QWidget(parent) {
    setWindowIcon(QIcon(":/images/chart"));
    setWindowTitle(QString("ChartViewer: senza_titolo"));

    QVBoxLayout* mainLayout=new QVBoxLayout;
    addMenus(mainLayout);
    QHBoxLayout* graphLayout=new QHBoxLayout;
    addTable(graphLayout);
    addChart(graphLayout);
    mainLayout->addLayout(graphLayout);

    setLayout(mainLayout);
}

void View::addMenus(QVBoxLayout* layout) {
    QMenuBar* menuBar=new QMenuBar(this);

    file=new QMenu("File", menuBar);

    menuBar->addMenu(file);
    file->addAction(new QAction("Nuovo...", file));

    layout->addWidget(menuBar);
}

void View::addTable(QHBoxLayout* layout) {
    tableView=new QTableView;
    layout->addWidget(tableView);
}

void View::addChart(QHBoxLayout* layout) { //TEST
    chartView=new QChartView;
    layout->addWidget(chartView);
}

void View::setModel(QAbstractItemModel* m) {
    tableView->setModel(m);
}

void View::setController(Controller* c) {
    controller=c;
    connect(file->actions().at(0), SIGNAL(triggered()), controller, SLOT(renewGraph()));
}
