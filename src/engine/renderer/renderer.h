#include ""

class renderer {
private:
    unsigned int VAO;
    unsigned int IBO;
    
    
    void UploadDataToBuffers(GPUVertex vertexes, uint32_t indices);
public:
    void renderCamera(camera Camera);
}