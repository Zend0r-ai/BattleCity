#include "engine.h"

Engine::Engine(int width, int height) {
    screenSizeWidth_ = width, screenSizeHeight_ = height;
}

Engine::~Engine() {
    delete player;
    delete playerBullet;
    destroySprite(void_);
    delete base;
    delete gui_;
    delete extraLife;
    for(auto it : allObj) delete it;
    allObj.clear();
    for(auto it : enemyList) delete it;
    enemyList.clear();
}


void Engine::PreInit(int &width, int &height, bool &fullscreen) {
    width = screenSizeWidth_;
    height = screenSizeHeight_;
    fullscreen = true;

}

bool Engine::Init() {
    getScreenSize(screenSizeWidth_, screenSizeHeight_);
    std::cout << screenSizeWidth_ << " " << screenSizeHeight_ << endl;
    showCursor(false);
    gui_ = new Gui(screenSizeWidth_ / 2 + (8 * 26) / 2, screenSizeHeight_ / 2 - (8 * 26) / 2);
    void_ = createSprite("../../app/resources/Void.TGA");
    player = new Player(screenSizeWidth_ / 2 - 32 , screenSizeHeight_ / 2 + (8 * 20) / 2, FRKey::UP);
    playerBullet = new Bullet(player->collisionModel.x,
                              player->collisionModel.y , player->getDirection(),
                              ModelType::PLAYER_BULLET, 1, player);
    base = new Eagle(screenSizeWidth_ / 2 - 8, screenSizeHeight_ / 2 + (8 * 22) / 2);
    allObj.push_back(player);
    allObj.push_back(playerBullet);
    allObj.push_back(base);
    extraLife = new Booster(0,0);

    string stage_1 =
            "00000000000000000000000000"
            "00000000000000000000000000"
            "00110011001100110011001100"
            "00110011001100110011001100"
            "00110011001100110011001100"
            "00110011001122110011001100"
            "00110011001122110011001100"
            "00110011001100110011001100"
            "00110011000000000011001100"
            "00110011000000000011001100"
            "00000000001100110000000000"
            "00000000001100110000000000"
            "11001111000000000011110011"
            "22001111000000000011110022"
            "00000000001100110000000000"
            "00000000001111110000000000"
            "00000000001111110000000000"
            "00000000001100110000000000"
            "00110011001100110011001100"
            "00110011001100110011001100"
            "00110011001100110011001100"
            "00110011000000000011001100"
            "00110011000000000011001100"
            "00110011000111100011001100"
            "00000000000100100000000000"
            "00000000000100100000000000";

    string enemiesList = "11000000000000000000";
    readEnemyList(enemiesList);
    readMap(stage_1);

    return true;
}

void Engine::Close() {
}

bool Engine::Tick() {
    frameCount++;
    spawnEnemies();
    if(frameCount == 500)
        frameCount = 0;
    // draw map and gui

    for(int i = 0; i < 13; ++i) {
        for(int j = 0; j < 13; ++j) {
            drawSprite(void_, (screenSizeWidth_ / 2 - (16 * 13) / 2) + j * 16, (screenSizeHeight_  / 2 - (16 * 13) / 2) + i * 16);
        }
    }
    if(isMove) {
        player->rotate(curPlayerDirection);
        player->move(curPlayerDirection, frameCount);
    }
    playerBullet->move(playerBullet->getDirection(), frameCount);

    collisionDetection();

    gui_->setPlayerHP(player->getHP());
    int count = 0;
    for(auto& it : enemyList) {
        if(it->getIsAlive())
            count++;
    }
    gui_->setEnemyCount(count);
    gui_->drawGui();
    drawFrame();
    if(base->getStatus() == false || !player->getHP() || count == 0) {
        gui_->baseStatus(0);
        return true;
    }
    return false;
}

void Engine::onMouseMove(int x, int y, int xrelative, int yrelative) {
}

void Engine::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    if(button == FRMouseButton::LEFT && player->isShootable()) {
        playerBullet->removeToOwner();
        playerBullet->setDirection(player->getDirection());
        playerBullet->setIsVisible(true);
        player->setIsShootable(false);
    }
}

void Engine::onKeyPressed(FRKey k) {

    isMove = true;
    curPlayerDirection = k;

}

void Engine::onKeyReleased(FRKey k) {
        isMove = false;
}

const char *Engine::GetTitle() {
    return "Battle City";
}

void Engine::readMap(const string& map) {
    for(int i = 0; i < 26; ++i) {
        for(int j = 0; j < 26; ++j) {
            if(map.at(i * 26 + j) == '1')
                allObj.push_back(new BrickWall((screenSizeWidth_ / 2 - 104) + j * 8,
                                                (screenSizeHeight_  / 2 - 104) + i * 8));
            else if(map.at(i * 26 + j) == '2')
                allObj.push_back(new SteelWall((screenSizeWidth_ / 2 - 104) + j * 8,
                                                (screenSizeHeight_  / 2 - 104) + i * 8));
        }
    }
}

void Engine::readEnemyList(const string& list) {

    for(int i = 0; i < 20; ++i) {
        Enemy* enemy;
        if(list.at(i) == 1)
            enemy = new FastEnemy(0, 0, false);
        else
            enemy = new BasicEnemy(0, 0, false);
        allObj.push_back(enemy);
        allObj.push_back(new Bullet(enemy->collisionModel.x, enemy->collisionModel.y, enemy->getDirection(),
                                    ModelType::ENEMY_BULLET, enemy->getBulletSpeed(), enemy));
        enemyList.push_back(enemy);
    }

    random_shuffle(enemyList.begin(), enemyList.end());

    enemyList.at(3)->setBoosterAvailable(true);
    enemyList.at(10)->setBoosterAvailable(true);
    enemyList.at(17)->setBoosterAvailable(true);
}

void Engine::collisionDetection() {
    for (auto &item1 : allObj) {
        if (item1->borderCollision()) {
            switch (item1->type_) {
                case ModelType::PLAYER : {
                    auto player = dynamic_cast<Player *>(item1);
                    player->ifBorderCollisionDetected();
                    break;
                }
                case ModelType::ENEMY : {
                    auto enemy = dynamic_cast<Enemy *>(item1);
                    enemy->ifBorderCollisionDetected();
                    break;
                }
                case ModelType::PLAYER_BULLET : {
                    auto bullet = dynamic_cast<Bullet *>(item1);
                    bullet->ifBorderCollisionDetected();
                    break;
                }
                case ModelType::ENEMY_BULLET : {
                    auto bullet = dynamic_cast<Bullet *>(item1);
                    bullet->ifBorderCollisionDetected();
                    break;
                }
            }
        }
        for (auto &item2 : allObj) {
            if (&item1 != &item2 && item1->getIsVisible() && item2->getIsVisible()) {

                if (item1->checkCollision(item2)) {
                    switch (item1->type_) {
                        case ModelType::PLAYER : {
                            auto player = dynamic_cast<Player *>(item1);
                            player->ifCollisionDetected(item2);
                            break;
                        }
                        case ModelType::ENEMY : {
                            auto enemy = dynamic_cast<Enemy *>(item1);
                            enemy->ifCollisionDetected(item2);
                            break;
                        }
                        case ModelType::PLAYER_BULLET : {
                            auto bullet = dynamic_cast<Bullet *>(item1);
                            bullet->ifCollisionDetected(item2);
                            break;
                        }
                        case ModelType::ENEMY_BULLET : {
                            auto bullet = dynamic_cast<Bullet *>(item1);
                            bullet->ifCollisionDetected(item2);
                            break;
                        }
                        case ModelType::WALL : {
                            auto wall = dynamic_cast<Wall *>(item1);
                            wall->ifCollisionDetected(item2);
                            break;
                        }
                        case ModelType::EAGLE : {
                            auto eagle = dynamic_cast<Eagle *>(item1);
                            eagle->ifCollisionDetected(item2);
                            break;
                        }
                        case ModelType::EXTRA_LIFE : {
                            auto booster = dynamic_cast<Booster *>(item1);
                            booster->ifCollisionDetected(item2);
                            break;
                        }
                    }
                }
            }
        }
        if (item1->borderCollision()) {
            if (item1->type_ == ModelType::ENEMY_BULLET || item1->type_ == ModelType::PLAYER_BULLET) {
                auto bullet = dynamic_cast<Bullet *>(item1);
                bullet->ifBorderCollisionDetected();
            }
            if (item1->type_ == ModelType::ENEMY) {
                auto enemy = dynamic_cast<Enemy *>(item1);
                enemy->ifBorderCollisionDetected();
            }
            if (item1->type_ == ModelType::PLAYER) {
                auto player = dynamic_cast<Player *>(item1);
                player->ifBorderCollisionDetected();
            }
        } else {
            if (item1->type_ == ModelType::ENEMY) {
                auto enemy = dynamic_cast<Enemy *>(item1);
                if(enemy->getIsVisible()){
                    if (frameCount % 20 == 0 )
                        enemy->rotate(enemy->chooseDirection());
                    enemy->move(enemy->getDirection(), frameCount);
                }
            }
            if (item1->type_ == ModelType::PLAYER) {
                auto player = dynamic_cast<Player *>(item1);

                if (isMove) {
                    player->rotate(curPlayerDirection);
                    player->move(curPlayerDirection, frameCount);
                }
            }
            if (item1->type_ == ModelType::ENEMY_BULLET) {
                auto bullet = dynamic_cast<Bullet *>(item1);
                if (bullet->getOwner()->getIsVisible() && !bullet->getIsVisible()) {
                    bullet->setIsVisible(true);
                    bullet->collisionModel = bullet->getOwner()->collisionModel;
                }
                if (!bullet->getOwner()->getIsVisible() && bullet->getIsVisible()) bullet->setIsVisible(false);

                bullet->move(bullet->getDirection(), frameCount);
            }
            if (item1->type_ == ModelType::PLAYER_BULLET) {
                playerBullet->move(playerBullet->getDirection(), frameCount);
            }
        }
    }
}

void Engine::spawnEnemies() {
    if(frameCount % 250 != 0)
        return;

    for(auto& it : enemyList) {
        if(!it->getIsVisible() && it->getIsAlive()){
            int pos;

            do {
                int pos = rand() % 13;
                it->collisionModel.x = screenSizeWidth_ / 2 - 104 + pos * 16;
                it->collisionModel.y = screenSizeHeight_ / 2 - 104;
            } while(it->checkCollision(player, it->getDirection()));

            it->setIsVisible(true);
            return;
        }
    }
}

void Engine::drawFrame() {
    for(auto& it : allObj) {
        if(it->getIsVisible())
            it->draw();
    }
}
