#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include "base_manager.h"
#include "../draw/drawvisitor.h"
#include "../object/abstractobject.h"
#include "../object/camera/camera.h"

class DrawManager : public BaseManager
{
public:
    DrawManager();
    explicit DrawManager(std::shared_ptr<DrawVisitor> visitor);
    ~DrawManager() = default;

    void set_visitor(std::shared_ptr<DrawVisitor> visitor);
    void accept(std::shared_ptr<AbstractObject> obj);
    void set_camera(std::shared_ptr<Camera> camera);

protected:
    std::shared_ptr<DrawVisitor> visitor;
};

#endif // DRAW_MANAGER_H
