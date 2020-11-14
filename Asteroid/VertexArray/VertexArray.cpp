#include <GL/glew.h>

#include "VertexArray.hpp"

VertexArray::VertexArray(const float* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices)
: mNumVertices(numVertices), mNumIndices(numIndices)
{
    glGenVertexArrays(1, &mVertexArrayID);
    glBindVertexArray(mVertexArrayID);
    
    glGenBuffers(1, &mIndexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexArrayID);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &mIndexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &mVertexBufferID);
    glDeleteBuffers(1, &mIndexBufferID);
    glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::SetActive()
{
    glBindVertexArray(mVertexArrayID);
}
