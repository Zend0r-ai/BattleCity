#pragma once
#include "bullet.h"

#include "displayableObject.h"

enum class WallType {
    BRICK,
    STEEL
};

class DisplayableObject;

class Wall : public DisplayableObject {
public:

    Wall(WallType type, int posX, int posY);
    virtual ~Wall() {
        destroySprite(sprite_);
    }
    WallType getWallType() const {
        return wallType_;
    }

    void ifCollisionDetected(DisplayableObject *obj) override;

    void move(FRKey direction, int frame) override;

    void ifBorderCollisionDetected() override;

    void hitObject() override;

protected:
    WallType wallType_;

};




class BrickWall : public Wall {
public:
    BrickWall(int posX, int posY) : Wall(WallType::BRICK, posX, posY) {
        sprite_ = createSprite("../../app/resources/BasicWall.TGA");
        setCollisionModel();
    }
    ~BrickWall()  {
        destroySprite(sprite_);
    }
};




class SteelWall : public Wall {
public:
    SteelWall(int posX, int posY) : Wall(WallType::STEEL, posX, posY) {
        sprite_ = createSprite("../../app/resources/SteelWall.TGA");
        setCollisionModel();
    }
    ~SteelWall()  {
        destroySprite(sprite_);
    }
};
