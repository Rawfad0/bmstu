#include "elevator.h"

Elevator::Elevator(QObject *parent) : QObject(parent)
{
    _controller.setStyleSheet("background-color:lightblue");

    QObject::connect(&_cabin,       SIGNAL(signalControllerMove()),         &_controller,   SLOT(slotControllerMoving()));
    QObject::connect(&_cabin,       SIGNAL(signalControllerNext(bool)),     &_controller,   SLOT(slotControllerTargeting(bool)));
    QObject::connect(&_controller,  SIGNAL(signalCabinMove()),              &_cabin,        SLOT(slotCabinMoving()));
    QObject::connect(&_controller,  SIGNAL(signalCabinStay()),              &_cabin,        SLOT(slotCabinStaying()));
}


QWidget *Elevator::widget()
{
    return &_controller;
}
