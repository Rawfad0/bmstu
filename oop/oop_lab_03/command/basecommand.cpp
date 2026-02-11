#include "basecommand.h"

BaseCommand::BaseCommand() {}

void BaseCommand::SetFacade(const Facade& facade)
{
    this->proxy.draw = facade.DrawMngr;
    this->proxy.scene = facade.SceneMngr;
    this->proxy.loader = facade.LoadMngr;
    this->proxy.transform = facade.TransformMngr;
}
