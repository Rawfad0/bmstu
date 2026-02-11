#include "cabin.h"

Cabin::Cabin(QObject *parent): QObject(parent)
{
    _state = WAITING;

    QObject::connect(&_timerMoving, SIGNAL(timeout()),              this, SLOT(slotCabinMoved()));
    QObject::connect(this,          SIGNAL(signalDoorOpen()),       &_doors, SLOT(slotDoorOpening()));
    QObject::connect(&_doors,       SIGNAL(signalFloorFinished()),  this, SLOT(slotCabinWaiting()));
}

void Cabin::slotCabinWaiting()
{
    if (this->_state == STAYING)
    {
        this->_state = WAITING;
        qDebug() << "Cabin waiting";

        emit signalControllerNext(false);
    }
}

void Cabin::slotCabinMoving()
{
    if (this->_state == WAITING || this->_state == MOVED)
    {
        this->_state = MOVING;
        qDebug() << "Cabin moving";

        this->_timerMoving.start(MOVING_TIME);
    }
}

void Cabin::slotCabinMoved()
{
    if (this->_state == MOVING)
    {
        _state = MOVED;
        this->_timerMoving.stop();
        // qDebug() << "Cabin moved";
        emit signalControllerMove();
    }
}

void Cabin::slotCabinStaying()
{
    if (this->_state == MOVED || this->_state == WAITING || this->_state == STAYING)
    {
        this->_state = STAYING;
        qDebug() << "Cabin staying";
        
        this->_timerMoving.stop();

        emit signalDoorOpen();
    }
}

