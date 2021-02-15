#pragma once
#include "Framework.h"
#include "player.h"
#include "displayableObject.h"

class Booster : public DisplayableObject {
public:
    Booster(int posX, int posY) : DisplayableObject(ModelType::EXTRA_LIFE, posX, posY) {
        sprite_ = createSprite("../../app/resources/ExtraLife.TGA");
        isVisible_ = false;
        setCollisionModel();
    }

    void ifBorderCollisionDetected() override;
    void move(FRKey direction, int frame) override;
    void ifCollisionDetected(DisplayableObject *obj) override;
    void hitObject() override;

    void setPosition(int posX, int posY) {
        this->collisionModel.x = posX;
        this->collisionModel.y = posY;
    }

    ~Booster() {
        destroySprite(sprite_);
    }

};
