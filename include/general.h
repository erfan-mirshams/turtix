#ifndef GENERAL_H_
#define GENERAL_H_

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int MAX_PATH_SIZE = 2048;
const int PERCENTAGE_AMOUNT = 100;
const int BOX_PERCENTAGE_LIMIT = 25;
const int GRID_SIZE = 100;
const int GRID_DIR_CNT = 4;
const int DIRX[GRID_DIR_CNT] = {0, 1, 0, -1};
const int DIRY[GRID_DIR_CNT] = {1, 0, -1, 0};
const int NA = -1;
const float GRID_SIZEF = static_cast<float>(GRID_SIZE);
const float INF = 1e6;
const sf::Time TICKING_TIME = sf::milliseconds(70);
const sf::Time LEVEL_TIMEOUT = sf::seconds(0.75);
const std::string EXEC_LINK_PATH = "/proc/self/exe";
const std::string DIR_DELIM = "/";
const std::string PREV_DIR = "..";
const std::string NAME_DELIM = "-";
const std::string TEXTURES_DIR = "textures";
enum ENTITY{ENT_TURTLE, ENT_GROUND, ENT_PORTAL, ENT_ENEMY1, ENT_ENEMY2, ENT_BABY, ENT_GEM, ENT_STAR, ENT_MOVING_BLOCK, ENT_BLADE, ENT_BARRIER};
enum DIRECTION {BOTTOM, RIGHT, TOP, LEFT};
using namespace sf;
using namespace std;
int calMod(int a, int b);
int percentage(int per, int amount);
int randomIntBetween(int l, int r);
string getExecutablePath();
string removeFinalTwoDirsFromPath(string path);
string intToBinaryString(int x);
bool areGridsAdjacent(Vector2i v, Vector2i w);
#endif // GENERAL_H_
