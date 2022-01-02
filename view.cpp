#include "view.h"

View::View(QWidget* parent): QWidget(parent) {
    QVBoxLayout* mainLayout=new QVBoxLayout;

    addMenus(mainLayout);
    addTable(mainLayout);

    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    resize(QSize(1024, 720));
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

void View::setModel(QAbstractItemModel* model) {
    table->setModel(model);
}
