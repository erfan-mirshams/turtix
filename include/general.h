#ifndef GENERAL_H_
#define GENERAL_H_

#include <string>
#include <unistd.h>
#include <cstdlib>
const int MAX_PATH_SIZE = 2048;
const int PERCENTAGE_AMOUNT = 100;
const std::string EXEC_LINK_PATH = "/proc/self/exe";
using namespace std;
int percentage(int per, int amount);
int randomIntBetween(int l, int r);
string getExecutablePath();
#endif // GENERAL_H_
