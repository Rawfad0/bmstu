#ifndef FACADE_H
#define FACADE_H

#include "../manager/draw_manager.h"
#include "../manager/load_manager.h"
#include "../manager/scene_manager.h"
#include "../manager/transform_manager.h"

class BaseCommand;

class Facade
{
    friend class BaseCommand;
public:
    Facade();
    Facade(DrawManager d, LoadManager l, TransformManager t, SceneManager s);

    void execute(BaseCommand& command);

protected:
    std::shared_ptr<DrawManager> DrawMngr;
    std::shared_ptr<LoadManager> LoadMngr;
    std::shared_ptr<TransformManager> TransformMngr;
    std::shared_ptr<SceneManager> SceneMngr;
};

#endif // FACADE_H
