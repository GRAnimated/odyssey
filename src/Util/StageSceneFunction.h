#pragma once

#include <al/Library/LiveActor/LiveActor.h>

namespace StageSceneFunction {
void appearPlayerDeadCoin(al::LiveActor*);
}

class IJudge;

namespace rs {
void resetJudge(IJudge*);
bool updateJudge(IJudge*);
bool isJudge(const IJudge*);
bool updateJudgeAndResult(IJudge*);
void judgeAndResetReturnTrue(IJudge*);
void isEnableShowDemoAfterOpenMoonRockFirst(const al::LiveActor*);
void isFirstDemoOpenMoonRock(const al::LiveActor*);
void isEnableShowDemoMoonRockMapWorld(const al::LiveActor*);
void showDemoAfterOpenMoonRockFirst(const al::LiveActor*);
void showDemoMoonRockMapWorld(const al::LiveActor*);
}  // namespace rs
