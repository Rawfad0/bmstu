#include "qtfactory.h"
#include "qtdrawer.h"

QtFactory::QtFactory() {}

QtFactory::QtFactory(std::shared_ptr<QGraphicsScene> scene, QGraphicsView* view)
    : scene(scene), view(view)
{}

std::shared_ptr<AbstractDrawer> QtFactory::get_drawer()
{
    return std::make_shared<QTDrawer>(this->scene, this->view);
}
