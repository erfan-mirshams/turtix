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
    for(int i = 0; i < w + 2; i++){
        line.push_back(NA);
    }
    vec.push_back(line);
    line.clear();
    for(int i = 0; i < h; i++){
        line.push_back(NA);
        for(int j = 0; j < w; j++){
            if(j < (int)readFile[i].size()){
                line.push_back(charToEntId(readFile[i][j]));
            }
            else{
                line.push_back(NA);
            }
        }
        line.push_back(NA);
        vec.push_back(line);
        line.clear();
    }
    for(int i = 0; i < w + 2; i++){
        line.push_back(NA);
    }
    vec.push_back(line);
    ground = new Ground(path, vec);
}

Level::Level(RenderWindow* _window, View* _view, Font* _font, string _path){
    window = _window;
    view = _view;
    font = _font;
    path = _path;
    readMap(1);
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
    window->draw(*(turtle->getSprite()));
    Vector2i pos;
    pos = getPosGrid(turtle->getSprite());
    // cout << "POS GRID: " << pos.x << " " << pos.y << endl;
    window -> setView(window -> getDefaultView());
}

void Level::incrementMovements(){
    vector<Sprite*> groundSprites = ground ->getSprites();
    for(int i = 0; i < (int)groundSprites.size(); i++){
        if(areColliding(turtle -> getSprite(), groundSprites[i])){
            turtle -> manageWallImpact(groundSprites[i]);
        }
    }
    turtle -> incrementMovement();
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
}
