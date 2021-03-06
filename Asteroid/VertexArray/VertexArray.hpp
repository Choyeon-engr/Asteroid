#pragma once

class VertexArray
{
public:
    VertexArray(const float* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices);
    ~VertexArray();
    
    void SetActive();
    
    unsigned int GetNumVertices() const { return mNumVertices; }
    unsigned int GetNumIndices() const { return mNumIndices; }
    
private:
    unsigned int mNumVertices;
    unsigned int mNumIndices;
    
    unsigned int mVertexBuffer;
    unsigned int mIndexBuffer;
    unsigned int mVertexArray;
};
