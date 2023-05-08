#include "../include/level.h"

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
}

Level::Level(RenderWindow* _window, View* _view, Font* _font, string _path){
    window = _window;
    view = _view;
    font = _font;
    path = _path;
    readMap(2);
    viewOffset = Vector2f(0, 0);
    turtle = new Turtle(path + DIR_DELIM + TEXTURES_DIR);
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
    ground -> draw(window);
    enemyList -> draw(window);
    babyList -> draw(window);
    window->draw(*(turtle->getSprite()));
    Vector2i pos;
    pos = getPosGrid(turtle->getSprite());
    // cout << "POS GRID: " << pos.x << " " << pos.y << endl;
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
    // cout << "YOHOO" << endl;
    gridPosList.push_back(GridItem(getPosGrid(turtle -> getSprite()), ENT_TURTLE, turtle -> getSprite()));
    vector<Sprite*> groundSprites = ground ->getSprites();
    // cout << "GROUNDSZ: " << groundSprites.size() << endl;
    // cout << "ENEMYSZ:" << enemyList -> enemies.size() << endl;
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
    // cout << "GridSz: " << gridPosList.size() << endl;
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
                        Enemy* enem = enemyList -> enemies[j - 1 - groundSprites.size() - babyList -> babies.size()];
                        handleEnemyImpact(enem);
                    }
                    if(gridPosList[j].type == ENT_BABY && !turtle -> isGhost()){
                        Baby* babe = babyList -> babies[j - 1];
                        babe -> manageTurtleImpact(turtle -> getSprite());
                    }
                }
                if(gridPosList[i].type == ENT_BABY){
                    Baby* babe = babyList -> babies[i - 1];
                    if(gridPosList[j].type == ENT_GROUND){
                        babe -> manageWallImpact(gridPosList[j].sprite);
                    }
                    if(!babe -> isActive()){
                        continue;
                    }
                    if(gridPosList[j].type == ENT_ENEMY1){
                        Enemy* enem = enemyList -> enemies[j - 1 - groundSprites.size() - babyList -> babies.size()];
                        babe -> die();
                        enem -> attack();
                    }
                }
            }
        }
    }
    gridPosList.clear();
    turtle->incrementMovement();
    setViewPos();
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

Level::~Level(){
    view -> setCenter(view -> getCenter() - viewOffset);
    delete turtle;
    delete ground;
    delete enemyList;
    delete babyList;
}
