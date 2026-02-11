#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QTimer>

#include "doors.h"
#include "button.h"

#define MOVING_TIME 2000

class Cabin: public QObject
{
    Q_OBJECT
public:
    Cabin(QObject *parent = nullptr);
    enum cabin_state_t { WAITING, MOVING, MOVED, STAYING};

public slots:
    void slotCabinWaiting();
    void slotCabinMoving();
    void slotCabinStaying();
    void slotCabinMoved();


signals:
    void signalControllerNext(bool, int=1, Button::direction_t = Button::direction_t::NONE);
    void signalControllerMove();
    void signalDoorOpen();

private:
    Doors _doors;
    cabin_state_t _state;
    QTimer _timerMoving;

};

#endif // CABIN_H
