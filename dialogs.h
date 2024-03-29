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
    ~NewDialog() =default;

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
    ~EditLabelDialog() =default;

    QString getLabel() const;

public slots:
    void updateLabel();
};


class AddDialog: public QDialog {
    Q_OBJECT

private:
    size_t num;
    QLineEdit* numLine;

public:
    AddDialog(bool, QWidget* =nullptr);
    ~AddDialog() =default;

    size_t getNum() const;

public slots:
    void updateNum();
};

#endif // DIALOGS_H
