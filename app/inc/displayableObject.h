#pragma once
#include "Framework.h"
#include <vector>
#include <iostream>


typedef struct Rectangle {
  int x;
  int y;
  int width;
  int height;
} Rect;

enum class ModelType {
    PLAYER,
    ENEMY,
    WALL,
    ENEMY_BULLET,
    PLAYER_BULLET,
    EAGLE,
    EXTRA_LIFE
};

class DisplayableObject {
public:
    const ModelType type_;
    Rect collisionModel;

    DisplayableObject(ModelType modelType, int posX, int posY);
    virtual ~DisplayableObject();

    void setCollisionModel();

    void draw() {
        drawSprite(sprite_, collisionModel.x, collisionModel.y);
    }
    bool checkCollision(const DisplayableObject *obj) const;

    virtual void ifCollisionDetected(DisplayableObject* obj) = 0;
    virtual void hitObject() = 0;
    virtual void move(FRKey direction, int frame) = 0;
    bool borderCollision();
    virtual void ifBorderCollisionDetected() = 0;


    ModelType getType() const {
        return type_;
    }

    bool getIsVisible() const;

    void setIsVisible(bool isVisible);

protected:
    bool isVisible_;
    Sprite* sprite_;

    bool checkBorder(FRKey direction);
};
