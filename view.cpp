#include "view.h"
#include "controller.h"

View::View(QWidget* parent): QWidget(parent) {
    setWindowIcon(QIcon(":/images/chart"));
    setWindowTitle(QString("ChartViewer: senza_titolo"));

    QVBoxLayout* mainLayout=new QVBoxLayout;
    addMenus(mainLayout);
    graphSplitter=new QSplitter;
    addTable(graphSplitter);
    addChart(graphSplitter);
    graphSplitter->setSizes({this->width()/2, this->width()/2});
    mainLayout->addWidget(graphSplitter);

    setLayout(mainLayout);
}

void View::addMenus(QVBoxLayout* layout) {
    QMenuBar* menuBar=new QMenuBar(this);

    file=new QMenu("File", menuBar);
    view=new QMenu("Vista", menuBar);

    file->addAction(new QAction("Nuovo...", file));
    menuBar->addMenu(file);

    view->addAction(new QAction("Reimposta", view));
    connect(view->actions().at(0), SIGNAL(triggered()), this, SLOT(splitView(0)));
    view->addAction(new QAction("Nascondi tabella", view));
    connect(view->actions().at(1), SIGNAL(triggered()), this, SLOT(splitView(1)));
    view->addAction(new QAction("Nascondi grafico", view));
    connect(view->actions().at(2), SIGNAL(triggered()), this, SLOT(splitView(2)));
    menuBar->addMenu(view);

    layout->addWidget(menuBar);
}

void View::addTable(QSplitter* splitter) {
    tableView=new QTableView;
    splitter->addWidget(tableView);
}

void View::addChart(QSplitter* splitter) { //TEST
    chartView=new QChartView;
    splitter->addWidget(chartView);
}

void View::setModel(QAbstractItemModel* m) {
    tableView->setModel(m);
}

void View::setController(Controller* c) {
    controller=c;
    connect(file->actions().at(0), SIGNAL(triggered()), controller, SLOT(renewGraph()));
}

void View::splitView(int split) const {
    QList<int> width;
    switch(split) {
    case 1:
        width={0, view->width()};
        break;
    case 2:
        width={view->width(), 0};
        break;
    default:
        width={view->width()/2, view->width()/2};
    }
    graphSplitter->setSizes(width);
}
