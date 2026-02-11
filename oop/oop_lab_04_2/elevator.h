#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>

#include "controller.h"
#include "cabin.h"
// #include "usings.h"

class Elevator: public QObject
{
    Q_OBJECT

public:
    explicit Elevator(QObject *parent = nullptr);
    ~Elevator() = default;

    QWidget *widget();

private:
    Controller _controller;
    Cabin _cabin_1;
    Cabin _cabin_2;

};

#endif // ELEVATOR_H
