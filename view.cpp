#include "view.h"
#include "controller.h"

View::View(QWidget* parent): QWidget(parent) {
    setWindowIcon(QIcon(":/images/chart"));
    setWindowTitle(QString("ChartViewer"));

    chart=new BarChart;
    //setChartType(); //default chart

    QVBoxLayout* mainLayout=new QVBoxLayout;
    addMenus(mainLayout);
    addToolBar(mainLayout);
    graphSplitter=new QSplitter;
    addTable(graphSplitter);
    addChart(graphSplitter);
    graphSplitter->setSizes({this->width()/2, this->width()/2});
    mainLayout->addWidget(graphSplitter);

    setLayout(mainLayout);

    resize(900, 500);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), QApplication::desktop()->availableGeometry()));
    setGlobalTheme(1);
    setTableTheme(1);
}

void View::addMenus(QVBoxLayout* layout) {
    QMenuBar* menuBar=new QMenuBar(this);
    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    file=new QMenu("File", menuBar);
    view=new QMenu("Vista", menuBar);
    chartType=new QMenu("Grafico", menuBar);
    themes=new QMenu("Temi", menuBar);


    //FILE
    file->addAction(new QAction("Nuovo...", file));
    menuBar->addMenu(file);


    //VIEW
    //splitter
    QMenu* viewSplitter=new QMenu("Separatore", view);
    viewSplitter->addAction(new QAction("Reimposta", viewSplitter));
    viewSplitter->addAction(new QAction("Nascondi tabella", viewSplitter));
    viewSplitter->addAction(new QAction("Nascondi grafico", viewSplitter));
    QSignalMapper* viewSplitterSignals=new QSignalMapper;
    for(int i=0; i<3; i++) {
        connect(viewSplitter->actions().at(i), SIGNAL(triggered()), viewSplitterSignals, SLOT(map()));
        viewSplitterSignals->setMapping(viewSplitter->actions().at(i), i);
    }
    connect(viewSplitterSignals, SIGNAL(mapped(int)), this, SLOT(setSplitter(int)));
    view->addMenu(viewSplitter);

    //zoom
    QMenu* viewZoom=new QMenu("Zoom", view);
    viewZoom->addAction(new QAction("Zoom Out -", viewZoom));
    viewZoom->addAction(new QAction("Zoom In +", viewZoom));
    QSignalMapper* viewZoomSignals=new QSignalMapper;
    connect(viewZoom->actions().at(0), SIGNAL(triggered()), viewZoomSignals, SLOT(map()));
    viewZoomSignals->setMapping(viewZoom->actions().at(0), 0);
    connect(viewZoom->actions().at(1), SIGNAL(triggered()), viewZoomSignals, SLOT(map()));
    viewZoomSignals->setMapping(viewZoom->actions().at(1), 1);
    connect(viewZoomSignals, SIGNAL(mapped(int)), this, SLOT(setChartZoom(int)));
    view->addMenu(viewZoom);

    menuBar->addMenu(view);


    //CHARTTYPE
    QActionGroup* chartTypeGroup=new QActionGroup(chartType);
    chartTypeGroup->setExclusive(true);
    chartTypeGroup->addAction(chartType->addAction(QString("Bar Chart (Grafico a barre)")))->setCheckable(true);
    chartTypeGroup->actions().at(0)->setChecked(true);
    chartTypeGroup->addAction(chartType->addAction(QString("Line Chart (Grafico a linee)")))->setCheckable(true);
    chartTypeGroup->addAction(chartType->addAction(QString("Pie Chart (Grafico a torta)")))->setCheckable(true);
    QSignalMapper* chartTypeSignals=new QSignalMapper;
    for(int i=0; i<2; i++) {
        connect(chartType->actions().at(i), SIGNAL(triggered()), chartTypeSignals, SLOT(map()));
        chartTypeSignals->setMapping(chartType->actions().at(i), i);
    }
    connect(chartTypeSignals, SIGNAL(mapped(int)), this, SLOT(setChartType(int)));
    menuBar->addMenu(chartType);


    //THEMES
    //global
    QMenu* themesGlobal=new QMenu("Globali", themes);

    QActionGroup* themesGlobalGroup=new QActionGroup(themesGlobal);
    themesGlobalGroup->setExclusive(true);
    themesGlobalGroup->addAction(themesGlobal->addAction((QString("Light"))))->setCheckable(true);
    themesGlobalGroup->addAction(themesGlobal->addAction((QString("Blue Cerulean"))))->setCheckable(true);
    themesGlobalGroup->actions().at(1)->setChecked(true);
    themesGlobalGroup->addAction(themesGlobal->addAction((QString("Dark"))))->setCheckable(true);
    themesGlobalGroup->addAction(themesGlobal->addAction((QString("Brown Sand"))))->setCheckable(true);
    themesGlobalGroup->addAction(themesGlobal->addAction((QString("Blue Ncs"))))->setCheckable(true);
    themesGlobalGroup->addAction(themesGlobal->addAction((QString("High Contrast"))))->setCheckable(true);
    themesGlobalGroup->addAction(themesGlobal->addAction((QString("Blue Icy"))))->setCheckable(true);
    themesGlobalGroup->addAction(themesGlobal->addAction((QString("Qt"))))->setCheckable(true);
    QSignalMapper* themesGlobalSignals=new QSignalMapper;
    for(int i=0; i<8; i++) {
        connect(themesGlobal->actions().at(i), SIGNAL(triggered()), themesGlobalSignals, SLOT(map()));
        themesGlobalSignals->setMapping(themesGlobal->actions().at(i), i);
    }
    connect(themesGlobalSignals, SIGNAL(mapped(int)), this, SLOT(setGlobalTheme(int)));
    themes->addMenu(themesGlobal);

    //table
    QMenu* themesTable=new QMenu("Tabella", themes);

    QActionGroup* themesTableGroup=new QActionGroup(themesTable);
    themesTableGroup->setExclusive(true);
    themesTableGroup->addAction(themesTable->addAction((QString("Light"))))->setCheckable(true);
    themesTableGroup->addAction(themesTable->addAction((QString("Dark"))))->setCheckable(true);
    themesTableGroup->actions().at(1)->setChecked(true);
    QSignalMapper* themesTableSignals=new QSignalMapper;
    for(int i=0; i<2; i++) {
        connect(themesTableGroup->actions().at(i), SIGNAL(triggered()), themesTableSignals, SLOT(map()));
        themesTableSignals->setMapping(themesTableGroup->actions().at(i), i);
    }
    connect(themesTableSignals, SIGNAL(mapped(int)), this, SLOT(setTableTheme(int)));
    themes->addMenu(themesTable);

    menuBar->addMenu(themes);

    layout->addWidget(menuBar);
}

void View::addToolBar(QVBoxLayout* layout) {
    QToolBar* toolBar=new QToolBar;
    layout->addWidget(toolBar);
}

void View::addTable(QSplitter* splitter) {
    tableView=new QTableView;
    splitter->addWidget(tableView);
}

void View::addChart(QSplitter* splitter) {
    chartView=new QChartView(chart->getChart());
    splitter->addWidget(chartView);
}

void View::setModel(QAbstractItemModel* m) {
    tableView->setModel(m);
    chart->setModel(m);
}

void View::setController(Controller* c) {
    controller=c;
    setWindowTitle(QString(controller->getName()+" | ChartViewer"));
    //chart->setController(c);
    connect(file->actions().at(0), SIGNAL(triggered()), controller, SLOT(renewGraph()));
}

void View::setSplitter(int split) const {
    QList<int> width;
    switch(split) {
    case 1:
        width={0, view->width()};
        break;
    case 2:
        width={view->width(), 0};
        break;
    default:
        width={view->width(), view->width()};
    }
    graphSplitter->setSizes(width);
}

void View::setChartZoom(int z) const {
    if(z)
        chart->getChart()->zoomIn();
    else
        chart->getChart()->zoomOut();
}

void View::setChartType(int c) {
    switch(c) {
    case 1:
        chart=new LineChart;
        break;
    case 2:
        chart=new PieChart;
        break;
    default:
        chart=new BarChart;
    }
}

void View::setGlobalTheme(int theme) const {
    QPalette palette=window()->palette();
    switch(theme) {
    case 0:
        palette.setColor(QPalette::Window, QRgb(0xf0f0f0));
        palette.setColor(QPalette::WindowText, QRgb(0x404044));
        chart->setChartTheme(QChart::ChartThemeLight);
        break;
    case 2:
        palette.setColor(QPalette::Window, QRgb(0x40434a));
        palette.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
       chart->setChartTheme(QChart::ChartThemeDark);
        break;
    case 3:
        palette.setColor(QPalette::Window, QRgb(0x9e8965));
        palette.setColor(QPalette::WindowText, QRgb(0x404044));
        chart->setChartTheme(QChart::ChartThemeBrownSand);
        break;
    case 4:
        palette.setColor(QPalette::Window, QRgb(0x018bba));
        palette.setColor(QPalette::WindowText, QRgb(0x404044));
        chart->setChartTheme(QChart::ChartThemeBlueNcs);
        break;
    case 5:
        palette.setColor(QPalette::Window, QRgb(0xffab03));
        palette.setColor(QPalette::WindowText, QRgb(0x181818));
        chart->setChartTheme(QChart::ChartThemeHighContrast);
        break;
    case 6:
        palette.setColor(QPalette::Window, QRgb(0xcee7f0));
        palette.setColor(QPalette::WindowText, QRgb(0x404044));
        chart->setChartTheme(QChart::ChartThemeBlueIcy);
        break;
    case 7:
        palette.setColor(QPalette::Window, QRgb(0xf0f0f0));
        palette.setColor(QPalette::WindowText, QRgb(0x404044));
        chart->setChartTheme(QChart::ChartThemeQt);
        break;
    default:
        palette.setColor(QPalette::Window, QRgb(0x121218));
        palette.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        chart->setChartTheme(QChart::ChartThemeBlueCerulean);
    }
    window()->setPalette(palette);
}

void View::setTableTheme(int theme) const {
    QPalette light;
    light.setColor(QPalette::Background, QRgb(0x2a2e32));
    light.setColor(QPalette::Base, QRgb(0xf0f0f0));
    light.setColor(QPalette::Text, QRgb(0x404044));

    QPalette dark;
    dark.setColor(QPalette::Background, QRgb(0x2a2e32));
    dark.setColor(QPalette::Base, QRgb(0x1b1e20));
    dark.setColor(QPalette::Text, QRgb(0xd6d6d6));

    switch(theme) {
    case 0:
        tableView->setPalette(light);
        break;
    default:
        tableView->setPalette(dark);
    }
}
