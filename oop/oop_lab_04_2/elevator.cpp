#include "elevator.h"

Elevator::Elevator(QObject *parent) : QObject(parent)
{
    _controller.setStyleSheet("background-color:lightblue");

    QObject::connect(&_cabin_1,     SIGNAL(signalControllerMove(int)),      &_controller,   SLOT(slotControllerMoving(int)));
    QObject::connect(&_cabin_1,     SIGNAL(signalControllerNext(int, bool)),&_controller,   SLOT(slotControllerTargeting(int, bool)));
    QObject::connect(&_cabin_2,     SIGNAL(signalControllerMove(int)),      &_controller,   SLOT(slotControllerMoving(int)));
    QObject::connect(&_cabin_2,     SIGNAL(signalControllerNext(int, bool)),&_controller,   SLOT(slotControllerTargeting(int, bool)));
    QObject::connect(&_controller,  SIGNAL(signalCabin1Move()),             &_cabin_1,      SLOT(slotCabinMoving()));
    QObject::connect(&_controller,  SIGNAL(signalCabin1Stay()),             &_cabin_1,      SLOT(slotCabinStaying()));
    QObject::connect(&_controller,  SIGNAL(signalCabin2Move()),             &_cabin_2,      SLOT(slotCabinMoving()));
    QObject::connect(&_controller,  SIGNAL(signalCabin2Stay()),             &_cabin_2,      SLOT(slotCabinStaying()));

    _cabin_1.setNumber(1);
    _cabin_2.setNumber(2);
}


QWidget *Elevator::widget()
{
    return &_controller;
}
