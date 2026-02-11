#include "rotatevisitor.h"
#include "../object/carcas/carcas.h"
#include "../object/camera/camera.h"
#include "../object/model.h"
#include <iostream>

RotateVisitor::RotateVisitor(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void RotateVisitor::visit(Model& obj)
{
    std::vector<Point>& points = obj.model->get_points();

    for (auto& elem : points)
    {
        elem.rotate(this->x, this->y, this->z);
    }
    
    // obj.get_center().rotate(this->x, this->y, this->z);
    return;
}

void RotateVisitor::visit(Camera& obj)
{
    obj.up.rotate(this->x, this->y, this->z);
    obj.forward.rotate(this->x, this->y, this->z);
    obj.right.rotate(this->x, this->y, this->z);
}

void RotateVisitor::visit(CompositeObject& obj)
{
    for (auto &elem : obj)
        elem->accept(std::make_shared<RotateVisitor>(*this));
    obj.get_center().rotate(this->x, this->y, this->z);
}
