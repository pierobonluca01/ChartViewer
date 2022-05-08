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
    size_t rows;
    size_t columns;

    QLineEdit* nameLine;
    QLineEdit* rowsLine;
    QLineEdit* columnsLine;

public:
    NewDialog(QWidget* =nullptr);

    QString getName() const;
    size_t getRows() const;
    size_t getColumns() const;

public slots:
    void updateText();
};


class EditLabelDialog: public QDialog {
    Q_OBJECT

private:
    QString label;
    QLineEdit* labelLine;

public:
    EditLabelDialog(bool, QString, QWidget* =nullptr);

    QString getLabel() const;

public slots:
    void updateLabel();
};

#endif // DIALOGS_H
