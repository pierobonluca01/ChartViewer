#include "dialogs.h"

NewDialog::NewDialog(QWidget* parent): QDialog(parent) {
    setWindowTitle(QString("Nuovo..."));

    nameLine=new QLineEdit;
    nameLine->setPlaceholderText(QString("senza_titolo"));
    nameLine->setMaxLength(30);

    rowsLine=new QLineEdit;
    rowsLine->setPlaceholderText(QString("0"));
    rowsLine->setValidator(new QIntValidator(0, 999));

    columnsLine=new QLineEdit;
    columnsLine->setPlaceholderText(QString("0"));
    columnsLine->setValidator(new QIntValidator(0, 999));

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

    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(confirmation, SIGNAL(clicked()), this, SLOT(updateText()));
    connect(confirmation, SIGNAL(clicked()), this, SLOT(accept()));
}

QString NewDialog::getName() const {
    return name;
}

size_t NewDialog::getRows() const {
    return rows;
}

size_t NewDialog::getColumns() const {
    return columns;
}


/*slots*/

void NewDialog::updateText() {
    name=nameLine->text();
    if(name=="")
        name="senza_nome";
    rows=rowsLine->text().toUInt();
    columns=columnsLine->text().toUInt();

}
