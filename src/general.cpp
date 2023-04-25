#include "../include/general.h"

int percentage(int per, int amount){
    return (amount * per) / PERCENTAGE_AMOUNT;
}

int randomIntBetween(int l, int r){
    int num = rand();
    int x = r - l + 1;
    num %= x;
    num += l;
    return num;
}

string getExecutablePath() {
    char path[MAX_PATH_SIZE];
    ssize_t count = readlink(EXEC_LINK_PATH.c_str(), path, sizeof(path));
    if (count != -1) {
        path[count] = '\0';
        return string(path);
    }
    return "";
}
