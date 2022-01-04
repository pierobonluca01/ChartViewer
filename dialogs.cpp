#include "dialogs.h"

NewDialog::NewDialog(QWidget* parent): QDialog(parent) {

    QLineEdit* nameLine=new QLineEdit;
    nameLine->setPlaceholderText(QString("senzatitolo"));
    QLineEdit* rowsLine=new QLineEdit;
    rowsLine->setPlaceholderText(QString("0"));
    QLineEdit* columnsLine=new QLineEdit;
    columnsLine->setPlaceholderText(QString("0"));

    QGridLayout* grid=new QGridLayout();

    grid->addWidget(new QLabel("Nome:"), 0, 0);
    grid->addWidget(nameLine, 0, 1);
    grid->setVerticalSpacing(20);
    grid->addWidget(new QLabel("Righe:"), 1, 0);
    grid->addWidget(rowsLine, 1, 1);
    grid->addWidget(new QLabel("Colonne:"), 1, 2);
    grid->addWidget(columnsLine, 1, 3);

    setLayout(grid);

    //QPushButton* conferma=new QPushButton("C", this);
}

QString NewDialog::getName() {
    return name;
}

unsigned int NewDialog::getRows() {
    return rows;
}

unsigned int NewDialog::getColumns() {
    return columns;
}
