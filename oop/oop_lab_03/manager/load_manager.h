#ifndef LOAD_MANAGER_H
#define LOAD_MANAGER_H

#include "base_manager.h"
#include "../object/abstractobject.h"
#include "../loader/loader.h"
#include "../builder/carcasdirector.h"
#include "../loader/filereader.h"
#include "../loader/binaryreader.h"
#include "../builder/carcasbuilder.h"
#include "../builder/matrixbuilder.h"
#include "../solution/load_solution.h"
#include <fstream>
#include <iostream>


class LoadManager : public BaseManager
{
public:
    LoadManager();
    ~LoadManager() = default;

    template<typename builder>
        requires std::derived_from<builder, BaseCarcasBuilder> && std::constructible_from<builder, std::shared_ptr<AbstractReader>>
    std::shared_ptr<AbstractObject> load(const std::string& filename, const bool isbin, const bool ismatrix)
    {
        std::shared_ptr<BaseDirector> myDirector = solution->create(filename, isbin, ismatrix);
        return myDirector->create();
    }
    
    void setSolution(std::shared_ptr<LoadSolution> solution)
    {
        this->solution = solution;
    }

private:
    std::shared_ptr<LoadSolution> solution;

    // template<typename builder>
    //     requires std::derived_from<builder, BaseCarcasBuilder> && std::constructible_from<builder, std::shared_ptr<AbstractReader>>
    // std::shared_ptr<AbstractObject> load_from_file(const std::string& filename)
    // {
    //     const char* name = filename.c_str();
    //     std::shared_ptr<AbstractReader> reader = std::make_shared<FileReader>(filename);
    //     std::shared_ptr<BaseCarcasBuilder> _builder = std::make_shared<builder>(reader);
    //     std::shared_ptr<BaseDirector> myDirector = DirectorCreator::create<CarcasDirector>(_builder);
    //     return myDirector->create();
    // }

    // template<typename builder>
    //     requires std::derived_from<builder, BaseCarcasBuilder> && std::constructible_from<builder, std::shared_ptr<AbstractReader>>
    // std::shared_ptr<AbstractObject> load_from_binary(const std::string& filename)
    // {
    //     std::shared_ptr<AbstractReader> reader = std::make_shared<BinaryReader>(filename);
    //     std::shared_ptr<BaseCarcasBuilder> _builder = std::make_shared<builder>(reader);
    //     std::shared_ptr<BaseDirector> myDirector = DirectorCreator::create<CarcasDirector>(_builder);
    //     return myDirector->create();
    // }

    // std::shared_ptr<AbstractObject> load_composite_file(const std::string& filename)
    // {
    //     FILE *file = fopen(filename.c_str(), "r");
    //     std::shared_ptr<CompositeObject> composite = std::make_shared<CompositeObject>();
    //     int cnt = 0;
    //     fscanf(file, "%d", &cnt);
    //     for (int i = 0; i < cnt; i++)
    //     {
    //         int carcas, filet;
    //         char tmp_file[512];
    //         fscanf(file, "%d %d %s", &filet, &carcas, tmp_file);
    //         const std::string& new_filename = std::string(tmp_file);
    //         if (filet == COMP)
    //             this->load_composite_file(new_filename);
    //         if (filet == TXT)
    //         {
    //             if (carcas == CARCAS)
    //             {
    //                 std::shared_ptr<AbstractObject> obj = this->load_from_file<CarcasBuilder>(new_filename);
    //                 composite->add(obj);
    //             }
    //             else
    //             {
    //                 auto obj = this->load_from_file<MatrixBuilder>(new_filename);
    //                 composite->add(obj);
    //             }
    //         }
    //         else
    //         {
    //             if (carcas == CARCAS)
    //             {
    //                 auto obj = this->load_from_binary<CarcasBuilder>(new_filename);
    //                 composite->add(obj);
    //             }
    //             else
    //             {
    //                 auto obj = this->load_from_binary<MatrixBuilder>(new_filename);
    //                 composite->add(obj);
    //             }
    //         }
    //     }
    //     fclose(file);
    //     return composite;
    // }

// protected:
//     std::shared_ptr<AbstractReader> get_reader(int num, const std::string& filename)
//     {
//         if (num == TXT)
//             return std::make_shared<FileReader>(filename);
//         else
//             return std::make_shared<BinaryReader>(filename);
//     }

//     std::shared_ptr<BaseCarcasBuilder> get_builder(int num, std::shared_ptr<AbstractReader> reader )
//     {
//         if (num == CARCAS)
//             return std::make_shared<CarcasBuilder>(reader);
//         else
//             return std::make_shared<MatrixBuilder>(reader);
//     }
};

#endif // LOAD_MANAGER_H
