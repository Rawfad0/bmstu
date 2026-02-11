#include "draw_manager.h"

DrawManager::DrawManager() {}

DrawManager::DrawManager(std::shared_ptr<DrawVisitor> visitor): visitor(visitor)
{}


void DrawManager::set_visitor(std::shared_ptr<DrawVisitor> visitor)
{
    this->visitor = visitor;
}

void DrawManager::set_camera(std::shared_ptr<Camera> camera)
{
    this->visitor->set_camera(camera);
}

void DrawManager::accept(std::shared_ptr<AbstractObject> obj)
{
    obj->accept(this->visitor);
}
