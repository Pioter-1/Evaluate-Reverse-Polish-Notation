#ifndef CALCULATORONP_H
#define CALCULATORONP_H

#include <QObject>
#include <QString>

class CalculatorONP : public QObject
{
    Q_OBJECT
public:
    explicit CalculatorONP(QObject *parent = 0);

signals:
    //zwrot odpowiedzi
    void output(QString output);
public slots:
    //przyjecie danych wejsciowych
    void input(QString input);
private:
    //obliczenia
    QString evaluate(QStringList eq);
};

#endif // CALCULATORONP_H
