#pragma once
#include <vector>
#include <cstdint>
#include "camera/camera.h"
#include "datatypes/datatypes.h"

class renderer {
private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int IBO = 0;
    
    void UploadDataToBuffers(const std::vector<GPUVertex>& vertexes, const std::vector<uint32_t>& indices);

    void ClearBuffers();
public:

    void Render(GLFWwindow* Window);
    
    void renderCamera(const camera& Camera);
};