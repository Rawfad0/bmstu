#include "load_solution.h"

LoadSolution::LoadSolution() {}

// template<typename builder>
//     requires std::derived_from<builder, BaseCarcasBuilder> && std::constructible_from<builder, std::shared_ptr<AbstractReader>> 
std::shared_ptr<BaseDirector> LoadSolution::create(const std::string &filename, bool isbin, bool ismatrix)
{
    std::shared_ptr<AbstractReader> reader;
    if (isbin)
        reader = std::make_shared<BinaryReader>(filename);
    else
        reader = std::make_shared<FileReader>(filename);

    std::shared_ptr<BaseCarcasBuilder> _builder;
    if (ismatrix)
        _builder = std::make_shared<MatrixBuilder>(reader);
    else
        _builder = std::make_shared<CarcasBuilder>(reader);
    // std::shared_ptr<BaseCarcasBuilder> _builder = std::make_shared<CarcasBuilder>(reader);
    std::shared_ptr<BaseDirector> myDirector = DirectorCreator::create<CarcasDirector>(_builder);
    return myDirector;
}
