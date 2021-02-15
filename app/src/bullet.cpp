#include "bullet.h"

Bullet::Bullet(int newPosX, int newPosY, FRKey newDirection, ModelType bulletType, int speed, DisplayableObject* owner) :
              DisplayableObject(bulletType, newPosX, newPosY),
              direction_(newDirection), speed_(speed), owner_(owner) {
    spriteBase.push_back(createSprite("../../app/resources/BulletRIGHT.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/BulletLEFT.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/BulletDOWN.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/BulletUP.TGA"));
    sprite_ = spriteBase.at(static_cast<int>(newDirection));
    isVisible_ = false;
    setCollisionModel();
}

void Bullet::move(FRKey direction, int frame) {
    if(isVisible_){
        direction_ = direction;
        switch (direction) {
            case FRKey::RIGHT: {
                this->collisionModel.x++;
                break;
            }
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
            default:
                break;
        }
    }
}

void Bullet::removeToOwner() {
    if(owner_->type_ == ModelType::ENEMY) {
        auto enemy = dynamic_cast<Enemy*>(owner_);
        this->setDirection(enemy->getDirection());
        this->collisionModel = owner_->collisionModel;
    } else if(owner_->type_ == ModelType::PLAYER) {
        this->collisionModel = owner_->collisionModel;
        isVisible_ = false;
        auto player = dynamic_cast<Player*>(owner_);
        player->setIsShootable(true);
    }
}

void Bullet::ifCollisionDetected(DisplayableObject *obj) {
    switch (obj->type_) {
        case ModelType::WALL : {
            this->hitObject();
            obj->hitObject();
            break;
        }
        case ModelType::EAGLE : {
            this->hitObject();
            obj->hitObject();
            break;
        }
        default: break;
    }
    if(this->type_ == ModelType::ENEMY_BULLET &&
        (obj->type_ == ModelType::PLAYER || obj->type_ == ModelType::PLAYER_BULLET)) {
        this->hitObject();
        obj->hitObject();
    } else if(this->type_ == ModelType::PLAYER_BULLET &&
        (obj->type_ == ModelType::ENEMY || obj->type_ == ModelType::ENEMY_BULLET)) {
        this->hitObject();
        obj->hitObject();
    }
}

void Bullet::hitObject() {
    this->removeToOwner();
}
//
//void Bullet::borderCollision() {
////    if(checkBorder(direction_))
//        this->removeToOwner();
//}

void Bullet::ifBorderCollisionDetected() {
    this->removeToOwner();
}
//    int w, h;
//    getScreenSize(w, h);
//    bool collX, collY;
//    collX = this->collisionModel.width <= w / 2 + 104 &&
//            w / 2 - 104 <= this->collisionModel.x; // !!!!
//    collY = this->collisionModel.height <= h / 2 + 104 && // !!!
//            h / 2 - 104 <= this->collisionModel.y; // !!!!