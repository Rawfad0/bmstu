#include "button.h"
#include "usings.h"

Button::Button(QWidget *parent): QPushButton(parent)
{
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(slotButtonPressed()));
    QObject::connect(this, SIGNAL(signalButtonRelease()), this, SLOT(slotButtonUnpressed())); // Выключается когда лифт приедет и издаст сигнал

    _state = UNPRESSED;
    _floor = 1;
    _position = NONE;
}

void Button::setFloor(int floor)
{
    _floor = floor;
}

void Button::setPosition(Button::position_t position)
{
    _position = position;
}

void Button::slotButtonPressed()
{
    if (this->_state == UNPRESSED)
    {
        this->_state = PRESSED;
        
        this->setStyleSheet(QString("background-color:") + BUTTON_COLOR_ACTIVE);
        this->update();

        if (_position == DOWN)
            qDebug() << "Call from floor: " << this->_floor << ", position: v.";
        else if (_position == UP)
            qDebug() << "Call from floor: " << this->_floor << ", position: ^.";
        else if (_position == CABIN1)
            qDebug() << "Call from cabin 1: floor " << this->_floor;
        else if (_position == CABIN2)
            qDebug() << "Call from cabin 2: floor " << this->_floor;
        
        this->setDisabled(true);
        if (_position == CABIN2)
            emit signalControllerTarget(2, true, this->_floor, this->_position);
        else
            emit signalControllerTarget(1, true, this->_floor, this->_position);
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
