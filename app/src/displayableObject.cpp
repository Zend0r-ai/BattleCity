#include "displayableObject.h"

DisplayableObject::DisplayableObject(ModelType modelType, int posX, int posY) : type_(modelType) {
    collisionModel.x = posX;
    collisionModel.y = posY;
    isVisible_ = true;
}

DisplayableObject::~DisplayableObject() {
    destroySprite(sprite_);
}



bool DisplayableObject::checkCollision(const DisplayableObject *obj) const {
    bool collX = this->collisionModel.x + this->collisionModel.width >= obj->collisionModel.x && // !!!!
        obj->collisionModel.x + obj->collisionModel.width >= this->collisionModel.x; // !!!!
    bool collY = this->collisionModel.y + this->collisionModel.height >= obj->collisionModel.y && // !!!
        obj->collisionModel.y + obj->collisionModel.height >= this->collisionModel.y; // !!!!
    return collX && collY;
}

bool DisplayableObject::borderCollision() {
    int w, h;
    getScreenSize(w, h);
    bool collX, collY;
    collX = this->collisionModel.x + this->collisionModel.width == w / 2 + 104 ||
            w / 2 - 104 == this->collisionModel.x ||
            this->collisionModel.y + this->collisionModel.height == h / 2 + 104 || // !!!
            h / 2 - 104 == this->collisionModel.y; // !!!!


    return collX;
}

void DisplayableObject::move(FRKey direction, int frame) {
    switch (direction) {
        case FRKey::RIGHT:{
            this->collisionModel.x++;
            break;}
        case FRKey::LEFT : {
            this->collisionModel.x--;
            break;
        }
        case FRKey::DOWN : {
            this->collisionModel.y++;
            break;
        }
        case FRKey::UP : {
            this->collisionModel.y--;
            break;
        }
        default: break;
    }
}

void DisplayableObject::setCollisionModel() {
    if(!sprite_)
        return;
    int width, height;
    getSpriteSize(sprite_, width, height);
    collisionModel.width = width;
    collisionModel.height = height;
}

bool DisplayableObject::getIsVisible() const {
    return isVisible_;
}

void DisplayableObject::setIsVisible(bool isVisible) {
    isVisible_ = isVisible;
}

bool DisplayableObject::checkBorder(FRKey direction) {
//    bool res;
//    int screenW, screenH;
//    getScreenSize(screenW, screenH);
//    switch (direction) {
//        case FRKey::RIGHT: {
//            res = this->collisionModel.x + this->collisionModel.width >= screenW / 2 + 104;
//            break;
//        }
//        case FRKey::LEFT : {
//            res = this->collisionModel.x <= screenW / 2 - 104;
//            break;
//        }
//        case FRKey::DOWN : {
//            res = this->collisionModel.y + this->collisionModel.height >= screenH / 2 + 104;
//            break;
//        }
//        case FRKey::UP : {
//            res = this->collisionModel.y <= screenH / 2 - 104;
//            break;
//        }
//        default:
//            break;
//    }
//    return res;
    int w, h;
    getScreenSize(w, h);
    bool collX, collY;
    collX = this->collisionModel.x + this->collisionModel.width <= w / 2 + 104 &&
            w / 2 - 104 <= this->collisionModel.x + this->collisionModel.width; // !!!!
    collY = this->collisionModel.y + this->collisionModel.height <= h / 2 + 104 && // !!!
            h / 2 - 104 <= this->collisionModel.y + this->collisionModel.height; // !!!!


    return collX && collY;
}

//bool DisplayableObject::borderCollision() const {
//    int w, h;
//    getScreenSize(w, h);
//    bool collX, collY;
//    collX = this->collisionModel.width <= w / 2 + 104 &&
//            w / 2 - 104 <= this->collisionModel.x; // !!!!
//    collY = this->collisionModel.height <= h / 2 + 104 && // !!!
//            h / 2 - 104 <= this->collisionModel.y; // !!!!
//
//
//    return collX && collY;
//}
