#include "game/gameData/progression/AchievementInfoReader.h"

#include "al/byaml/ByamlIter.h"
#include "al/util/ResourceUtil.h"
#include "al/util/StringUtil.h"

AchievementInfoReader::AchievementInfoReader() = default;

void AchievementInfoReader::init() {  // TODO minor mismatches during loop
    al::Resource* achievementInfoResource =
        al::findOrCreateResource("SystemData/AchievementInfo", nullptr);
    const char* byamlFileName = al::StringTmp<256>{"%s.byml", "AchievementInfo"}.cstr();

    if (!achievementInfoResource->isExistFile(byamlFileName))
        return;

    al::ByamlIter achievementInfo = achievementInfoResource->getByml("AchievementInfo");
    al::ByamlIter achievementInfoArray;
    if (achievementInfo.tryGetIterByKey(&achievementInfoArray, "AchievementInfoArray")) {
        auto size = achievementInfoArray.getSize();
        array.allocBuffer(size, nullptr);

        for (u32 i = 0; i < size; i++) {
            al::ByamlIter iter;
            if (achievementInfoArray.tryGetIterByIndex(&iter, i)) {
                const char* name = nullptr;
                iter.tryGetStringByKey(&name, "Name");
                const char* note = nullptr;
                iter.tryGetStringByKey(&note, "Note");
                int num = 1;
                iter.tryGetIntByKey(&num, "Num");
                int level = -1;
                iter.tryGetIntByKey(&level, "Level");

                array.pushBack(new AchievementInfo(name, num, level, note));
            }
        }
    }
}

int AchievementInfoReader::tryFindIndexByName(const char* name) const {
    for (int i = 0; i < array.size(); i++) {
        if (al::isEqualString(name, array[i]->mName))
            return i;
    }
    return -1;
}
