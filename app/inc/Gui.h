#pragma once
#include <Framework.h>
#include <vector>
class Gui {
public:
    Gui(int posX, int posY);

    void setPlayerHP(int HP) {
//        if(HP >= 0)
            playerHP_ = HP;
    }


    void setEnemyCount(int count) {
        enemyCount_ = count;
    }
//    static bool setPlayerHP(int HP) {
//        playerHP_ = HP;
//    }
    void baseStatus(int res) {
        baseHP_ = res;
    }

    void drawGui();
    void drawGameOver();



private:
    int posX_, posY_;
    int playerHP_;
    int enemyCount_;
    int baseHP_;
    Sprite* sprite_;
    Sprite* enemyIconSprite_;
    Sprite* voidSprite_;
    std::vector<Sprite*> numeration_;
};
