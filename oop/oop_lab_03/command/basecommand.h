#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "../facade/facade.h"

struct FacadeProxy
{
    std::shared_ptr<DrawManager> draw;
    std::shared_ptr<SceneManager> scene;
    std::shared_ptr<TransformManager> transform;
    std::shared_ptr<LoadManager> loader;
};


class BaseCommand
{
public:
    BaseCommand();
    virtual ~BaseCommand() = default;

    virtual void execute() = 0;

    void SetFacade(const Facade& facade);

protected:
    FacadeProxy proxy;
};


#endif // BASECOMMAND_H
