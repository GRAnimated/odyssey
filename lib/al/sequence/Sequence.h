#pragma once

#include <prim/seadSafeString.h>
#include "al/iuse/IUseAudioKeeper.h"
#include "al/iuse/IUseSceneCreator.h"
#include "al/nerve/NerveExecutor.h"
#include "al/system/GameDrawInfo.h"

namespace al {
class GameSystemInfo;
class SequenceInitInfo;
class AudioSystemInfo;
class AudioDirector;
class Scene;

class Sequence : public al::NerveExecutor, public al::IUseAudioKeeper, public al::IUseSceneCreator {
public:
    Sequence(const char* name);
    virtual ~Sequence() override;
    virtual void init(const al::SequenceInitInfo& initInfo);
    virtual void update();
    virtual void kill();
    virtual void drawMain() const;
    virtual void drawSub() const;
    virtual bool isDisposable() { return false; }
    virtual al::Scene* getCurrentScene() const;
    virtual al::SceneCreator* getSceneCreator() const override;
    virtual void setSceneCreator(al::SceneCreator* sceneCreator) override;

    al::AudioKeeper* getAudioKeeper() const override;
    void initAudio(const al::GameSystemInfo&, const char*, int, int, int, const char*);
    void initAudioKeeper(const char*);
    void initDrawSystemInfo(const al::SequenceInitInfo&);
    al::AudioSystemInfo* getAudioSystemInfo();

protected:
    al::GameDrawInfo* getDrawInfo() const { return mGameDrawInfo; }

private:
    sead::FixedSafeString<0x40> mName;
    al::Scene* mNextScene;
    al::Scene* mCurrentScene;
    al::SceneCreator* mSceneCreator;
    al::AudioDirector* mAudioDirector;
    al::AudioKeeper* mAudioKeeper;
    al::GameDrawInfo* mGameDrawInfo;
    bool mIsAlive;
};
}  // namespace al