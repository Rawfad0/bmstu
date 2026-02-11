#include "button.h"
#include "usings.h"

Button::Button(QWidget *parent): QPushButton(parent)
{
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(slotButtonPressed()));
    QObject::connect(this, SIGNAL(signalButtonRelease()), this, SLOT(slotButtonUnpressed())); // Выключается когда лифт приедет и издаст сигнал

    _state = UNPRESSED;
    _floor = 1;
    _direction = NONE;
}

void Button::setFloor(int floor)
{
    _floor = floor;
}

void Button::setDirection(Button::direction_t direction)
{
    _direction = direction;
}

void Button::slotButtonPressed()
{
    if (this->_state == UNPRESSED)
    {
        this->_state = PRESSED;
        
        this->setStyleSheet(QString("background-color:") + BUTTON_COLOR_ACTIVE);
        this->update();

        if (_direction == DOWN)
            qDebug() << "Call from floor: " << this->_floor << ", direction: v.";
        else if (_direction == UP)
            qDebug() << "Call from floor: " << this->_floor << ", direction: ^.";
        else
            qDebug() << "Call from elevator: floor " << this->_floor;

        this->setDisabled(true);
        emit signalControllerTarget(true, this->_floor, this->_direction);
    }
}

void Button::slotButtonUnpressed()
{
    if (this->_state == PRESSED)
    {
        this->_state = UNPRESSED;

        this->setStyleSheet((QString("background-color:") + BUTTON_COLOR_INACTIVE));
        this->update();
        this->setDisabled(false);
    }
}
