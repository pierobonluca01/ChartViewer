#include "view.h"

View::View(QWidget* parent): QWidget(parent) {
    setWindowIcon(QIcon(":/images/chart"));

    QVBoxLayout* mainLayout=new QVBoxLayout;

    addMenus(mainLayout);
    addTable(mainLayout);

    setLayout(mainLayout);
}

void View::addMenus(QVBoxLayout* layout) {
    QMenuBar* menuBar=new QMenuBar(this);

    file=new QMenu("File", menuBar);

    menuBar->addMenu(file);

    layout->addWidget(menuBar);
}

void View::addTable(QVBoxLayout* layout) {
    table=new QTableView;
    layout->addWidget(table);
}

void View::setModel(QAbstractItemModel* model) { //test
    table->setModel(model);
}
