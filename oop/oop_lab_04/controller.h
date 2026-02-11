#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <memory>
#include <vector>
#include "button.h"
#include "usings.h"

#define START_FLOOR 1
#define MAX_FLOOR 9

class Controller: public QWidget
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = nullptr);
    ~Controller() override = default;
    enum controller_state_t { WAITING, TARGETING, MOVING, STAYING };
    enum move_direction_t { DOWN, STAY, UP };

public slots:
    void slotControllerWaiting();
    void slotControllerTargeting(bool ,int = 0,Button::direction_t = Button::direction_t::NONE);
    void slotControllerMoving();
    void slotControllerStaying();

signals:
    void signalControllerMove();
    void signalControllerStay();
    void signalCabinMove();
    void signalCabinStay();
    void signalTargetsDone();


private:
    controller_state_t _state;
    move_direction_t _direction;

    int _curFloor;
    int _targetFloor;
    bool _set_target();
    int _find_next_target();
    void _setDirection();
    void _processNewTarget(int floor, Button::direction_t direction);
    void _processNextTarget();
    void _processButtons();
    
    std::vector<bool> _is_pressed;
    std::vector<bool> _is_pressed_down;
    std::vector<bool> _is_pressed_up;

    std::vector<std::shared_ptr<Button>> _buttons_floor_down;
    std::vector<std::shared_ptr<Button>> _buttons_floor_up;
    std::vector<std::shared_ptr<Button>> _buttons_elevator;
    std::unique_ptr<QHBoxLayout> _layout;
};

#endif // CONTROLLER_H
