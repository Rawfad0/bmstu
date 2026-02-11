#include "controller.h"

Controller::Controller(QWidget *parent): QWidget(parent)
{
    _state = WAITING;
    _direction = STAY;

    _curFloor = START_FLOOR;
    _targetFloor = START_FLOOR;

    this->_layout = std::make_unique<QHBoxLayout>();
    this->setLayout(this->_layout.get());

    QVBoxLayout *_layout_floor = new QVBoxLayout;
    QVBoxLayout *_layout_elevator = new QVBoxLayout;
    

    for (int i = 0; i < MAX_FLOOR; i++)
    {
        auto new_button_up = std::make_shared<Button>();
        new_button_up->setFloor(MAX_FLOOR - i);
        new_button_up->setDirection(Button::direction_t::UP);
        new_button_up->setText(QString::number(MAX_FLOOR - i));
        new_button_up->setStyleSheet(QString("background-color:") + BUTTON_COLOR_INACTIVE);
        this->_buttons_floor_up.insert(this->_buttons_floor_up.begin(), new_button_up);
        _layout_floor->addWidget(dynamic_cast<QPushButton *>(new_button_up.get()));
        _is_pressed_up.push_back(false);
        QObject::connect(new_button_up.get(), SIGNAL(signalControllerTarget(bool, int, Button::direction_t)), this, SLOT(slotControllerTargeting(bool, int, Button::direction_t)));

        auto new_button_down = std::make_shared<Button>();
        new_button_down->setFloor(MAX_FLOOR - i);
        new_button_down->setDirection(Button::direction_t::DOWN);
        new_button_down->setText(QString::number(MAX_FLOOR - i));
        new_button_down->setStyleSheet(QString("background-color:") + BUTTON_COLOR_INACTIVE);
        this->_buttons_floor_down.insert(this->_buttons_floor_down.begin(), new_button_down);
        _layout_floor->addWidget(dynamic_cast<QPushButton *>(new_button_down.get()));
        _is_pressed_down.push_back(false);
        QObject::connect(new_button_down.get(), SIGNAL(signalControllerTarget(bool, int, Button::direction_t)), this, SLOT(slotControllerTargeting(bool, int, Button::direction_t)));    
    }

    for (int i = 0; i < MAX_FLOOR; i++)
    {
        auto new_button = std::make_shared<Button>();
        new_button->setFloor(MAX_FLOOR - i);
        new_button->setDirection(Button::direction_t::NONE);
        new_button->setText(QString::number(MAX_FLOOR - i));
        new_button->setStyleSheet(QString("background-color:") + BUTTON_COLOR_INACTIVE);
        this->_buttons_elevator.insert(this->_buttons_elevator.begin(), new_button);
        _layout_elevator->addWidget(dynamic_cast<QPushButton *>(new_button.get()));
        _is_pressed.push_back(false);
        QObject::connect(new_button.get(), SIGNAL(signalControllerTarget(bool, int, Button::direction_t)), this, SLOT(slotControllerTargeting(bool, int, Button::direction_t)));
    }
    _layout->addLayout(_layout_floor);
    _layout->addLayout(_layout_elevator);

    QObject::connect(this,  SIGNAL(signalTargetsDone()),    this, SLOT(slotControllerWaiting()));
    QObject::connect(this,  SIGNAL(signalControllerMove()), this, SLOT(slotControllerMoving()));
    QObject::connect(this,  SIGNAL(signalControllerStay()), this, SLOT(slotControllerStaying()));
    
}

void Controller::_setDirection()
{
    if (_targetFloor < _curFloor)
        _direction = DOWN;
    else if (_targetFloor > _curFloor)
        _direction = UP;
    else
        _direction = STAY;
}

void Controller::_processNewTarget(int floor, Button::direction_t direction)
{
    if (direction == Button::direction_t::DOWN)
        this->_is_pressed_down[floor - 1] = true;
    else if (direction == Button::direction_t::UP)
        this->_is_pressed_up[floor - 1] = true;
    else
        this->_is_pressed[floor - 1] = true;
    _set_target();
    if (_targetFloor < _curFloor)
        _direction = DOWN;
    else if (_targetFloor > _curFloor)
        _direction = UP;
}

void Controller::_processNextTarget()
{
    this->_state = TARGETING;
    if (_set_target())
    {
        _setDirection();
        emit signalControllerMove();
    }
    else
    {
        qDebug() << "Done";
        _direction = STAY;
        emit signalTargetsDone();
    }
}

void Controller::slotControllerWaiting()
{
    if (_state == TARGETING)
        this->_state = WAITING;
}

void Controller::slotControllerTargeting(bool is_new_target, int floor, Button::direction_t direction)
{
    if (_state == WAITING)
    {
        if (is_new_target)
        {
            this->_state = TARGETING;
            _processNewTarget(floor, direction);
            emit signalControllerMove();
        }
    }
    else if (_state == STAYING)
    {
        if (is_new_target)
        {
            this->_state = TARGETING;
            _processNewTarget(floor, direction);
            emit signalControllerStay();    
        }
        else
            _processNextTarget();
    }
    else if (_state == MOVING)
    {
        if (is_new_target)
        {
            this->_state = TARGETING;
            _processNewTarget(floor, direction);
        }
    }
    else if (_state == TARGETING)
    {
        if (is_new_target)
            _processNewTarget(floor, direction);
    }
}

void Controller::slotControllerMoving()
{
    if (_state == TARGETING || _state == MOVING)
    {
        _state = MOVING;

        qDebug() << "Elevator reached floor: " << this->_curFloor;
        if (_curFloor == _targetFloor)
        {
            emit signalControllerStay();
        }
        else
        {
            if (_direction == UP)
            {
                _curFloor++;
                emit signalCabinMove();
            }
            else
            {
                _curFloor--;
                emit signalCabinMove();
            }
        }
    }
}

void Controller::slotControllerStaying()
{
    qDebug() << "Controller state STAYING: " << this->_curFloor;
    if (_state == TARGETING)
    {
        _state = STAYING;
        if (_targetFloor == _curFloor)
        {
            _processButtons();
            emit signalCabinStay();
        }
    }
    else if (_state == MOVING)
    {
        _state = STAYING;
        _processButtons();
        emit signalCabinStay();
    }
}

void Controller::_processButtons()
{
    int next_target = _find_next_target();
    // qDebug() << "NEXT TARGET: " << next_target;
    if ((_direction != DOWN && next_target < _curFloor) || (_direction != UP && next_target > _curFloor))
    {
        this->_is_pressed_up[_curFloor - 1] = false;
        emit this->_buttons_floor_up[_curFloor - 1]->signalButtonRelease();
        this->_is_pressed_down[_curFloor - 1] = false;
        emit this->_buttons_floor_down[_curFloor - 1]->signalButtonRelease();
    }
    else if (next_target < _curFloor)
    {
        this->_is_pressed_down[_curFloor - 1] = false;
        emit this->_buttons_floor_down[_curFloor - 1]->signalButtonRelease();
    }
    else if (next_target > _curFloor)
    {
        this->_is_pressed_up[_curFloor - 1] = false;
        emit this->_buttons_floor_up[_curFloor - 1]->signalButtonRelease();
    }
    else
    {
        this->_is_pressed_down[_curFloor - 1] = false;
        this->_is_pressed_up[_curFloor - 1] = false;
        emit this->_buttons_floor_down[_curFloor - 1]->signalButtonRelease();
        emit this->_buttons_floor_up[_curFloor - 1]->signalButtonRelease();
    }
    this->_is_pressed[_curFloor - 1] = false;
    emit this->_buttons_elevator[_curFloor - 1]->signalButtonRelease();
}

bool Controller::_set_target()
{
    if (_direction == UP)
    {
        for (int i = _curFloor - 1; i < MAX_FLOOR; i++)
            if (_is_pressed[i] || _is_pressed_up[i])
            {
                _targetFloor = i + 1;
                return true;
            }
        for (int i = MAX_FLOOR - 1; i >= START_FLOOR - 1; i--)
            if (_is_pressed[i] || _is_pressed_down[i])
            {
                _targetFloor = i + 1;
                return true;
            }
        for (int i = START_FLOOR - 1; i < _curFloor - 1; i++)
            if (_is_pressed[i] || _is_pressed_up[i])
            {
                _targetFloor = i + 1;
                return true;
            }
    }
    else
    {
        for (int i = _curFloor - 1; i >= START_FLOOR - 1; i--)
            if (_is_pressed[i] || _is_pressed_down[i])
            {
                _targetFloor = i + 1;
                return true;
            }
        for (int i = START_FLOOR - 1; i < MAX_FLOOR; i++)
            if (_is_pressed[i] || _is_pressed_up[i])
            {
                _targetFloor = i + 1;
                return true;
            }
        for (int i = MAX_FLOOR - 1; i < _curFloor - 1; i--)
            if (_is_pressed[i] || _is_pressed_down[i])
            {
                _targetFloor = i + 1;
                return true;
            }
    }
    return false;
}

int Controller::_find_next_target()
{
    if (_direction == UP)
    {
        for (int i = _curFloor; i < MAX_FLOOR; i++)
            if (_is_pressed[i] || _is_pressed_up[i])
                return i + 1;
        for (int i = MAX_FLOOR - 1; i >= START_FLOOR - 1; i--)
            if (i != _curFloor - 1 && (_is_pressed[i] || _is_pressed_down[i]))
                return i + 1;
        for (int i = START_FLOOR - 1; i < _curFloor - 1; i++)
            if (_is_pressed[i] || _is_pressed_up[i])
                return i + 1;
    }
    else
    {
        for (int i = _curFloor; i >= START_FLOOR - 1; i--)
            if (i != _curFloor - 1 && (_is_pressed[i] || _is_pressed_down[i]))
                return i + 1;
        for (int i = START_FLOOR - 1; i < MAX_FLOOR; i++)
            if (_is_pressed[i] || _is_pressed_up[i])
                return i + 1;
        for (int i = MAX_FLOOR - 1; i < _curFloor - 1; i--)
            if (_is_pressed[i] || _is_pressed_down[i])
                return i + 1;
    }
    return _curFloor;
}
