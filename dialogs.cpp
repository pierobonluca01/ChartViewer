#include "dialogs.h"


//NEW DIALOG

NewDialog::NewDialog(QWidget* parent): QDialog(parent) {
    setWindowTitle(QString("Nuovo..."));

    nameLine=new QLineEdit;
    nameLine->setPlaceholderText(QString("senza_titolo"));
    nameLine->setMaxLength(30);

    rowsLine=new QLineEdit;
    rowsLine->setPlaceholderText(QString("0"));
    rowsLine->setValidator(new QIntValidator(0, 999, rowsLine));

    columnsLine=new QLineEdit;
    columnsLine->setPlaceholderText(QString("0"));
    columnsLine->setValidator(new QIntValidator(0, 999, columnsLine));


    QHBoxLayout *line1=new QHBoxLayout;
    line1->addWidget(new QLabel("Nome:"));
    line1->addWidget(nameLine);

    QHBoxLayout *line2=new QHBoxLayout;
    line2->addWidget(new QLabel("Righe:"));
    line2->addWidget(rowsLine);
    line2->addWidget(new QLabel("Colonne:"));
    line2->addWidget(columnsLine);

    QPushButton* confirmation=new QPushButton("Conferma");
    QPushButton* cancel=new QPushButton("Annulla");

    QHBoxLayout *line3=new QHBoxLayout;
    line3->addSpacerItem(new QSpacerItem(150, 0));
    line3->addWidget(cancel);
    line3->addWidget(confirmation);

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addLayout(line1);
    layout->addLayout(line2);
    layout->addSpacerItem(new QSpacerItem(0, 20));
    layout->addWidget(new QLabel("<b>Attenzione</b>: I dati non salvati andranno persi."));
    layout->addSpacerItem(new QSpacerItem(0, 10));
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


//EDIT LABEL DIALOG

EditLabelDialog::EditLabelDialog(bool orientation, QString oldLabel, QWidget* parent): QDialog(parent) {
    setWindowTitle(QString("Modifica intestazione..."));

    labelLine=new QLineEdit;
    labelLine->setPlaceholderText(QString("intestazione"));
    labelLine->setMaxLength(30);
    QPushButton* confirmation=new QPushButton("Conferma");
    QPushButton* cancel=new QPushButton("Annulla");

    QHBoxLayout *line=new QHBoxLayout;
    line->addWidget(new QLabel("Nuova intestazione:"));
    line->addWidget(labelLine);

    QHBoxLayout *buttons=new QHBoxLayout;
    buttons->addSpacerItem(new QSpacerItem(150, 0));
    buttons->addWidget(cancel);
    buttons->addWidget(confirmation);
    cancel->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *layout=new QVBoxLayout(this);
    QString o="colonna";
    if(orientation)
        o="riga";
    layout->addWidget(new QLabel("Stai modificando l'intestazione della <b>"+o+"</b> \"<i>"+oldLabel+"\"</i>."));
    layout->addLayout(line);
    layout->addSpacerItem(new QSpacerItem(0, 20));
    layout->addLayout(buttons);

    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(confirmation, SIGNAL(clicked()), this, SLOT(updateLabel()));
    connect(confirmation, SIGNAL(clicked()), this, SLOT(accept()));
}

QString EditLabelDialog::getLabel() const {
    return label;
}

/*slots*/

void EditLabelDialog::updateLabel() {
    label=labelLine->text();
    if(label=="")
        label="intestazione";
}


//ADD DIALOG

AddDialog::AddDialog(bool orientation, QWidget* parent): QDialog(parent) {
    QString o="colonne";
    if(orientation)
        o="righe";
    setWindowTitle(QString("Aggiungi "+o+"..."));

    numLine=new QLineEdit;
    numLine->setPlaceholderText(QString("1"));
    numLine->setValidator(new QIntValidator(0, 999));

    QPushButton* confirmation=new QPushButton("Conferma");
    QPushButton* cancel=new QPushButton("Annulla");

    QHBoxLayout *line=new QHBoxLayout;

    line->addWidget(new QLabel("Numero "+o+":"));
    line->addWidget(numLine);

    QHBoxLayout *buttons=new QHBoxLayout;
    buttons->addSpacerItem(new QSpacerItem(150, 0));
    buttons->addWidget(cancel);
    buttons->addWidget(confirmation);
    cancel->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(new QLabel("Quante <b>"+o+"</b> vuoi aggiungere?"));
    layout->addLayout(line);
    layout->addSpacerItem(new QSpacerItem(0, 20));
    layout->addLayout(buttons);

    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(confirmation, SIGNAL(clicked()), this, SLOT(updateNum()));
    connect(confirmation, SIGNAL(clicked()), this, SLOT(accept()));
}

size_t AddDialog::getNum() const {
    return num;
}

void AddDialog::updateNum() {
    QString numstring=numLine->text();
    if(numstring=="")
        numstring="1";
    num=numstring.toUInt();
}
