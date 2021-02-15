#pragma once
#include "Framework.h"
#include "bullet.h"
#include "Gui.h"
#include "displayableObject.h"


class Bullet;
class DisplayableObject;

class Player : public DisplayableObject {
public:
    Player(int posX, int posY, FRKey direction);
    ~Player()  {
        for(auto it : spriteBase) destroySprite(it);
        spriteBase.clear();
        destroySprite(sprite_);
///        delete bullet_;
    }

    void rotate(FRKey newDirection);

    void ifBorderCollisionDetected() override;

    void move(FRKey direction, int frame) override;

    void ifCollisionDetected(DisplayableObject *obj) override;

    void hitObject() override;

    bool isShootable() const;

    void setIsShootable(bool value) {isShootable_ = value;}
    void addHP() {health_++;}
    int getHP() { return health_; }
    FRKey getDirection() const {return direction_;}

    bool getDamage();

    void restartBattle();

private:
    FRKey direction_;
    std::vector<Sprite*> spriteBase;
    int health_;
    int tankSpeed_;
    int bulletSpeed_;
    bool isShootable_;
};
