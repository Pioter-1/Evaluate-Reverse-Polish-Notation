#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "calculatoronp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    //przeslanie wyrazenia do kalkulatora
    void sigCalculate(QString calc);
public slots:
    //obsluga enter w line edit
    void onTextEditEnterPress();
    //reakcja na wynik kalkulatora
    void onResult(QString result);
private:
    Ui::MainWindow *ui;
    //instrukcja uzytkownika
    void printInstructions();
    //obiekt kalkulatora
    CalculatorONP* mKalkulator;
    //do prezentacji wyniku w calosci
    QString mMessageAppender;
};

#endif // MAINWINDOW_H
