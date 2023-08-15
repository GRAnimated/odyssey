#include "EnemyStateDamageCap.h"
#include "Enemy/EnemyCap.h"
#include <al/Library/Nerve/NerveSetupUtil.h>
#include <al/Library/LiveActor/ActorActionFunction.h>
#include <al/Library/LiveActor/ActorFlagFunction.h>

namespace {
NERVE_IMPL(EnemyStateDamageCap, Wait);
NERVE_IMPL(EnemyStateDamageCap, DamageCap);

struct {
    NERVE_MAKE(EnemyStateDamageCap, Wait);
    NERVE_MAKE(EnemyStateDamageCap, DamageCap);
} NrvEnemyStateDamageCap;

}  // namespace

namespace rs {
bool isMsgCapAttack(const al::SensorMsg*);
void requestHitReactionToAttacker(const al::SensorMsg*, const al::HitSensor*, const al::HitSensor*);
}  // namespace rs

EnemyStateDamageCap::EnemyStateDamageCap(al::LiveActor* actor) : al::ActorStateBase("キャプチャ敵の帽子反応ステート", actor) {
    mEnemyCap = nullptr;
    initNerve(&NrvEnemyStateDamageCap.Wait, 0);
}

void EnemyStateDamageCap::kill() {
    al::setNerve(this, &NrvEnemyStateDamageCap.Wait);
    mIsDead = true;
}

void EnemyStateDamageCap::createEnemyCap(const al::ActorInitInfo& info, const char* name) {
    mEnemyCap = rs::tryCreateEnemyCap(mActor, info, name);
}

bool EnemyStateDamageCap::tryReceiveMsgCapBlow(const al::SensorMsg* msg, al::HitSensor* source, al::HitSensor* target) {
    if (!mEnemyCap)
        return false;
    if (al::isAlive(mEnemyCap) && !mEnemyCap->isBlowDown() && rs::isMsgCapAttack(msg)) {
        rs::requestHitReactionToAttacker(msg, target, source);
        mEnemyCap->startBlowDown(source);
        al::setNerve(this, &NrvEnemyStateDamageCap.Wait);
        return true;
    }
    return false;
}

bool EnemyStateDamageCap::isCapOn() const {
    if (mEnemyCap && al::isAlive(mEnemyCap))
        return mEnemyCap->isBlowDown() ^ 1;
    return false;
}

void EnemyStateDamageCap::blowCap(al::HitSensor* source) {
    if (!mEnemyCap || !al::isAlive(mEnemyCap))
        return;
    if (!mEnemyCap->isBlowDown())
        mEnemyCap->startBlowDown(source);
}

void EnemyStateDamageCap::resetCap() {
    if (mEnemyCap)
        mEnemyCap->appear();
}

void EnemyStateDamageCap::makeActorDeadCap() {
    if (mEnemyCap)
        mEnemyCap->makeActorDead();
}

void EnemyStateDamageCap::exeWait() {}

void EnemyStateDamageCap::exeDamageCap() {
    if (al::isFirstStep(this))
        al::startAction(mActor, "DamageCap");
    if (al::isActionEnd(mActor))
        kill();
}