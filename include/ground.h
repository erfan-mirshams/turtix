#ifndef GROUND_H_
#define GROUND_H_

#include "general.h"
#include "sprite.h"

const int GROUND_CNT = 16;
const string GROUND_DIR = "ground";
const string GROUND_PREFIX = "ground";
const string GROUND_FORMAT = ".png";

class Ground{
    private:
    vector<Texture*> textures;
    vector<Sprite*> sprites;
    string path;
    public:
    Ground(string _path, vector< vector<int> > mp);
    void loadTextures();
    void draw(RenderWindow* window);
    virtual ~Ground();
    vector<Sprite*> getSprites();
};

#endif // GROUND_H_
