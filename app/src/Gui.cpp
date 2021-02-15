#include "Gui.h"
#include <iostream>

//Gui::Gui(int playerHP, int posX, int posY) :
//            playerHP_(playerHP), posX_(posX), posY_(posY), enemyCount_(20), baseHP_(1) {
Gui::Gui(int posX, int posY) : posX_(posX), posY_(posY) {
    sprite_ = createSprite("../../app/resources/GUI.tga");
    voidSprite_ = createSprite("../../app/resources/GrayVoid.TGA");

    numeration_.push_back(createSprite("../../app/resources/0.TGA"));
    numeration_.push_back(createSprite("../../app/resources/1.TGA"));
    numeration_.push_back(createSprite("../../app/resources/2.TGA"));
    numeration_.push_back(createSprite("../../app/resources/3.TGA"));
    numeration_.push_back(createSprite("../../app/resources/4.TGA"));
    numeration_.push_back(createSprite("../../app/resources/5.TGA"));
    numeration_.push_back(createSprite("../../app/resources/6.TGA"));
    numeration_.push_back(createSprite("../../app/resources/7.TGA"));
    numeration_.push_back(createSprite("../../app/resources/8.TGA"));
    numeration_.push_back(createSprite("../../app/resources/9.TGA"));

    enemyIconSprite_ = createSprite("../../app/resources/EnemyIcon.TGA");
    playerHP_ = 2;
    enemyCount_ = 20;
    baseHP_ = 1;
}

void Gui::drawGui() {

    drawSprite(sprite_, posX_, posY_);
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 10; ++j) {
            if(enemyCount_ > j * 2 + i){
                drawSprite(enemyIconSprite_, posX_ + 8 * i + 8, posY_ + 8 * j + 24);
            } else {

                drawSprite(voidSprite_, posX_ + 8 * i + 8, posY_ + 8 * j + 24);
            }
        }
    }

    drawSprite(numeration_.at(playerHP_), posX_ + 16, posY_ + 144);

    drawSprite(numeration_.at(0), posX_ + 16, posY_ + 168);
    drawSprite(numeration_.at(baseHP_ / 10),posX_ + 8 , posY_ + 200);
    drawSprite(numeration_.at(baseHP_ % 10),posX_ + 16 , posY_ + 200);
//    for(int i = 0; i < 20; ++i) {
//        if(i < enemyCount_) {
//            if(i % 2 == 0)
//                drawSprite(enemyIconSprite_, posX_ + 8, posY_ + 8 * i);
//            else
//                drawSprite(enemyIconSprite_, posX_ + 16, posY_ + 8 * i - 1);
//        }
//
//    }
}

void Gui::drawGameOver() {

}
