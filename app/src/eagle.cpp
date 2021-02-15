#include "eagle.h"


Eagle::Eagle(int posX, int posY) : DisplayableObject(ModelType::EAGLE, posX, posY), status_(true)
{
    basic_ = createSprite("../../app/resources/Base.TGA");
    defeat_ = createSprite("../../app/resources/BaseDefeat.TGA");
    sprite_ = basic_;
    setCollisionModel();
}

void Eagle::move(FRKey direction, int frame) {
    return;
}

void Eagle::ifCollisionDetected(DisplayableObject *obj) {
    switch (obj->type_) {
        case ModelType::PLAYER_BULLET : {
            this->destroy();
            break;
        }
        case ModelType::ENEMY_BULLET : {
            this->destroy();
            break;
        }
    }
}

void Eagle::hitObject() {
    destroy();
}


void Eagle::ifBorderCollisionDetected() {
    return;
}
