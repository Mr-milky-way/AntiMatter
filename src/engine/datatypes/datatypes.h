#include <cstdint>
#include <map>
#pragma once


//Vectors (prolly a better way to do this)


struct vector2Float {
    float x,y;
};

//VECTOR 3 ------------
struct vector3Float {
    float x,y,z;
};


struct vector3uint8 {
    uint8_t x,y,z;
};

struct vector3int8 {
    int8_t x,y,z;
};

struct vector3uint16 {
    uint16_t x,y,z;
};

struct vector3int16 {
    int16_t x,y,z;
};

struct vector3uint32 {
    uint32_t x,y,z;
};

struct vector3int32 {
    int32_t x,y,z;
};

struct vector3uint64 {
    uint64_t x,y,z;
};

struct vector3int64 {
    int64_t x,y,z;
};


// 3d Rendering Stuff
// Maxes: 256 Meshes per model (basicly Textures)
// 65,535 (UINT 16) meshes (Most likely more than needed)
// 4 billion faces MAX
// 65,535 different materials

struct Model {
    uint16_t FirstMesh;
    uint8_t meshCount;
};

struct Material {
    std::map<uint8_t, uint32_t> texture;
    uint32_t shader;
};

struct mesh {
    uint32_t firstFace;
    uint32_t numberOfFaces;
    uint16_t MaterialIndex;
};

struct face {
    uint32_t vertexes[3];
    uint32_t normals[3];
    uint32_t uvs[3];
};


struct GPUVertex {
    vector3Float position;
    vector3Float normal;
    vector3Float tangent;
    vector2Float uv;
};

struct RuntimeMesh {
    uint32_t baseVertex;
    uint32_t startIndex;
    uint32_t indexCount;
    uint16_t materialIndex;
};