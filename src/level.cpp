#include "../include/level.h"
#include <SFML/System/Vector2.hpp>
#include <string>

int charToEntId(char c){
    int ans = NA;
    for(int i = 0; i < ENTITY_CNT; i++){
        if(c == ENTITY_CHAR[i]){
            ans = i;
            break;
        }
    }
    return ans;
}

GridItem::GridItem(Vector2i _pos, ENTITY _type, Sprite* _sprite){
    pos = _pos;
    type = _type;
    sprite = _sprite;
}

void Level::readMap(int ind){
    string name = path + DIR_DELIM + MAPS_DIR + DIR_DELIM + MAPS_PREFIX + NAME_DELIM + to_string(ind) + MAPS_FORMAT;
    ifstream inputFile(name);
    vector<string> readFile;
    string lineOfFile;
    rescued = 0;
    int w, h;
    w = h = 0;
    while(getline(inputFile, lineOfFile)){
        h++;
        readFile.push_back(lineOfFile);
        w = max(w, (int)lineOfFile.size());
    }
    inputFile.close();
    vector< vector<int> > vec;
    vector<int> line;
    for(int i = 0; i < w + 4; i++){
        line.push_back(NA);
    }
    vec.push_back(line);
    line.clear();
    line.push_back(NA);
    for(int i = 0; i < w + 2; i++){
        line.push_back(ENT_GROUND);
    }
    line.push_back(NA);
    vec.push_back(line);
    line.clear();
    for(int i = 0; i < h; i++){
        line.push_back(NA);
        line.push_back(ENT_GROUND);
        for(int j = 0; j < w; j++){
            if(j < (int)readFile[i].size()){
                line.push_back(charToEntId(readFile[i][j]));
            }
            else{
                line.push_back(NA);
            }
        }
        line.push_back(ENT_GROUND);
        line.push_back(NA);
        vec.push_back(line);
        line.clear();
    }
    line.push_back(NA);
    for(int i = 0; i < w + 2; i++){
        line.push_back(ENT_GROUND);
    }
    line.push_back(NA);
    vec.push_back(line);
    line.clear();
    for(int i = 0; i < w + 4; i++){
        line.push_back(NA);
    }
    vec.push_back(line);
    ground = new Ground(path, vec);
    enemyList = new EnemyList(path, vec);
    babyList = new BabyList(path, vec);
    portal = new Portal(path, vec);
    turtle = new Turtle(path, portal -> getSprite() -> getPosition());
    Vector2f turtPos = static_cast<Vector2f>(getPosWindow(turtle -> getSprite()));
    turtPos.x -= percentage(WIDTH, 50);
    turtPos.y -= percentage(HEIGHT, 50);
    viewOffset = turtPos;
    view -> setCenter(view -> getCenter() + viewOffset);
}

Level::Level(RenderWindow* _window, View* _view, Font* _font, string _path){
    window = _window;
    view = _view;
    font = _font;
    path = _path;
    finishLevels = false;
    msgText.setFont(*font);
    msgText.setCharacterSize(LEVEL_FONT_SZ);
    levelNum = 0;
    readMap(levelNum);
}

void Level::setViewPos(){
    Vector2i pos = getPosWindow(turtle -> getSprite());
    Vector2f offset(0, 0);
    int leftMargin = percentage(BOX_PERCENTAGE_LIMIT, WIDTH) + viewOffset.x;
    if(pos.x < leftMargin){
        offset.x = pos.x - leftMargin;
    }
    int rightMargin = percentage(PERCENTAGE_AMOUNT - BOX_PERCENTAGE_LIMIT, WIDTH) + viewOffset.x;
    if(pos.x > rightMargin){
        offset.x = pos.x - rightMargin;
    }
    int topMargin = percentage(BOX_PERCENTAGE_LIMIT, HEIGHT) + viewOffset.y;
    if(pos.y < topMargin){
        offset.y = pos.y - topMargin;
    }
    int bottomMargin = percentage(PERCENTAGE_AMOUNT - BOX_PERCENTAGE_LIMIT, HEIGHT) + viewOffset.y;
    if(pos.y > bottomMargin){
        offset.y = pos.y - bottomMargin;
    }
    view -> setCenter(view -> getCenter() + offset);
    viewOffset += offset;
}

void Level::draw(){
    window -> setView(*view);
    window -> draw(*(portal -> getSprite()));
    ground -> draw(window);
    enemyList -> draw(window);
    babyList -> draw(window);
    window->draw(*(turtle->getSprite()));
    Vector2i pos;
    pos = getPosGrid(turtle->getSprite());
    window -> setView(window -> getDefaultView());
}

void Level::handleEnemyImpact(Enemy *enem){
  if (enem->isGhost() || !enem->isVisible()) {
    return;
  }
  if (enem->isDead()) {
    if (turtle->isAttacking()) {
      enem->dieForGood();
    }
    return;
  }
  bool impactRes = turtle->manageEnemyImpact(enem -> getSprite());
  if (enem->canBeHurt() && impactRes) {
    enem->hurt();
  } else {
    turtle->hurt();
    enem->attack();
  }
}

void Level::incrementMovements(){
    gridPosList.push_back(GridItem(getPosGrid(turtle -> getSprite()), ENT_TURTLE, turtle -> getSprite()));
    gridPosList.push_back(GridItem(getPosGrid(portal -> getSprite()), ENT_PORTAL, portal -> getSprite()));
    vector<Sprite*> groundSprites = ground ->getSprites();
    for(int i = 0; i < (int)babyList -> babies.size(); i++){
        gridPosList.push_back(GridItem(getPosGrid(babyList -> babies[i] -> getSprite()), ENT_BABY, babyList -> babies[i] -> getSprite()));
        babyList -> incrementMovement(i);
    }
    for(int i = 0; i < (int)groundSprites.size(); i++){
        gridPosList.push_back(GridItem(getPosGrid(groundSprites[i]), ENT_GROUND, groundSprites[i]));
    }
    for(int i = 0; i < (int)enemyList -> enemies.size(); i++){
        gridPosList.push_back(GridItem(getPosGrid(enemyList -> enemies[i] -> getSprite()), ENT_ENEMY1, enemyList -> enemies[i] -> getSprite()));
        enemyList -> incrementMovement(i);
    }
    for(int i = 0; i < (int)gridPosList.size(); i++) {
        for(int j = i + 1; j < (int)gridPosList.size(); j++){
            if(gridPosList[i].type == gridPosList[j].type){
                continue;
            }
            if(areGridsAdjacent(gridPosList[i].pos, gridPosList[j].pos) &&
                areColliding(gridPosList[i].sprite, gridPosList[j].sprite)) {
                if(gridPosList[i].type == ENT_TURTLE){
                    if(gridPosList[j].type == ENT_GROUND){
                        turtle -> manageWallImpact(gridPosList[j].sprite);
                    }
                    if(gridPosList[j].type == ENT_ENEMY1 && !turtle -> isGhost()){
                        Enemy* enem = enemyList -> enemies[j - 2 - groundSprites.size() - babyList -> babies.size()];
                        handleEnemyImpact(enem);
                    }
                    if(gridPosList[j].type == ENT_BABY && !turtle -> isGhost()){
                        Baby* babe = babyList -> babies[j - 2];
                        babe -> manageTurtleImpact(turtle -> getSprite());
                    }
                }
                if(gridPosList[i].type == ENT_PORTAL){
                    if(gridPosList[j].type == ENT_BABY){
                        Baby* babe = babyList -> babies[j - 2];
                        if(babe -> isVisible()){
                            babe -> managePortalImpact();
                            rescued++;
                        }
                    }
                }
                if(gridPosList[i].type == ENT_BABY){
                    Baby* babe = babyList -> babies[i - 2];
                    if(gridPosList[j].type == ENT_GROUND){
                        babe -> manageWallImpact(gridPosList[j].sprite);
                    }
                    if(!babe -> isActive()){
                        continue;
                    }
                    if(gridPosList[j].type == ENT_ENEMY1){
                        Enemy* enem = enemyList -> enemies[j - 2 - groundSprites.size() - babyList -> babies.size()];
                        if(enem -> isDead() || !enem -> isVisible()){
                            continue;
                        }
                        babe -> die();
                        enem -> attack();
                    }
                }
            }
        }
    }
    gridPosList.clear();
    portal -> incrementMovement();
    turtle->incrementMovement();
    if(rescued == (int)babyList -> babies.size()){
        win();
    }
    if(turtle -> isDead()){
        lose();
    }
    setViewPos();
}

bool Level::isFinished(){
    return finishLevels;
}

void Level::lose(){
    loseMessage();
    tidyUp();
    readMap(levelNum);
}

void Level::win(){
    winMessage();
    if(levelNum + 1 < NUMBER_OF_LEVELS){
        tidyUp();
        levelNum++;
        readMap(levelNum);
    }
    else{
        finishLevels = true;
    }
}

void Level::fixTurtle(){
    turtle -> fixHorizontalMovement();
    turtle -> fixTurtle();
}

void Level::SpaceKeyPress(){
    turtle -> attack();
}

void Level::upKeyPress(){
    turtle -> jump();
}

void Level::rightKeyPress(){
    turtle -> moveRight();
}

void Level::leftKeyPress(){
    turtle -> moveLeft();
}

void Level::vKeyPress(){
    turtle -> hurt();
}

View* Level::getView(){
    return view;
}

void Level::tidyUp(){
    view -> setCenter(view -> getCenter() - viewOffset);
    delete turtle;
    delete ground;
    delete enemyList;
    delete babyList;
    delete portal;
}

void Level::textRender(){
    window -> clear(LEVEL_BACKGROUND_COLOR);
    window -> setView(*view);
    window -> draw(msgText);
    window -> setView(window -> getDefaultView());
    window -> display();
}

void Level::incrementMsg(){
    Clock tmpClock1, tmpClock2;
    while(tmpClock1.getElapsedTime() < MSG_TIME){
        if(tmpClock2.getElapsedTime() >= TICKING_TIME){
            tmpClock2.restart();
            Color tempCol = msgText.getFillColor();
            tempCol.a = min(COLOR_SIZE, tempCol.a + OPACITY_STEP);
            msgText.setFillColor(tempCol);
            textRender();
        }
    }
}

void Level::winMessage(){
    msgText.setString(WIN_MESSAGE + " ;) You Completed Level " + to_string(levelNum + 1));
    msgText.setFillColor(WIN_COLOR);
    fixTextPosition();
    incrementMsg();
}

void Level::restartCurrentLevel(){
    tidyUp();
    readMap(levelNum);
}

void Level::loseMessage(){
    msgText.setString(LOSE_MESSAGE);
    msgText.setFillColor(LOSE_COLOR);
    fixTextPosition();
    incrementMsg();
}

void Level::fixTextPosition(){
    FloatRect rect = msgText.getLocalBounds();
    msgText.setPosition(viewOffset.x + (WIDTH - rect.width) / 2, viewOffset.y + (HEIGHT - rect.height) / 2);
}

Level::~Level(){
    tidyUp();
}
