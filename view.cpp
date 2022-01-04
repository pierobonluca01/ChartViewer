#include "view.h"
#include "controller.h"

View::View(QWidget* parent): QWidget(parent) {
    setWindowIcon(QIcon(":/images/chart"));
    setWindowTitle(QString("ChartViewer: untitled_graph"));

    QVBoxLayout* mainLayout=new QVBoxLayout;

    addMenus(mainLayout);
    addTable(mainLayout);

    setLayout(mainLayout);
}

void View::addMenus(QVBoxLayout* layout) {
    QMenuBar* menuBar=new QMenuBar(this);

    file=new QMenu("File", menuBar);

    menuBar->addMenu(file);
    file->addAction(new QAction("Nuovo...", file));

    layout->addWidget(menuBar);
}

void View::addTable(QVBoxLayout* layout) {
    tableView=new QTableView;
    layout->addWidget(tableView);
}

void View::setModel(QAbstractItemModel* m) {
    tableView->setModel(m);
}

void View::setController(Controller* c) {
    controller=c;
    //connect(file->actions()[0], SIGNAL(triggered()), controller, SLOT(newGraph()));
}
