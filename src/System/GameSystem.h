#pragma once

#include <al/Library/Nerve/NerveExecutor.h>
#include <al/Library/Nerve/NerveSetupUtil.h>

namespace al {
class Sequence;
class GameSystemInfo;
class AudioSystem;
class AudioInfoListWithParts;
class AccountHolder;
class NetworkSystem;
class HtmlViewer;
class GamePadSystem;
class ApplicationMessageReceiver;
class WaveVibrationHolder;
}

class ProjectNfpDirector;
class GameConfigData;
class GameSystem : public al::NerveExecutor {
    al::Sequence* mSequence;
    al::GameSystemInfo* mSystemInfo;
    al::AudioSystem * mAudioSystem;
    al::AudioInfoListWithParts* mAudioInfoList;
    al::AccountHolder* mAccountHolder;
    al::NetworkSystem* mNetworkSystem;
    void* field_40;
    al::HtmlViewer* mHtmlViewer;
    ProjectNfpDirector* mNfpDirector;
    al::GamePadSystem* mGamePadSystem;
    al::ApplicationMessageReceiver* mApplicationMessageReceiver;
    al::WaveVibrationHolder* mWaveVibrationHolder;
    bool mIsSinglePlay;
    GameConfigData *mGameConfigData;
    bool mIsSequenceSetupIncomplete;

public:
    GameSystem();
    virtual ~GameSystem();
    virtual void init();
    virtual void movement();
    void setPadName();
    bool tryChangeSequence(const char*);
    void drawMain();

    void exePlay();
};
