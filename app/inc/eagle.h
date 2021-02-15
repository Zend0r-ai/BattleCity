#pragma once
#include "displayableObject.h"
#include "Gui.h"

class Eagle : public DisplayableObject {
public:
    Eagle(int posX, int posY);
    ~Eagle() {
        destroySprite(basic_);
        destroySprite(sprite_);
        destroySprite(defeat_);
    }

    bool getStatus() const {
        return status_;
    }
    void destroy() {
        status_ = false;
        sprite_ = defeat_;
    }

    void ifBorderCollisionDetected() override;

    void ifCollisionDetected(DisplayableObject *obj) override;

    void move(FRKey direction, int frame) override;

    void hitObject() override;

private:
    bool status_;
    Sprite* basic_;
    Sprite* defeat_;
};

