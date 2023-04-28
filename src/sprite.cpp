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
