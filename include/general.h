#ifndef GENERAL_H_
#define GENERAL_H_

#include <string>
#include <vector>
#include <unistd.h>
#include <cstdlib>
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int MAX_PATH_SIZE = 2048;
const int PERCENTAGE_AMOUNT = 100;
const int GRID_SIZE = 100;
const int NA = -1;
const float GRID_SIZEF = static_cast<float>(GRID_SIZE);
const std::string EXEC_LINK_PATH = "/proc/self/exe";
const std::string DIR_DELIM = "/";
const std::string PREV_DIR = "..";
using namespace std;
int percentage(int per, int amount);
int randomIntBetween(int l, int r);
string getExecutablePath();
string removeFinalTwoDirsFromPath(string path);
#endif // GENERAL_H_
