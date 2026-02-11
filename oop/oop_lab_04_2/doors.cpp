#include "doors.h"

Doors::Doors(QObject *parent): QObject(parent)
{
    _state = CLOSED;

    QObject::connect(&_timerOpening,    SIGNAL(timeout()),  this, SLOT(slotDoorOpened()));
    QObject::connect(&_timerWaiting,    SIGNAL(timeout()),  this, SLOT(slotDoorClosing()));
    QObject::connect(&_timerClosing,    SIGNAL(timeout()),  this, SLOT(slotDoorClosed()));
}

void Doors::slotDoorOpening()
{
    if (this->_state == CLOSED)
    {
        this->_state = OPENING;
        qDebug() << "Doors are opening";

        this->_timerOpening.start(OPENING_TIME);
    }
    else if (this->_state == CLOSING)
    {
        this->_state = OPENING;
    
        auto remain_time = this->_timerClosing.remainingTime();
        qDebug() << "Doors are opening (from closing)";
        this->_timerClosing.stop();
        this->_timerOpening.start(OPENING_TIME - remain_time);
    }
    // else
    //     qDebug() << "Doors slot: opening (incorrect _state)" << this->_state;
}

void Doors::slotDoorOpened()
{
    if (this->_state == OPENING)
    {
        this->_state = OPENED;
        qDebug() << "Doors are opened";

        this->_timerWaiting.start(WAITING_TIME);
    }
    // else
    //     qDebug() << "Doors slot: opened (incorrect _state)" << this->_state;
}

void Doors::slotDoorClosing()
{
    if (this->_state == OPENED)
    {
        this->_state = CLOSING;
        qDebug() << "Doors are closing";

        this->_timerClosing.start(CLOSING_TIME);
    }
    // else
    //     qDebug() << "Doors slot: closing (incorrect _state)" << this->_state;
}

void Doors::slotDoorClosed()
{
    if (this->_state == CLOSING)
    {
        this->_state = CLOSED;
        qDebug() << "Doors are closed";

        emit signalFloorFinished();
    }
    // else
    //     qDebug() << "Doors slot: closed (incorrect _state)" << _state;
}
