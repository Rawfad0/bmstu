#include "cameracommand.h"

CameraAddCommand::CameraAddCommand(std::shared_ptr<AbstractObject> camera): camera(camera)
{
    method = &SceneManager::add_camera;
}

void CameraAddCommand::execute()
{
    ((*(this->proxy.scene)).*method)(this->camera);
}


CameraRemoveCommand::CameraRemoveCommand(size_t id): id(id)
{
    method = &SceneManager::remove_camera;
}

void CameraRemoveCommand::execute()
{
    ((*(this->proxy.scene)).*method)(this->id);
}


CameraSetCommand::CameraSetCommand(size_t id): id(id)
{
    method = &SceneManager::set_camera;
}

void CameraSetCommand::execute()
{
    ((*(this->proxy.scene)).*method)(this->id);
}


CameraGetCommand::CameraGetCommand(std::shared_ptr<Camera>& camera): camera(camera)
{
    method = &SceneManager::get_main_camera;
}

void CameraGetCommand::execute()
{
    this->camera = ((*(this->proxy.scene)).*method)();
}


CameraTransformCommand::CameraTransformCommand(std::shared_ptr<Camera>& camera): camera(camera)
{
    method = &TransformManager::transform;
}

void CameraTransformCommand::execute()
{
    std::shared_ptr<AbstractObject> obj = this->camera;
    ((*(this->proxy.transform)).*method)(obj);
}
