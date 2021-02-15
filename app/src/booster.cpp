#include "booster.h"



void Booster::move(FRKey direction, int frame) {
    return;
}

void Booster::ifCollisionDetected(DisplayableObject *obj) {
    if(obj->type_ == ModelType::PLAYER) {
        auto player = dynamic_cast<Player*>(obj);
        player->addHP();
        hitObject();
    }
//    DisplayableObject::ifCollisionDetected(obj);
}

void Booster::hitObject() {
    this->isVisible_ = false;
}

void Booster::ifBorderCollisionDetected() {
    return;
}
