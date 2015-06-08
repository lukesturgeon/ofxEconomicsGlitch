//
//  Tile.cpp
//  osxHighPerformanceVideoPlayerExample
//
//  Created by Peter Hudson on 03/06/2015.
//
//

#include "Tile.h"

Tile::Tile() {
}

void Tile::setPos(int i, int num, int numX, int numY, int srcW, int srcH, int dstW, int dstH) {
    
    //  int srcX, srcYy, srcW, srcH, dstX, dstY, dstW, dstH;
    
    sW = srcW / numX;
    sH = srcH / numY;
    dW = dstW / numX;
    dH = dstH / numY;
    int x = num % i;
    sX = x * sW;
    dX = x * dW;
    int y = i / numY;
    sY = y * sH;
    dY = y * dH;
    
}

void Tile::update() {
    
}

void Tile::draw() {
    
}