#include "drawall.h"
#include "../object/abstractobject.h"
#include "../object/camera/camera.h"
#include "../object/carcas/carcas.h"
#include "../object/model.h"


DrawAll::DrawAll() {}

DrawAll::DrawAll(std::shared_ptr<AbstractGraphicFactory> factory, std::shared_ptr<Camera>  camera)
{
    this->factory = factory;
    this->camera = camera;
}

DrawAll::DrawAll(const DrawAll& visitor)
{
    this->camera = visitor.camera;
    this->factory = visitor.factory;
}


void DrawAll::visit(Model& carcas)
{
    auto points = carcas.model->get_points();
    auto links = carcas.model->get_links();

    auto drawer = this->factory->get_drawer();

    for (auto& link : links)
    {
        Point left = this->get_proection(points[link.get_left()]);
        Point right = this->get_proection(points[link.get_right()]);


        if (left.get_z() < -1 || right.get_z() < -1)
            continue;
        if (left.get_z() > 1 || right.get_z() > 1)
            continue;
        else if (left.get_z() > 0 && right.get_z() > 0)
            drawer->draw_line(left, right);
    }
}

void DrawAll::visit(Camera& camera)
{
    return;
}

void DrawAll::visit(CompositeObject& obj)
{
//    obj.accept(std::make_shared<DrawAll>(*this));
    for (auto &elem : obj)
        elem->accept(std::make_shared<DrawAll>(*this));
}
