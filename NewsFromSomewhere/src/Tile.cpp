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
        
    sW = float(srcW) / numX;
    sH = float(srcH) / numY;
    dW = float(dstW) / numX;
    dH = float(dstH) / numY;
    
    float x = i % numX;
    sX = x * sW;
    dX = x * dW;
    
    float y = i / numX;
    sY = y * sH;
    dY = y * dH;
    
}