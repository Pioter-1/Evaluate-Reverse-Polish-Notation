#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //tworze instancje kalkulatora
    mKalkulator = new CalculatorONP(this);
    //drukuje instrukcje dla uzytkownika
    printInstructions();
    //nacisniecie enter zostanie obsluzone w onTextEditEnterPress
    connect(ui->lineEdit,&QLineEdit::returnPressed,this, &MainWindow::onTextEditEnterPress);
    //wyrazenie podlaczone do kalkulatora
    connect(this,&MainWindow::sigCalculate, mKalkulator, &CalculatorONP::input);
    //wynik obliczenia podlaczony do ui
    connect(mKalkulator,&CalculatorONP::output,this,&MainWindow::onResult);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTextEditEnterPress()
{
    //popieram wyraznie ONP
    QString line = ui->lineEdit->text();
    //czyszcze input line
    ui->lineEdit->clear();
    //qDebug()<<"Enter pressed: "<<line;
    //czyszcze i zapamietuje pierwsza czesc wiadomosci
    mMessageAppender.clear();
    mMessageAppender.append(QString("Wyrażenie:<%1> ").arg(line));

    //przesylam wyrazenie do kalkulatora
    emit sigCalculate(line);
}

void MainWindow::onResult(QString result)
{
    qDebug()<<"Otrzymalem wynik "<<result;
    //umieszczam wynik w oknie
    ui->textBrowser->append(QString("%1 Wynik <%2>\n").arg(mMessageAppender).arg(result));
}

void MainWindow::printInstructions()
{
    QString instrukcja("Proszę podać wyrażenie w odwrotnej notacji Polskiej.\n"
                       "Po naciśnięciu Enter Wynik pojawi sie na ekranie\n"
                       "Wartości liczbowe i operatory matematyczne należy rozdzielić spacją\n"
                       "Program wspiera operatory \"+\",\"-\",\"*\",\"/\"\n"
                       "Proszę szczególną uwagę zwrócić na <-> przy kopiowaniu ze schowka\n"
                       "--------------------------------------------------------------------------\n");
    ui->textBrowser->setText(instrukcja);
}
