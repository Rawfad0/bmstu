#include "abstractobject.h"
#include "carcas/carcas.h"

std::size_t AbstractObject::nextid = 0;

CompositeObject::CompositeObject(std::shared_ptr<AbstractObject> &element)
{
    this->elements.push_back(element);
}

CompositeObject::CompositeObject(std::vector<std::shared_ptr<AbstractObject>>& vector)
{
    this->elements = vector;
}

Point& CompositeObject::get_center() {
    return this->center;
}

bool CompositeObject::add(const std::shared_ptr<AbstractObject> &element)
{
    this->elements.push_back(element);
    this->center.set_x(0);
    this->center.set_y(0);
    this->center.set_z(0);
    for (auto &e : this->elements)
    {
        Point c = e->get_center();
        auto x = c.get_x();
        auto y = c.get_y();
        auto z = c.get_z();
        this->center.set_x(x + this->center.get_x());
        this->center.set_y(y + this->center.get_y());
        this->center.set_z(z + this->center.get_z());
    }
    if (this->elements.size())
    {
        this->center.set_x(this->center.get_x() / this->elements.size());
        this->center.set_y(this->center.get_y() / this->elements.size());
        this->center.set_z(this->center.get_z() / this->elements.size());
    }
    return true;
}

bool CompositeObject::remove(const Iterator &iter)
{
    this->elements.erase(iter);

    return true;
}

bool CompositeObject::IsDrawable()
{
    return false;
}

bool CompositeObject::IsComposite()
{
    return true;
}

Iterator CompositeObject::begin()
{
    return this->elements.begin();
}

Iterator CompositeObject::end()
{
    return this->elements.end();
}

void CompositeObject::accept(std::shared_ptr<AbstractVisitor> visitor)
{
    visitor->visit(*this);
//    for (auto &element : this->elements)
//    {
//        element->accept(visitor);
//    }
}

std::vector<std::shared_ptr<AbstractObject>>& CompositeObject::get()
{
    return this->elements;
}
