//
//  Tile.h
//  osxHighPerformanceVideoPlayerExample
//
//  Created by Peter Hudson on 03/06/2015.
//
//

#pragma once
#ifndef Tile_h
#define Tile_h

#include "ofMain.h"

class Tile {
    
public:
    
    Tile();
    void update();
    void draw();
    void setPos(int i, int num, int numX, int numY, int srcW, int srcH, int dstW, int dstH);
    int sX, sY, sW, sH, dX, dY, dW, dH;
    
    
private:
    
    
};


#endif