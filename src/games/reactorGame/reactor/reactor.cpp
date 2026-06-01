#include "reactor.h"
#include <vector>
#include <iostream>
#include <thread>



void Reactor::Start() {
    isRunning = true;
    workerThread = std::thread(&Reactor::tickLoop, this);
}

void Reactor::tickLoop() {
    while (isRunning) {
        tick();
        //TODO: sleep for a certen amount of time
    }
}

void Reactor::Stop() {
    isRunning = false;
    if (workerThread.joinable()) {
        workerThread.join();
    }
}



static tile emptyTile; 
tile& Reactor::get(int x, int y, int z) {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
        return emptyTile;
    }
    return grid[x + y * width + z * width * height];
}

void Reactor::initGrid(int x, int y, int z) {
    width = x;
    height = y;
    depth = z;
    grid.clear();
    grid.resize(width * height * depth);
}

void Reactor::tick() {
    for (int z = 0; z < depth; z++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                tile& Maintile = get(x,y,z);

                tile borderTiles[6];
                borderTiles[0] = get(x-1,y,z);
                borderTiles[1] = get(x+1,y,z);
                borderTiles[2] = get(x,y-1,z);
                borderTiles[3] = get(x,y+1,z);
                borderTiles[4] = get(x,y,z-1);
                borderTiles[5] = get(x,y,z+1);
            }
        }
    }
}