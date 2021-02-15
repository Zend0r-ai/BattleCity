#include "player.h"

Player::Player(int posX, int posY, FRKey direction) : direction_(direction),
                DisplayableObject(ModelType::PLAYER, posX, posY) {
    spriteBase.push_back(createSprite("../../app/resources/PlayerRIGHT.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/PlayerLEFT.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/PlayerDOWN.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/PlayerUP.TGA"));
    sprite_ = spriteBase.at(static_cast<int>(direction));
    tankSpeed_ = 2;
    setCollisionModel();
    health_ = 2;
    isShootable_ = true;

}

void Player::rotate(FRKey newDirection) {
    if(direction_ != newDirection) {
        direction_ = newDirection;
        switch (direction_) {
            case FRKey::RIGHT: {
                sprite_ = spriteBase.at(0);
                break;
            }
            case FRKey::LEFT : {
                sprite_ = spriteBase.at(1);
                break;
            }
            case FRKey::DOWN : {
                sprite_ = spriteBase.at(2);
                break;
            }
            case FRKey::UP : {
                sprite_ = spriteBase.at(3);
                break;
            }
            default:
                break;
        }
    }
}

void Player::move(FRKey direction, int frame) {
    if(frame % (4 - this->tankSpeed_) == 0)
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

bool Player::isShootable() const {
    return isShootable_;
}

bool Player::getDamage() {
    this->health_--;
}

void Player::restartBattle() {
    int w, h;
    getScreenSize(w,h);
    this->collisionModel.x = w / 2 - 32;
    this->collisionModel.y = h / 2 + (8 * 22) / 2;
    this->direction_ = FRKey::UP;
//    screenSizeWidth_ / 2 - (8 * 8) / 2 , screenSizeHeight_ / 2 + (8 * 22) / 2,
}

void Player::ifCollisionDetected(DisplayableObject *obj) {
    switch (obj->type_) {
        case ModelType::ENEMY_BULLET : {
            obj->hitObject();
            this->hitObject();
            break;
        }
        case ModelType::ENEMY : {
            this->hitObject();
            break;
        }
        case ModelType::EXTRA_LIFE : {
            this->addHP();
            obj->hitObject();
            break;
        }
        case ModelType::WALL : {
            if(direction_ == FRKey::RIGHT)
                this->collisionModel.x--;
            else if (direction_ == FRKey::LEFT)
                this->collisionModel.x++;
            if(direction_ == FRKey::DOWN)
                this->collisionModel.y--;
            else if (direction_ == FRKey::UP)
                this->collisionModel.y++;
            break;
        }
        case ModelType::EAGLE : {
            if(direction_ == FRKey::RIGHT)
                this->collisionModel.x--;
            else if (direction_ == FRKey::LEFT)
                this->collisionModel.x++;
            if(direction_ == FRKey::DOWN)
                this->collisionModel.y--;
            else if (direction_ == FRKey::UP)
                this->collisionModel.y++;
            break;
        }
    }
}

void Player::hitObject() {
    this->getDamage();
    if(this->health_ != 0)
        this->restartBattle();
}
//
//void Player::borderCollision() {
//    if(checkBorder(direction_)) {
//        if(direction_ == FRKey::RIGHT)
//            this->move(FRKey::LEFT);
//        else if (direction_ == FRKey::LEFT)
//            this->move(FRKey::RIGHT);
//        if(direction_ == FRKey::DOWN)
//            this->move(FRKey::UP);
//        else if (direction_ == FRKey::UP)
//            this->move(FRKey::DOWN);
//    }
////    return DisplayableObject::borderCollision();
//}

void Player::ifBorderCollisionDetected() {
    if(direction_ == FRKey::RIGHT)
        this->collisionModel.x--;
    else if (direction_ == FRKey::LEFT)
        this->collisionModel.x++;
    if(direction_ == FRKey::DOWN)
        this->collisionModel.y--;
    else if (direction_ == FRKey::UP)
        this->collisionModel.y++;
}
