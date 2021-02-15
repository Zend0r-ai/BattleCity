#pragma once

#include "Framework.h"

#include "booster.h"
#include "displayableObject.h"
#include "bullet.h"
#include "Gui.h"

enum class EnemyType {
    BASIC,
    FAST
};

class Booster;

class Enemy : public DisplayableObject {
public:
    Enemy(int posX, int posY, EnemyType type, bool giveBooster);
    ~Enemy() {
        for(auto it : spriteBase) destroySprite(it);
        spriteBase.clear();
        destroySprite(sprite_);
    }
    FRKey chooseDirection() {
        return static_cast<FRKey>(rand() % 4);
    }

    bool checkCollision(const DisplayableObject* obj, FRKey direction) const;

    void ifBorderCollisionDetected() override;

    void rotate(FRKey newDirection);
    void move(FRKey direction, int frame) override;
    void ifCollisionDetected(DisplayableObject *obj) override;
    void hitObject() override;

    // get/set
    Booster *getBooster() const;

    void setBooster(Booster *booster);

    bool getShootAvalable() const { return isShootable_; }
    void setShootAvalable() { isShootable_ == !isShootable_; }

    int getHealth() const;
    void setHealth(int health);

    bool getBoosterAvailable() const;
    void setBoosterAvailable(bool setBooster);

    bool getIsAlive() const;
    void setIsAlive(bool isAlive);

    FRKey getDirection() const;

    void setDirection(FRKey direction);
    //get/set

    bool getDamage();

    int getBulletSpeed() const;

protected:

    FRKey direction_ = FRKey::DOWN;
    std::vector<Sprite*> spriteBase;
    bool isAlive_;
    int health_;
    int tankSpeed_;
    int bulletSpeed_;

    bool giveBooster_;
    Booster* booster_;
    bool isShootable_;
};




class BasicEnemy : public Enemy {
public:
     BasicEnemy(int posX, int posY, bool booster) : Enemy(posX, posY, EnemyType::BASIC, booster) {
        health_ = 1;
        tankSpeed_ = 1;
        bulletSpeed_ = 1;
    }
};

class FastEnemy : public Enemy{
public:
    FastEnemy(int posX, int posY, bool booster) :  Enemy(posX, posY, EnemyType::FAST, booster) {
        health_ = 1;
        tankSpeed_ = 3;
        bulletSpeed_ = 2;
    }

};




