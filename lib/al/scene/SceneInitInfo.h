#pragma once

#include "al/resource/GameDataHolderAccessor.h"

namespace al {
struct SceneInitInfo {
    struct GameSystemInfo* gameSysInfo;
    GameDataHolderAccessor* gameDataHolder;
    void* gap;
    char* initStageName;
    unsigned int scenarioNo;
};
}  // namespace al
