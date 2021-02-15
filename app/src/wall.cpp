#include "wall.h"

Wall::Wall(WallType type, int posX, int posY) :
            DisplayableObject(ModelType::WALL, posX, posY), wallType_(type)
{

}

void Wall::move(FRKey direction, int frame) {
    return;
}

void Wall::ifCollisionDetected(DisplayableObject *obj) {
        switch (obj->type_) {
            case ModelType::ENEMY_BULLET : {
                if(this->getWallType() == WallType::BRICK) {
                    this->hitObject();
                    obj->hitObject();
                }
                break;
            }
            case ModelType::PLAYER_BULLET : {
                if(this->getWallType() == WallType::BRICK) {
                    this->hitObject();
                    obj->hitObject();
                }
                break;
            }
            default: break;
        }
//    DisplayableObject::ifCollisionDetected(obj);
}

void Wall::hitObject() {
    if(wallType_ == WallType::BRICK)
        this->isVisible_ = false;
}



void Wall::ifBorderCollisionDetected() {
    return;
}
