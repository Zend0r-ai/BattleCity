#pragma once

#include <utility>

#include "Framework.h"
#include "enemy.h"
#include "player.h"
#include "displayableObject.h"

class Bullet : public DisplayableObject {
public:
    Bullet(int newPosX, int newPosY, FRKey newDirection, ModelType bulletType, int speed, DisplayableObject* owner);
    ~Bullet() {
        for(auto it : spriteBase) destroySprite(it);
        spriteBase.clear();
        destroySprite(sprite_);
        owner_ = nullptr;
    }

    void move(FRKey direction, int frame) override;
    void ifCollisionDetected(DisplayableObject *obj) override;
    void hitObject() override;

    void removeToOwner();

    void setDirection(FRKey newDirection) {
        direction_ = newDirection;
    }

FRKey getDirection() const {
        return direction_;
    }
    const DisplayableObject* getOwner() {
        return owner_;
    }

    void ifBorderCollisionDetected() override;

private:
    DisplayableObject* owner_;
    std::vector<Sprite*> spriteBase;
    FRKey direction_;
    int speed_;
};
