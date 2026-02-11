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
    void setNumber(int number);

public slots:
    void slotCabinWaiting();
    void slotCabinMoving();
    void slotCabinStaying();
    void slotCabinMoved();


signals:
    void signalControllerNext(int, bool, int=1, Button::position_t = Button::position_t::NONE);
    void signalControllerMove(int);
    void signalDoorOpen();

private:
    Doors _doors;
    cabin_state_t _state;
    int _cabin_number;
    QTimer _timerMoving;

};

#endif // CABIN_H
