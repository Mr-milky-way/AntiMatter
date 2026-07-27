#include <vector>
#include <cstdint>
#include <thread>
#include <atomic>

#pragma once
enum class tileTypes : uint8_t {
    Empty,
    Fuel,
    ControlRod,
    Coolant,
    Pipe
};

struct tile {
    tileTypes type;

    float temp = 21; // in C
    float emissivity = 0; // appplied on creation

    float percentWater = 0;
    float percentGas = 0;
    float reactivity = 0;
    float specificHeat = 0;
    float mass = 0;

    tile() : type(tileTypes::Empty) {}


    tile(tileTypes t, float tileMass) : type(t), mass(tileMass) {
        switch (type) {
            case tileTypes::Fuel:       
                emissivity = 0.85f; 
                specificHeat = 0.30f;
                break; 
            case tileTypes::ControlRod: 
                emissivity = 0.80f; 
                specificHeat = 1.21f;
                break; 
            case tileTypes::Coolant:    
                emissivity = 0.90f; 
                specificHeat = 4.184f;
                break; 
            case tileTypes::Pipe:       
                emissivity = 0.30f; 
                specificHeat = 0.50f;
                break; 
            case tileTypes::Empty: //no heat transfer or anything     
                emissivity = 0.00f; 
                //specificHeat = 1.00f;
                break;
        }
    }
};

class Reactor{

private:
    std::thread workerThread;
    std::atomic<bool> isRunning{false};


public: 



    void Start();
    void Stop();
    void tickLoop();
    std::vector<tile> grid;
    int width, height, depth;


    void initGrid(int x, int y, int z);

    tile& get(int x, int y, int z);

    void tick();
};