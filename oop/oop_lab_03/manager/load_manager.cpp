#include "load_manager.h"

LoadManager::LoadManager() {
    std::shared_ptr<LoadSolution> solution = std::make_shared<LoadSolution>();
    setSolution(solution);
}
