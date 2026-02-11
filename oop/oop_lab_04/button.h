#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QDebug>
#include <QPushButton>

class Button: public QPushButton
{
    Q_OBJECT

public:
    explicit Button(QWidget *parent = nullptr);
    ~Button() override = default;
    enum state_t { PRESSED, UNPRESSED };
    enum direction_t { DOWN, NONE, UP };
    void setFloor(int floor);
    void setDirection(direction_t direction);

public slots:
    void slotButtonPressed();
    void slotButtonUnpressed();

signals:
    void signalControllerTarget(bool, int, Button::direction_t);
    void signalButtonRelease();

private:
    state_t _state;
    int _floor;
    direction_t _direction;

};

#endif // BUTTON_H
