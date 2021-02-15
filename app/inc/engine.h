#pragma once

#include <iostream>

#include <Framework.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "displayableObject.h"
#include "booster.h"
#include "bullet.h"
#include "enemy.h"
#include "eagle.h"
#include "player.h"
#include "wall.h"
#include <memory>
#include <list>
#include <deque>
#include "Gui.h"
#include <algorithm>

using namespace std;

class Engine : public Framework {
public:
    Engine(int width, int height);
    ~Engine() override;
private:
    virtual void PreInit(int& width, int& height, bool& fullscreen);
    virtual bool Init();
    virtual void Close();
    virtual bool Tick();
    virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);
    virtual void onKeyPressed(FRKey k);
    virtual void onKeyReleased(FRKey k);
    virtual const char* GetTitle() override;

    void readMap(const string& map);
    void readEnemyList(const string& list);
    void collisionDetection();
    bool borderCollision(DisplayableObject* obj);
    void drawFrame();

    void spawnEnemies();

    int screenSizeWidth_, screenSizeHeight_;
    int frameCount = 0;
    Player* player;
    Bullet* playerBullet;
    Sprite* void_;
    Eagle* base;
    Gui* gui_;
    vector<Enemy*> enemyList;
    Booster* extraLife;
    vector<DisplayableObject*> allObj;

    FRKey curPlayerDirection = FRKey::COUNT;
    bool isMove = false;

};
