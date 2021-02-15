#include "enemy.h"

Enemy::Enemy(int posX, int posY, EnemyType type, bool giveBooster) :
        DisplayableObject(ModelType::ENEMY, posX, posY), giveBooster_(giveBooster){
    spriteBase.push_back(createSprite("../../app/resources/BasicEnemyRIGHT.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/BasicEnemyLEFT.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/BasicEnemyDOWN.TGA"));
    spriteBase.push_back(createSprite("../../app/resources/BasicEnemyUP.TGA"));
    sprite_ = spriteBase.at(static_cast<int>(direction_));

    tankSpeed_ = 1;
    setCollisionModel();
    isAlive_ = true;
    isVisible_ = false;
}

bool Enemy::checkCollision(const DisplayableObject *obj, FRKey direction) const {
    return false;
}

int Enemy::getHealth() const {
    return health_;
}

void Enemy::setHealth(int health) {
    health_ = health;
}

bool Enemy::getBoosterAvailable() const {
    return giveBooster_;
}

void Enemy::setBoosterAvailable(bool giveBooster) {
    giveBooster_ = giveBooster;
}

void Enemy::rotate(FRKey newDirection) {
    if(direction_ != newDirection && !this->borderCollision()) {
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

void Enemy::move(FRKey direction, int frame) {
    if (frame % (4 - tankSpeed_) == 0)
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

bool Enemy::getDamage() {
    health_--;
    if(health_ == 0)
        return false;

    return true;
}

void Enemy::ifCollisionDetected(DisplayableObject *obj) {
    switch (obj->type_) {
        case ModelType::PLAYER_BULLET : {
            auto bullet = dynamic_cast<Bullet*>(obj);
            bullet->removeToOwner();
            if(!this->getDamage())
                this->setIsVisible(false);
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
        default: break;
    }
}

void Enemy::hitObject() {
    if(!this->getDamage()) {
        this->isAlive_ = false;
        this->isVisible_ = false;
    }
    if(this->giveBooster_)
        booster_->setPosition(this->collisionModel.x, this->collisionModel.y);
}

bool Enemy::getIsAlive() const {
    return isAlive_;
}

void Enemy::setIsAlive(bool isAlive) {
    isAlive_ = isAlive;
}

FRKey Enemy::getDirection() const {
    return direction_;
}

void Enemy::setDirection(FRKey direction) {
    direction_ = direction;
}

int Enemy::getBulletSpeed() const {
    return bulletSpeed_;
}

void Enemy::ifBorderCollisionDetected() {
    if(direction_ == FRKey::RIGHT)
        this->collisionModel.x--;
    else if (direction_ == FRKey::LEFT)
        this->collisionModel.x++;
    if(direction_ == FRKey::DOWN)
        this->collisionModel.y--;
    else if (direction_ == FRKey::UP)
        this->collisionModel.y++;
}

Booster *Enemy::getBooster() const {
    return booster_;
}

void Enemy::setBooster(Booster *booster) {
    booster_ = booster;
}

