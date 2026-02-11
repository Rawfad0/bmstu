#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include "base_manager.h"
#include "../modelvisitor/modelvisitor.h"
#include "../builder/directorcreator.h"
#include "../object/abstractobject.h"
#include <memory>

template<typename Type>
concept ConstructibleDouble = std::is_constructible_v<Type, double, double, double>;

class TransformManager : public BaseManager
{
public:
    TransformManager() noexcept;
    explicit TransformManager(const std::shared_ptr<ModelVisitor> visitor) noexcept;

    template<typename visitor>
        requires Derivative<visitor, ModelVisitor> && NotAbstract<visitor> && ConstructibleDouble<visitor>
    void set_visitor(double x, double y, double z) { this->visitor = std::make_shared<visitor>(x, y, z); }

    void transform(std::shared_ptr<AbstractObject>& object) const;

protected:
    std::shared_ptr<ModelVisitor> visitor;
};

#endif // TRANSFORM_MANAGER_H
