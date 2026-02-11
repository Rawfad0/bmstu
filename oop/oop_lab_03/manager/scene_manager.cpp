#include "scene_manager.h"
#include <stdexcept>

SceneManager::SceneManager() {}

SceneManager::SceneManager(std::shared_ptr<Scene> scene)
    : scene(scene)
{}


void SceneManager::set_scene(std::shared_ptr<Scene> scene)
{
    this->scene = scene;
}
std::shared_ptr<Scene> SceneManager::get_scene()
{
    return this->scene;
}

void SceneManager::set_camera(std::shared_ptr<Camera> camera)
{
    this->camera = camera;
}

void SceneManager::add_object(std::shared_ptr<AbstractObject> object)
{
    this->scene->add_object(object);
}

std::vector<std::shared_ptr<AbstractObject>> SceneManager::get_objects()
{
    std::vector<std::shared_ptr<AbstractObject>> objects;
    for (auto it = this->scene->begin(); it != this->scene->end(); ++it)
    {
        objects.push_back(*it);
    }
    return objects;
}


void SceneManager::add_camera(std::shared_ptr<AbstractObject> camera)
{
    this->scene->add_camera(camera);
}

std::shared_ptr<AbstractObject> SceneManager::get_object(std::size_t id)
{
    std::shared_ptr<AbstractObject> obj = nullptr;
    for (auto it = this->scene->begin(); obj == nullptr && it != this->scene->end(); ++it)
    {
        if ((*it)->get_id() == id)
        {
            obj = *it;
        }
    }
    return obj;
}

void SceneManager::remove_object(std::size_t id)
{
    for (auto it = this->scene->cbegin(); it!= this->scene->cend(); ++it)
    {
        if ((*it)->get_id() == id)
        {
            this->scene->remove_object(it);
            return;
        }
    }
}

std::vector<std::shared_ptr<AbstractObject>> SceneManager::get_cameras()
{
    std::vector<std::shared_ptr<AbstractObject>> cameras;
    for (auto it = this->scene->beginCamera(); it!= this->scene->endCamera(); ++it)
    {
        cameras.push_back(**it);
    }
    return cameras;
}

std::shared_ptr<Camera> SceneManager::get_camera(std::size_t id)
{
    for (auto it = this->scene->beginCamera(); it!= this->scene->endCamera(); ++it)
    {
        if ((**it)->get_id() == id)
        {
            auto obj = std::dynamic_pointer_cast<Camera>(**it);
            if (obj == nullptr)
            {
                throw std::runtime_error("Object is not a camera");
            }
            return obj;
        }
    }
    return nullptr;
}
void SceneManager::remove_camera(std::size_t id)
{
    for (auto it = this->scene->beginCamera(); it!= this->scene->endCamera(); ++it)
    {
        if ((**it)->get_id() == id) {
            this->scene->remove_camera(it);
            return;
        }
    }
}

void SceneManager::set_camera(std::size_t id)
{
    this->camera = get_camera(id);
}

void SceneManager::clear_scene()
{
    this->scene->cameras.clear();
    this->scene->objects.clear();
}

std::shared_ptr<Camera> SceneManager::get_main_camera()
{
    return this->camera;
}

std::vector<std::size_t> SceneManager::get_object_ids()
{
    std::vector<std::size_t> ids;
    for (auto it = this->scene->begin(); it!= this->scene->end(); ++it)
    {
        ids.push_back((*it)->get_id());
    }
    return ids;
}

std::vector<std::size_t> SceneManager::get_camera_ids()
{
    std::vector<std::size_t> ids;
    for (auto it = this->scene->beginCamera(); it!= this->scene->endCamera(); ++it)
    {
        ids.push_back((**it)->get_id());
    }
    return ids;
}


void SceneManager::make_composite(std::vector<size_t> ids)
{
    std::vector<std::shared_ptr<AbstractObject>> objects;
    for (auto it = ids.begin(); it!= ids.end(); ++it) {
        objects.push_back(get_object(*it));
    }
    this->scene->add_composite(objects);
}


// std::shared_ptr<Scene> SceneManager::get_scene()
// {
//     return this->scene;
// }

// void SceneManager::set_scene(std::shared_ptr<Scene> scene)
// {
//     this->scene = scene;
// }

// std::shared_ptr<Camera>& SceneManager::get_camera()
// {
//     return this->camera;
// }

// void SceneManager::set_camera(std::shared_ptr<Camera> camera)
// {
//     this->camera = camera;
// }

// void SceneManager::set_camera(int id)
// {
//     std::shared_ptr<Camera> obj = this->get_scene()->get_cameras().at(id);
//     this->set_camera(obj);
// }

// void SceneManager::add_camera(std::shared_ptr<Camera> camera)
// {
//     this->scene->add_camera(camera);
// }

// void SceneManager::add_object(std::shared_ptr<AbstractObject>& object)
// {
//     this->scene->add_model(object);
// }

// std::vector<std::shared_ptr<AbstractObject>>& SceneManager::get_objects()
// {
//     return this->scene->get_models();
// }

// void SceneManager::remove_object(int id)
// {
//     this->scene->remove_model(id);
// }

// void SceneManager::remove_camera(int id)
// {
//     this->scene->remove_camera(id);
// }

// std::shared_ptr<AbstractObject> SceneManager::get_object(int id)
// {
//     return this->scene->get_object(id);
// }
