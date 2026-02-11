#ifndef QTFACTORY_H
#define QTFACTORY_H

#include "abstractgraphicfactory.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class QtFactory : public AbstractGraphicFactory
{
public:
    QtFactory();
    explicit QtFactory(std::shared_ptr<QGraphicsScene> scene, QGraphicsView* view);
    ~QtFactory() = default;

    std::shared_ptr<AbstractDrawer> get_drawer() override;

protected:
    std::shared_ptr<QGraphicsScene> scene;
    QGraphicsView* view;
};

#endif // QTFACTORY_H
