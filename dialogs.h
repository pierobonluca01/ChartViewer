#ifndef DIALOGS_H
#define DIALOGS_H

#include <cstdlib>
using std::size_t;

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QValidator>
#include <QDialog>
#include <QApplication>
#include <QBoxLayout>

class NewDialog: public QDialog {
    Q_OBJECT

private:
    QString name;
    unsigned int rows;
    unsigned int columns;

    QLineEdit* nameLine;
    QLineEdit* rowsLine;
    QLineEdit* columnsLine;

public:
    NewDialog(QWidget* =nullptr);

    QString getName() const;
    unsigned int getRows() const;
    unsigned int getColumns() const;

public slots:
    void getText();
};

#endif // DIALOGS_H
