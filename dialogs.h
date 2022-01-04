#ifndef DIALOGS_H
#define DIALOGS_H

#include <cstdlib>
using std::size_t;

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QApplication>
#include <QBoxLayout>

class NewDialog: public QDialog {
    Q_OBJECT

private:
    QString name;
    unsigned int rows;
    unsigned int columns;

public:
    NewDialog(QWidget* =nullptr);

    QString getName();
    unsigned int getRows();
    unsigned int getColumns();
};

#endif // DIALOGS_H
