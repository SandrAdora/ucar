#ifndef ZEITRAUM_H
#define ZEITRAUM_H

#include <QTime>

class Zeitraum
{
    QTime beginn;
    QTime ende;

public:
    Zeitraum();
    Zeitraum(QTime, QTime);
    ~Zeitraum();
    QTime get_beginn();
    void set_beginn(QTime);
    QTime get_ende();
    void set_ende(QTime);

    Zeitraum & operator=(const Zeitraum &);
};

QString int_toTag(int);

#endif // ZEITRAUM_H
