#include "dialogs.h"

NewDialog::NewDialog(QWidget* parent): QDialog(parent) {
    setWindowTitle(QString("Nuovo..."));

    QLineEdit* nameLine=new QLineEdit;
    nameLine->setPlaceholderText(QString("senza_titolo"));
    nameLine->setMaxLength(30);
    QLineEdit* rowsLine=new QLineEdit;
    rowsLine->setPlaceholderText(QString("0"));
    QLineEdit* columnsLine=new QLineEdit;
    columnsLine->setPlaceholderText(QString("0"));
    QPushButton* confirmation=new QPushButton("Conferma");
    QPushButton* cancel=new QPushButton("Annulla");

    QHBoxLayout *line1=new QHBoxLayout;
    line1->addWidget(new QLabel("Nome:"));
    line1->addWidget(nameLine);

    QHBoxLayout *line2=new QHBoxLayout;
    line2->addWidget(new QLabel("Righe:"));
    line2->addWidget(rowsLine);
    line2->addWidget(new QLabel("Colonne:"));
    line2->addWidget(columnsLine);

    QHBoxLayout *line3=new QHBoxLayout;
    line3->addSpacerItem(new QSpacerItem(150, 0));
    line3->addWidget(cancel);
    line3->addWidget(confirmation);

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addLayout(line1);
    layout->addLayout(line2);
    layout->addSpacerItem(new QSpacerItem(0, 20));
    layout->addLayout(line3);

    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    name=nameLine->text();

    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
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
