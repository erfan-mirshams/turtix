#include "../include/general.h"
#include <string>

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

string removeFinalTwoDirsFromPath(string path){
    vector<int> inds;
    for(int i = 0; i < (int)path.size(); i++){
        if(path[i] == '/'){
            inds.push_back(i);
        }
    }
    return path.substr(0, inds[(int)inds.size() - 2]);
}

int calMod(int a, int b){
    a += b;
    return (a % b);
}

string intToBinaryString(int x){
    string ans = "";
    for(int i = 0; i < GRID_DIR_CNT; i++){
        ans = to_string(x & 1) + ans;
        x >>= 1;
    }
    return ans;
}

bool areGridsAdjacent(Vector2i v, Vector2i w){
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(v.x + i == w.x && v.y + j == w.y){
                return true;
            }
        }
    }
    return false;
}
