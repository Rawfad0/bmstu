#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <memory>
#include <vector>
#include "button.h"

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
    void slotControllerWaiting(int);
    void slotControllerTargeting(int ,bool ,int = 0, Button::position_t = Button::position_t::NONE);
    void slotControllerMoving(int);
    void slotControllerStaying(int);

signals:
    void signalControllerMove(int);
    void signalControllerStay(int);
    void signalCabin1Move();
    void signalCabin1Stay();
    void signalCabin2Move();
    void signalCabin2Stay();
    void signalTargetsDone(int);


private:
    controller_state_t _state_1;
    controller_state_t _state_2;
    move_direction_t _direction_1;
    move_direction_t _direction_2;

    int _curFloor_1;
    int _curFloor_2;
    int _targetFloor_1;
    int _targetFloor_2;
    bool _set_target_1();
    bool _set_target_2();
    bool _set_target(int cabin_number);
    int _find_next_target_1();
    int _find_next_target_2();
    int _find_next_target(int cabin_number);
    void _setDirection(int cabin_number);
    void _setPressed(int floor, Button::position_t position);
    void _processNewTarget(int cabin_number, int floor, Button::position_t direction);
    void _processNextTarget(int cabin_number);
    void _processButtons(int cabin_number);
    void _emitCabinStay(int cabin_number);
    int _getTargetFloor(int cabin_number);
    int _getCurFloor(int cabin_number);
    Controller::move_direction_t _getDirection(int cabin_number);
    Controller::controller_state_t _getState(int cabin_number);
    void _setState(int cabin_number, Controller::controller_state_t);

    std::vector<bool> _is_pressed_1;
    std::vector<bool> _is_pressed_2;
    std::vector<bool> _is_pressed_down;
    std::vector<bool> _is_pressed_up;

    std::vector<std::shared_ptr<Button>> _buttons_floor_down;
    std::vector<std::shared_ptr<Button>> _buttons_floor_up;
    std::vector<std::shared_ptr<Button>> _buttons_elevator_1;
    std::vector<std::shared_ptr<Button>> _buttons_elevator_2;
    std::unique_ptr<QHBoxLayout> _layout;
};

#endif // CONTROLLER_H
