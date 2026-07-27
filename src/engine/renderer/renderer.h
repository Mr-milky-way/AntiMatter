#pragma once
#include <vector>
#include <cstdint>

class renderer {
private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int IBO = 0;
    
    void UploadDataToBuffers(const std::vector<GPUVertex>& vertexes, const std::vector<uint32_t>& indices);
public:

    renderer();
    ~renderer();


    
    void renderCamera(const camera& Camera);
};