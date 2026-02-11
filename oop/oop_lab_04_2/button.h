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
    enum position_t { NONE, DOWN, UP, CABIN1, CABIN2 };
    void setFloor(int floor);
    void setPosition(position_t direction);

public slots:
    void slotButtonPressed();
    void slotButtonUnpressed();

signals:
    void signalControllerTarget(int, bool, int, Button::position_t);
    void signalButtonRelease();

private:
    state_t _state;
    int _floor;
    position_t _position;

};

#endif // BUTTON_H
