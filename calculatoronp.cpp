#include "calculatoronp.h"
#include <QDebug>
#include <QStack>

CalculatorONP::CalculatorONP(QObject *parent) : QObject(parent)
{

}

void CalculatorONP::input(QString input)
{
    qDebug()<<"Przetwarzam "<<input;
    //najpierw dziele string wzgledem spacji
    QStringList splittedInput = input.split(' ');
    //Jesli nie mozna podzielic spacjami zwracam error
    if(splittedInput.size() == 1)
    {
        emit output(QString("Niewłaściwy format wejściowy. Należy użyć spacji jako sepratora"));
        return;
    }

    //sprawdzam czy string zawiera cyfru i operatory matematyczne
    bool cyfra = false;
    bool oper = false;
    for(QString str:splittedInput)
    {
        if(str[0].isDigit())
        {
            cyfra = true;
        }

        if(str.contains('+') || str.contains('-') ||
                str.contains('/') || str.contains('+'))
        {
            oper = true;
        }
    }
    if(!cyfra || !oper)
    {
        emit output(QString("Wyrazenie musi zawierac liczby i operatory matematyczne"));
        return;
    }
    emit output(evaluate(splittedInput));
}

QString CalculatorONP::evaluate(QStringList eq)
{
    //decyduje sie na double
    QStack<double> liczby;
    //stack<int> liczby;
    int liczba_elementow = eq.size();
    for (int i = 0; i < liczba_elementow; i ++)
    {
        QString element = eq.at(i);
        qDebug()<<"El: "<<element;
        //jesli operator
        if ((element.compare("+")==0) || (element.compare("-")==0) || (element.compare("*")==0) || (element.compare("/")==0))
        {
            // sciagam dwie liczby z stosu
            double a = liczby.top();
            liczby.pop();
            double b = liczby.top();
            liczby.pop();
            qDebug()<<"Sciagam "<<a<<" oraz "<<b;
            qDebug()<<"Stack "<<" "<<liczby;
            // obliczam wynik i odkladam rezultat spowrotem
            switch (element[0].toLatin1())
            {
                case '+':
                    qDebug()<<"Obliczanie + odkladam"<<a+b;
                    liczby.push(a + b);
                    qDebug()<<"Stack "<<" "<<liczby;
                break;
                case '-':
                    qDebug()<<"Obliczanie - odkladam"<<a-b;
                    liczby.push(b - a);
                    qDebug()<<"Stack "<<" "<<liczby;
                break;
                case '*':
                    qDebug()<<"Obliczanie * odkladam"<<a*b;
                    liczby.push(b * a);
                    qDebug()<<"Stack "<<" "<<liczby;
                break;
                case '/':
                    qDebug()<<"Obliczanie / odkladam"<<a/b;
                    liczby.push(b / a);
                    qDebug()<<"Stack "<<" "<<liczby;
                break;
            }
        }
        else
        {
            if(element[0].isDigit() == false)
            {
                qDebug()<<"Element nie jest operatora ani liczbą!";
                return QString("Wyrażenie zawiera nie obslugiwany element <%1>").arg(element);
            }
            // dodaje liczbe do stosu
            qDebug()<<"Odkladam "<<element.toDouble();
            liczby.push(element.toDouble());
            qDebug()<<"Stack "<<" "<<liczby;
        }
    }
    if (liczby.size())
    {
        double res = liczby.top();
        while (liczby.size())
        {
            liczby.pop();
        }
       return QString("%1").arg(res);
    }
    //Nieznany blad
    return QString("Nie udalo sie obliczyc wartosc wyrazenia!");
}
