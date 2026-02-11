#include "facade.h"
#include "../command/basecommand.h"

Facade::Facade() {}

Facade::Facade(DrawManager d, LoadManager l, TransformManager t, SceneManager s):
    DrawMngr(std::make_shared<DrawManager>(d)),
    LoadMngr(std::make_shared<LoadManager>(l)),
    TransformMngr(std::make_shared<TransformManager>(t)),
    SceneMngr(std::make_shared<SceneManager>(s))
{}

void Facade::execute(BaseCommand& command)
{
    command.SetFacade(*this);
    command.execute();
}
