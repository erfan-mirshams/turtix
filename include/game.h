#ifndef GAME_H_
#define GAME_H_


#include "general.h"
#include "turtle.h"

const int FRAME_RATE_LIMIT = 120;
const std::string GAME_TITLE = "Turtix";
const std::string TEXTURES_DIR = "resources/textures";
using namespace sf;
using namespace std;

class Game{
    private:
        bool endGame;
        RenderWindow *window;
        VideoMode videoMode;
        View view;
        string path;
        Event sfmlEvent;
        void initVariables();
        void initWindow();
        void close();
        void pollEvents();
        void draw(RenderTarget *target, Sprite sprite);
        bool hasTimePassed();
        Turtle *turtle; // temp
    public:
        bool keyPressed;
        Game();
        virtual ~Game();
        bool isRunning();
        void update();
        void render();
        void handleTime();
        void turnOnKeyPress();
        void turnOffKeyPress();
};


#endif // GAME_H_
