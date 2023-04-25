#ifndef GAME_H_
#define GAME_H_


#include "general.h"
#include "turtle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

const int FRAME_RATE_LIMIT = 120;
const std::string GAME_TITLE = "Turtix";
const std::string TEXTURES_DIR = "resources/textures";
using namespace sf;
using namespace std;

class Game{
    private:
        bool endGame;
        RenderWindow *window;
        Clock clock;
        float dt;
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
        Game();
        virtual ~Game();
        bool isRunning();
        void update();
        void render();
        void handleTime();
};


#endif // GAME_H_