#include "../include/sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

Texture createTrimmedTexture(const Image& image){
   Vector2u size = image.getSize();

    IntRect rect;
    bool flag = false;
    for (unsigned int x = 0; x < size.x; x++){
        if(flag){
            break;
        }
        for (unsigned int y = 0; y < size.y; y++){
            if (image.getPixel(x, y).a != 0){
                rect.left = x;
                flag = true;
                break;
            }
        }
    }
    flag = false;
    for (unsigned int y = 0; y < size.y; y++){
        if(flag){
            break;
        }
        for (unsigned int x = rect.left; x < size.x; x++){
            if (image.getPixel(x, y).a != 0){
                rect.top = y;
                flag = true;
                break;
            }
        }
    }
    flag = false;
    for (int x = size.x - 1; x >= static_cast<int>(rect.left); x--){
        if(flag){
            break;
        }
        for (int y = size.y - 1; y >= static_cast<int>(rect.top); y--){
            if (image.getPixel(x, y).a != 0){
                rect.width = x - rect.left + 1;
                flag = true;
                break;
            }
        }
    }
    flag = false;
    for (int y = size.y - 1; y >= static_cast<int>(rect.top); y--){
        if(flag){
            break;
        }
        for (int x = size.x - 1; x >= static_cast<int>(rect.left); x--){
            if (image.getPixel(x, y).a != 0){
                rect.height = y - rect.top + 1;
                flag = true;
                break;
            }
        }
    }

    Texture texture;
    texture.loadFromImage(image, rect);
    return texture;
}

void loadTrimmedTexture(Texture* texture, string fileName){
    Image img;
    img.loadFromFile(fileName);
    *(texture) = createTrimmedTexture(img);
}

void fitTextureInSprite(Sprite* sprite, Texture* texture){
    sprite -> setTexture(*texture);
    Vector2u textureSz = texture -> getSize();
    sprite -> setTextureRect(IntRect(0, 0, textureSz.x, textureSz.y));
    FloatRect bounds = sprite -> getLocalBounds();
    sprite -> setOrigin(bounds.width / 2, bounds.height / 2);
}

void flipSprite(Sprite* sprite){
    Vector2f scale = sprite -> getScale();
    sprite -> setScale(-scale.x, scale.y);
}

Vector2i getPosWindow(Sprite* sprite){
    return (static_cast<Vector2i>(sprite -> getPosition()));
}

Vector2f getPosView(Sprite* sprite, RenderWindow* window){
    return window -> mapPixelToCoords(static_cast<Vector2i>(sprite -> getPosition()));
}

Vector2i getPosGrid(Sprite* sprite){
    Vector2i grid = getPosWindow(sprite);
    grid.x /= GRID_SIZE;
    grid.y /= GRID_SIZE;
    return grid;
}

bool areColliding(Sprite *sprite1, Sprite *sprite2){
    return sprite1 -> getGlobalBounds().intersects(sprite2 -> getGlobalBounds());
}

int whichDirectionAreColliding(Sprite *sprite1, Sprite *sprite2){
    FloatRect bound1 = sprite1 -> getGlobalBounds();
    FloatRect bound2 = sprite2 -> getGlobalBounds();
    float sides[GRID_DIR_CNT];

    sides[BOTTOM] = bound2.top + bound2.height;
    sides[RIGHT] = bound2.left + bound2.width;
    sides[TOP] = bound2.top;
    sides[LEFT] = bound2.left;
    int intersectionSize[GRID_DIR_CNT];
    for(int i = 0; i < GRID_DIR_CNT; i++){
        intersectionSize[i] = 0;
    }
    for(int i = sides[LEFT]; i <= sides[RIGHT]; i++){
        intersectionSize[BOTTOM] += bound1.contains(i, sides[BOTTOM]);
        intersectionSize[TOP] += bound1.contains(i, sides[TOP]);
    }
    for(int i = sides[TOP]; i <= sides[BOTTOM]; i++){
        intersectionSize[RIGHT] += bound1.contains(sides[RIGHT], i);
        intersectionSize[LEFT] += bound1.contains(sides[LEFT], i);
    }
    int mx = -INF;
    int mxInd = NA;
    for(int i = 0; i < GRID_DIR_CNT; i++){
        if(intersectionSize[i] > mx){
            mx = intersectionSize[i];
            mxInd = i;
        }
    }
    return mxInd;
}
