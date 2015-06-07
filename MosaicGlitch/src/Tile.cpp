//
//  Tile.cpp
//  
//
//  Created by Peter Hudson on 03/06/2015.
//
//

#include "Tile.h"

Tile::Tile() {
}

void Tile::setPos(int i, int num, int numX, int numY, int srcW, int srcH, int dstW, int dstH) {
        
    sW = srcW / numX;
    sH = srcH / numY;
    dW = dstW / numX;
    dH = dstH / numY;
    
    float x = i % numX;
    sX = x * sW;
    dX = x * dW;
    
    float y = i / numX;
    sY = y * sH;
    dY = y * dH;
    
}

void Tile::update() {
    
    
}

void Tile::draw() {
    
}