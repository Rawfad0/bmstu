#ifndef DOORS_H
#define DOORS_H

#include<QObject>
#include<QTimer>
#include <QDebug>

#define OPENING_TIME 1000
#define WAITING_TIME 1000
#define CLOSING_TIME 1000

class Doors: public QObject
{
    Q_OBJECT
public:
    Doors(QObject *parent = nullptr);
    enum door_state_t { CLOSED, OPENING, OPENED, CLOSING };

public slots:
    void slotDoorOpening();
    void slotDoorOpened();
    void slotDoorClosing();
    void slotDoorClosed();

signals:
    void signalFloorFinished();

private:
    door_state_t _state;
    QTimer _timerOpening;
    QTimer _timerWaiting;
    QTimer _timerClosing;

};

#endif // DOORS_H
