#include "cabin.h"

Cabin::Cabin(QObject *parent): QObject(parent)
{
    _state = WAITING;

    QObject::connect(&this->_timerMoving,SIGNAL(timeout()),            this,         SLOT(slotCabinMoved()));
    QObject::connect(this,               SIGNAL(signalDoorOpen()),     &this->_doors,SLOT(slotDoorOpening()));
    QObject::connect(&this->_doors,      SIGNAL(signalFloorFinished()),this,         SLOT(slotCabinWaiting()));
}

void Cabin::setNumber(int number)
{
    this->_cabin_number = number;
}

void Cabin::slotCabinWaiting()
{
    if (this->_state == STAYING)
    {
        this->_state = WAITING;
        qDebug() << "Cabin" << this->_cabin_number << "waiting";

        emit signalControllerNext(this->_cabin_number, false);
    }
}

void Cabin::slotCabinMoving()
{
    if (this->_state == WAITING || this->_state == MOVED)
    {
        this->_state = MOVING;
        qDebug() << "Cabin" << this->_cabin_number << "moving";

        this->_timerMoving.start(MOVING_TIME);
    }
}

void Cabin::slotCabinMoved()
{
    if (this->_state == MOVING)
    {
        _state = MOVED;
        this->_timerMoving.stop();
        // qDebug() << "Cabin" << this->_cabin_number << "moved";
        emit signalControllerMove(this->_cabin_number);
    }
}

void Cabin::slotCabinStaying()
{
    if (this->_state == MOVED || this->_state == WAITING || this->_state == STAYING)
    {
        this->_state = STAYING;
        qDebug() << "Cabin" << this->_cabin_number << "staying";
        
        this->_timerMoving.stop();

        emit signalDoorOpen();
    }
}


