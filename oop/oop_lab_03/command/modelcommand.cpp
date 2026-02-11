#include "modelcommand.h"
#include "../manager/load_manager.h"
#include "../builder/carcasbuilder.h"
#include "../loader/filereader.h"
#include "../builder/carcasdirector.h"
#include "../modelvisitor/rotatevisitor.h"
#include "../modelvisitor/movevisitor.h"
#include "../modelvisitor/scalevisitor.h"
#include <iostream>

// template<class builder>
ModelLoad::ModelLoad(std::shared_ptr<AbstractObject>& obj, const std::string& filename, bool isbin, bool ismatrix)
    : obj(obj), filename(filename), isbin(isbin), ismatrix(ismatrix)
{
    this->method = &LoadManager::load<CarcasBuilder>;
}


void ModelLoad::execute()
{
    this->obj = ((*(this->proxy.loader)).*method)(this->filename, this->isbin, this->ismatrix);
}

// ModelLoadCarcas::ModelLoadCarcas(std::shared_ptr<AbstractObject>& obj, const std::string& filename, bool isbin)
//     : obj(obj), filename(filename), isbin(isbin)
// {
//     method = &LoadManager::load<CarcasBuilder>;
//     // if (!isbin)
//     // {
//     //     method = &LoadManager::load_from_file<CarcasBuilder>;
//     // }
//     // else
//     // {
//     //     method = &LoadManager::load_from_binary<CarcasBuilder>;
//     // }
// }


// void ModelLoadCarcas::execute()
// {
//     this->obj = ((*(this->proxy.loader)).*method)(this->filename);
// }

// ModelLoadMatrix::ModelLoadMatrix(std::shared_ptr<AbstractObject>& obj, const std::string& filename, bool isbin)
//     : obj(obj), filename(filename), isbin(isbin)
// {
//     method = &LoadManager::load<CarcasBuilder>;
//     // if (!isbin)
//     // {
//     //     method = &LoadManager::load_from_file<MatrixBuilder>;
//     // }
//     // else
//     // {
//     //     method = &LoadManager::load_from_binary<MatrixBuilder>;
//     // }
// }


// void ModelLoadMatrix::execute()
// {
//     this->obj = ((*(this->proxy.loader)).*method)(this->filename);
// }

// ModelLoadComposite::ModelLoadComposite(std::shared_ptr<AbstractObject>& obj, const std::string& filename)
//     : obj(obj), filename(filename)
// {
//     method = &LoadManager::load_composite_file;
// }


// void ModelLoadComposite::execute()
// {
//     this->obj = ((*(this->proxy.loader)).*method)(this->filename);
// }

ModelAddCarcas::ModelAddCarcas(std::shared_ptr<AbstractObject> obj)
    : obj(obj)
{
    this->method = &SceneManager::add_object;
}


void ModelAddCarcas::execute()
{
    ((*(this->proxy.scene)).*method)(this->obj);
}

ModelRemoveCommand::ModelRemoveCommand(size_t id)
    : id(id)
{
    method = &SceneManager::remove_object;
}

void ModelRemoveCommand::execute()
{
    ((*(this->proxy.scene)).*method)(this->id);
}

ModelGetCommand::ModelGetCommand(std::shared_ptr<AbstractObject>& object, size_t id): object(object), id(id)
{
    method = &SceneManager::get_object;
}

void ModelGetCommand::execute()
{
    this->object = ((*(this->proxy.scene)).*method)(this->id);
}

ModelsGetCommand::ModelsGetCommand(std::shared_ptr<AbstractObject>& object): object(object)
{
    this->method = &SceneManager::get_objects;
}

void ModelsGetCommand::execute()
{
    auto objects = ((*(this->proxy.scene)).*method)();
    this->object = std::make_shared<CompositeObject>();
    for (auto& obj : objects)
    {
        this->object->add(obj);
    }
}

ModelTransformCommand::ModelTransformCommand(std::shared_ptr<AbstractObject> obj): obj(obj)
{
    method = &TransformManager::transform;
}

void ModelTransformCommand::execute()
{
    ((*(this->proxy.transform)).*method)(this->obj);
}


MakeMoveCommand::MakeMoveCommand(double x, double y, double z): x(x), y(y), z(z)
{
    method = &TransformManager::set_visitor<MoveVisitor>;
}

void MakeMoveCommand::execute()
{
    ((*(this->proxy.transform)).*method)(this->x, this->y, this->z);
}

MakeRotateCommand::MakeRotateCommand(double x, double y, double z): x(x), y(y), z(z)
{
    method = &TransformManager::set_visitor<RotateVisitor>;
}

void MakeRotateCommand::execute()
{
    ((*(this->proxy.transform)).*method)(this->x, this->y, this->z);
}

MakeScaleCommand::MakeScaleCommand(double x, double y, double z): x(x), y(y), z(z)
{
    method = &TransformManager::set_visitor<ScaleVisitor>;
}

void MakeScaleCommand::execute()
{
    ((*(this->proxy.transform)).*method)(this->x, this->y, this->z);
}

MoveToCenterCommand::MoveToCenterCommand(std::shared_ptr<AbstractObject> Obj)
{
    this->x = -Obj->get_center().get_x();
    this->y = -Obj->get_center().get_y();
    this->z = -Obj->get_center().get_z();
    method = &TransformManager::set_visitor<MoveVisitor>;
}

void MoveToCenterCommand::execute()
{
    ((*(this->proxy.transform)).*method)(this->x, this->y, this->z);
}

MoveFromCenterCommand::MoveFromCenterCommand(std::shared_ptr<AbstractObject> Obj)
{
    this->x = Obj->get_center().get_x();
    this->y = Obj->get_center().get_y();
    this->z = Obj->get_center().get_z();
    method = &TransformManager::set_visitor<MoveVisitor>;
}

void MoveFromCenterCommand::execute()
{
    ((*(this->proxy.transform)).*method)(this->x, this->y, this->z);
}
