#include "transform_manager.h"

TransformManager::TransformManager() noexcept {}

TransformManager::TransformManager(const std::shared_ptr<ModelVisitor> visitor) noexcept: visitor(visitor) {}

void TransformManager::transform(std::shared_ptr<AbstractObject>& object) const
{
    object->accept(this->visitor);
}
