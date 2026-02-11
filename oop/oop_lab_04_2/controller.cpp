#include "controller.h"
#include "usings.h"


Controller::Controller(QWidget *parent): QWidget(parent)
{
    _state_1 = WAITING;
    _state_2 = WAITING;
    _direction_1 = STAY;
    _direction_2 = STAY;

    _curFloor_1 = START_FLOOR;
    _curFloor_2 = START_FLOOR;
    _targetFloor_1 = START_FLOOR;
    _targetFloor_2 = START_FLOOR;

    this->_layout = std::make_unique<QHBoxLayout>();
    this->setLayout(this->_layout.get());

    QVBoxLayout *_layout_floor = new QVBoxLayout;
    QVBoxLayout *_layout_elevator_1 = new QVBoxLayout;
    QVBoxLayout *_layout_elevator_2 = new QVBoxLayout;

    for (int i = 0; i < MAX_FLOOR; i++)
    {
        auto new_button_up = std::make_shared<Button>();
        new_button_up->setFloor(MAX_FLOOR - i);
        new_button_up->setPosition(Button::position_t::UP);
        new_button_up->setText(QString::number(MAX_FLOOR - i));
        new_button_up->setStyleSheet(QString("background-color:") + BUTTON_COLOR_INACTIVE);
        this->_buttons_floor_up.insert(this->_buttons_floor_up.begin(), new_button_up);
        _layout_floor->addWidget(dynamic_cast<QPushButton *>(new_button_up.get()));
        _is_pressed_up.push_back(false);
        QObject::connect(new_button_up.get(), SIGNAL(signalControllerTarget(int, bool, int, Button::position_t)), this, SLOT(slotControllerTargeting(int, bool, int, Button::position_t)));

        auto new_button_down = std::make_shared<Button>();
        new_button_down->setFloor(MAX_FLOOR - i);
        new_button_down->setPosition(Button::position_t::DOWN);
        new_button_down->setText(QString::number(MAX_FLOOR - i));
        new_button_down->setStyleSheet(QString("background-color:") + BUTTON_COLOR_INACTIVE);
        this->_buttons_floor_down.insert(this->_buttons_floor_down.begin(), new_button_down);
        _layout_floor->addWidget(dynamic_cast<QPushButton *>(new_button_down.get()));
        _is_pressed_down.push_back(false);
        QObject::connect(new_button_down.get(), SIGNAL(signalControllerTarget(int, bool, int, Button::position_t)), this, SLOT(slotControllerTargeting(int, bool, int, Button::position_t)));
    }

    for (int i = 0; i < MAX_FLOOR; i++)
    {
        auto new_button = std::make_shared<Button>();
        new_button->setFloor(MAX_FLOOR - i);
        new_button->setPosition(Button::position_t::CABIN1);
        new_button->setText(QString::number(MAX_FLOOR - i));
        new_button->setStyleSheet(QString("background-color:") + BUTTON_COLOR_INACTIVE);
        this->_buttons_elevator_1.insert(this->_buttons_elevator_1.begin(), new_button);
        _layout_elevator_1->addWidget(dynamic_cast<QPushButton *>(new_button.get()));
        _is_pressed_1.push_back(false);
        QObject::connect(new_button.get(), SIGNAL(signalControllerTarget(int, bool, int, Button::position_t)), this, SLOT(slotControllerTargeting(int, bool, int, Button::position_t)));
    }
    for (int i = 0; i < MAX_FLOOR; i++)
    {
        auto new_button = std::make_shared<Button>();
        new_button->setFloor(MAX_FLOOR - i);
        new_button->setPosition(Button::position_t::CABIN2);
        new_button->setText(QString::number(MAX_FLOOR - i));
        new_button->setStyleSheet(QString("background-color:") + BUTTON_COLOR_INACTIVE);
        this->_buttons_elevator_2.insert(this->_buttons_elevator_2.begin(), new_button);
        _layout_elevator_2->addWidget(dynamic_cast<QPushButton *>(new_button.get()));
        _is_pressed_2.push_back(false);
        QObject::connect(new_button.get(), SIGNAL(signalControllerTarget(int, bool, int, Button::position_t)), this, SLOT(slotControllerTargeting(int, bool, int, Button::position_t)));
    }
    _layout->addLayout(_layout_floor);
    _layout->addLayout(_layout_elevator_1);
    _layout->addLayout(_layout_elevator_2);

    QObject::connect(this,  SIGNAL(signalTargetsDone(int)),    this, SLOT(slotControllerWaiting(int)));
    QObject::connect(this,  SIGNAL(signalControllerMove(int)), this, SLOT(slotControllerMoving(int)));
    QObject::connect(this,  SIGNAL(signalControllerStay(int)), this, SLOT(slotControllerStaying(int)));
}

void Controller::_setDirection(int cabin_number)
{
    if (cabin_number == 1)
    {
        if (_targetFloor_1 < _curFloor_1)
            _direction_1 = DOWN;
        else if (_targetFloor_1 > _curFloor_1)
            _direction_1 = UP;
        else
            _direction_1 = STAY;
    }
    else if (cabin_number == 2)
    {
        if (_targetFloor_2 < _curFloor_2)
            _direction_2 = DOWN;
        else if (_targetFloor_2 > _curFloor_2)
            _direction_2 = UP;
        else
            _direction_2 = STAY;
    }
}

void Controller::_setPressed(int floor, Button::position_t position)
{
    if (position == Button::position_t::DOWN)
        this->_is_pressed_down[floor - 1] = true;
    else if (position == Button::position_t::UP)
        this->_is_pressed_up[floor - 1] = true;
    else if (position == Button::position_t::CABIN1)
        this->_is_pressed_1[floor - 1] = true;
    else if (position == Button::position_t::CABIN2)
        this->_is_pressed_2[floor - 1] = true;
}

void Controller::_processNewTarget(int cabin_number, int floor, Button::position_t position)
{
    _setPressed(floor, position);
    _set_target(cabin_number);
    if (cabin_number == 1)
    {
        if (_targetFloor_1 < _curFloor_1)
            _direction_1 = DOWN;
        else if (_targetFloor_1 > _curFloor_1)
            _direction_1 = UP;
    }
    else if (cabin_number == 2)
    {
        if (_targetFloor_2 < _curFloor_2)
            _direction_2 = DOWN;
        else if (_targetFloor_1 > _curFloor_2)
            _direction_2 = UP;
    }
}

void Controller::_processNextTarget(int cabin_number)
{
    _setState(cabin_number, TARGETING);
    if (_set_target(cabin_number))
    {
        _setDirection(cabin_number);
        emit signalControllerMove(cabin_number);
    }
    else
    {
        qDebug() << "Done" << cabin_number;
        if (cabin_number == 1)
            _direction_1 = STAY;
        else if (cabin_number == 2)
            _direction_2 = STAY;
        emit signalTargetsDone(cabin_number);
    }
}

void Controller::slotControllerWaiting(int cabin_number)
{
    if (_getState(cabin_number) == TARGETING)
        _setState(cabin_number, WAITING);
}


void Controller::slotControllerTargeting(int cabin_number, bool is_new_target, int floor, Button::position_t position)
{
    if (_getState(cabin_number) == WAITING)
    {
        if (is_new_target)
        {
            _setState(cabin_number, TARGETING);
            _processNewTarget(cabin_number, floor, position);
            emit signalControllerMove(cabin_number);
        }
        // else
        //     _processNextTarget(cabin_number);
    }
    else if (_getState(cabin_number) == STAYING)
    {
        if (is_new_target)
        {
            _setState(cabin_number, TARGETING);
            _processNewTarget(cabin_number, floor, position);
            emit signalControllerStay(cabin_number);    
        }
        else
            _processNextTarget(cabin_number);
    }
    else if (_getState(cabin_number) == MOVING)
    {
        if (is_new_target)
        {
            _setState(cabin_number, TARGETING);
            _processNewTarget(cabin_number, floor, position);
        }
        // else
        //     _processNextTarget(cabin_number);
    }
    else if (_getState(cabin_number) == TARGETING)
    {
        if (is_new_target)
            _processNewTarget(cabin_number, floor, position);
        // else
        //     _processNextTarget(cabin_number);
    }
}

// void Controller::slotControllerTargeting(int cabin_number, bool is_new_target, int floor, Button::position_t position)
// {
//     if (is_new_target)
//     {
//         if (position == Button::position_t::DOWN)
//             this->_is_pressed_down[floor - 1] = true;
//         else if (position == Button::position_t::UP)
//             this->_is_pressed_up[floor - 1] = true;
//         else if (position == Button::position_t::CABIN1)
//             this->_is_pressed_1[floor - 1] = true;
//         else if (position == Button::position_t::CABIN2)
//             this->_is_pressed_2[floor - 1] = true;
//         if (_set_target_1())
//         {
//             if (_targetFloor_1 < _curFloor_1)
//                 _direction_1 = DOWN;
//             else if (_targetFloor_1 > _curFloor_1)
//                 _direction_1 = UP;

//             if (_getState(cabin_number) == WAITING)
//                 _setState(cabin_number, TARGETING, emit signalControllerMove(1);
//             else if (_getState(cabin_number) == MOVING && _targetFloor_1 == _curFloor_1)
//                 _setState(cabin_number, TARGETING, emit signalControllerMove(1);
//         }
//         else if (_set_target_2())
//         {
//             if (_targetFloor_2 < _curFloor_2)
//                 _direction_2 = DOWN;
//             else if (_targetFloor_2 > _curFloor_2)
//                 _direction_2 = UP;

//             if (_getState(cabin_number) == WAITING)
//                 _setState(cabin_number, TARGETING, emit signalControllerMove(2);
//             else if (_getState(cabin_number) == MOVING && _targetFloor_2 == _curFloor_2)
//                 _setState(cabin_number, TARGETING, emit signalControllerMove(2);
//         }
//     }
//     else
//     {
//         _setState(cabin_number, TARGETING;
//         if ((cabin_number == 1 && _set_target_1()) || (cabin_number == 2 && _set_target_2()))
//         {
//             if (_targetFloor_1 < _curFloor_1)
//                 _direction_1 = DOWN;
//             else if (_targetFloor_1 > _curFloor_1)
//                 _direction_1 = UP;
//             else
//                 _direction_1 = STAY;
//             if (_targetFloor_2 < _curFloor_2)
//                 _direction_2 = DOWN;
//             else if (_targetFloor_2 > _curFloor_2)
//                 _direction_2 = UP;
//             else
//                 _direction_2 = STAY;
//             emit signalControllerMove(cabin_number);
//         }
//         else
//         {
//             qDebug() << "Done";
//             _direction_1 = STAY;
//             _direction_2 = STAY;
//             emit signalTargetsDone();
//         }
//     }
// }

void Controller::slotControllerMoving(int cabin_number)
{
    if (_getState(cabin_number) == TARGETING || _getState(cabin_number) == MOVING)
    {
        _setState(cabin_number, MOVING);
        
        int _curFloor = _getCurFloor(cabin_number);
        int _targetFloor = _getTargetFloor(cabin_number);
        qDebug() << "Elevator" << cabin_number << "reached floor: " << _curFloor;
        qDebug() << "c: " << _curFloor << "t: " << _targetFloor;

        if (_curFloor == _targetFloor)
            emit signalControllerStay(cabin_number);
        else
        {
            if (cabin_number == 1)
                if (_direction_1 == UP)
                {
                    _curFloor_1++;
                    emit signalCabin1Move();
                }
                else
                {
                    _curFloor_1--;
                    emit signalCabin1Move();
                }
            else if (cabin_number == 2)
                if (_direction_2 == UP)
                {
                    _curFloor_2++;
                    emit signalCabin2Move();
                }
                else
                {
                    _curFloor_2--;
                    emit signalCabin2Move();
                }
            else
                return;
        }
    }
}

void Controller::slotControllerStaying(int cabin_number)
{
    qDebug() << "Controller state STAYING: " << _getCurFloor(cabin_number);
    if (_getState(cabin_number) == TARGETING)
    {
        _setState(cabin_number, STAYING);
        if (_getTargetFloor(cabin_number) == _getCurFloor(cabin_number))
        {
            _processButtons(cabin_number);
            _emitCabinStay(cabin_number);
        }
    }
    else if (_getState(cabin_number) == MOVING)
    {
        _setState(cabin_number, STAYING);
        _processButtons(cabin_number);
        _emitCabinStay(cabin_number);
    }
}

void Controller::_emitCabinStay(int cabin_number)
{
    if (cabin_number == 1)
        emit signalCabin1Stay();
    else if (cabin_number == 2)
        emit signalCabin2Stay();
}

int Controller::_getTargetFloor(int cabin_number)
{
    if (cabin_number == 1)
        return _targetFloor_1;
    else if (cabin_number == 2)
        return _targetFloor_2;
    return 0;
}

int Controller::_getCurFloor(int cabin_number)
{
    if (cabin_number == 1)
        return _curFloor_1;
    else if (cabin_number == 2)
        return _curFloor_2;
    return 0;
}

Controller::move_direction_t Controller::_getDirection(int cabin_number)
{
    if (cabin_number == 1)
        return _direction_1;
    else
        return _direction_2;
}

Controller::controller_state_t Controller::_getState(int cabin_number)
{
    if (cabin_number == 1)
        return _state_1;
    else
        return _state_2;
}

void Controller::_setState(int cabin_number, Controller::controller_state_t state)
{
    if (cabin_number == 1)
        _state_1 = state;
    else
        _state_2 = state;
}

void Controller::_processButtons(int cabin_number)
{
    int _curFloor = _getCurFloor(cabin_number);
    move_direction_t _direction = _getDirection(cabin_number);
    int next_target = 0;
    if (cabin_number == 1)
        next_target = _find_next_target_1();
    else if (cabin_number == 2)
        next_target = _find_next_target_2();
    
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
    if (cabin_number == 1)
    {
        this->_is_pressed_1[_curFloor - 1] = false;
        emit this->_buttons_elevator_1[_curFloor - 1]->signalButtonRelease();
    }
    else if (cabin_number == 2)
    {
        this->_is_pressed_2[_curFloor - 1] = false;
        emit this->_buttons_elevator_2[_curFloor - 1]->signalButtonRelease();
    }
}

bool Controller::_set_target(int cabin_number)
{
    if (cabin_number == 1)
        return _set_target_1();
    else if (cabin_number == 2)    
        return _set_target_2();
    else
        return false;
}

bool Controller::_set_target_1()
{
    if (_direction_1 == UP)
    {
        for (int i = _curFloor_1 - 1; i < MAX_FLOOR; i++)
            if (_is_pressed_1[i] || _is_pressed_up[i])
            {
                _targetFloor_1 = i + 1;
                return true;
            }
        for (int i = MAX_FLOOR - 1; i >= START_FLOOR - 1; i--)
            if (_is_pressed_1[i] || _is_pressed_down[i])
            {
                _targetFloor_1 = i + 1;
                return true;
            }
        for (int i = START_FLOOR - 1; i < _curFloor_1 - 1; i++)
            if (_is_pressed_1[i] || _is_pressed_up[i])
            {
                _targetFloor_1 = i + 1;
                return true;
            }
    }
    else
    {
        for (int i = _curFloor_1 - 1; i >= START_FLOOR - 1; i--)
            if (_is_pressed_1[i] || _is_pressed_down[i])
            {
                _targetFloor_1 = i + 1;
                return true;
            }
        for (int i = START_FLOOR - 1; i < MAX_FLOOR; i++)
            if (_is_pressed_1[i] || _is_pressed_up[i])
            {
                _targetFloor_1 = i + 1;
                return true;
            }
        for (int i = MAX_FLOOR - 1; i < _curFloor_1 - 1; i--)
            if (_is_pressed_1[i] || _is_pressed_down[i])
            {
                _targetFloor_1 = i + 1;
                return true;
            }
    }
    return false;
}

bool Controller::_set_target_2()
{
    for (int i = START_FLOOR - 1; i < MAX_FLOOR; i++)
        if (_is_pressed_2[i])
        {
            _targetFloor_2 = i + 1;
            return true;
        }
    return false;
}

int Controller::_find_next_target(int cabin_number)
{
    if (cabin_number == 1)
        return _find_next_target_1();
    else if (cabin_number == 2)    
        return _find_next_target_2();
    else
        return false;
}

int Controller::_find_next_target_1()
{
    if (_direction_1 == UP)
    {
        for (int i = _curFloor_1; i < MAX_FLOOR; i++)
            if (_is_pressed_1[i] || _is_pressed_up[i])
                return i + 1;
        for (int i = MAX_FLOOR - 1; i >= START_FLOOR - 1; i--)
            if (i != _curFloor_1 - 1 && (_is_pressed_1[i] || _is_pressed_down[i]))
                return i + 1;
        for (int i = START_FLOOR - 1; i < _curFloor_1 - 1; i++)
            if (_is_pressed_1[i] || _is_pressed_up[i])
                return i + 1;
    }
    else
    {
        for (int i = _curFloor_1; i >= START_FLOOR - 1; i--)
            if (i != _curFloor_1 - 1 && (_is_pressed_1[i] || _is_pressed_down[i]))
                return i + 1;
        for (int i = START_FLOOR - 1; i < MAX_FLOOR; i++)
            if (_is_pressed_1[i] || _is_pressed_up[i])
                return i + 1;
        for (int i = MAX_FLOOR - 1; i < _curFloor_1 - 1; i--)
            if (_is_pressed_1[i] || _is_pressed_down[i])
                return i + 1;
    }
    return _curFloor_1;
}

int Controller::_find_next_target_2()
{
    for (int i = START_FLOOR - 1; i < MAX_FLOOR; i++)
        if (_is_pressed_2[i])
            return i + 1;
    return _curFloor_2;
}
