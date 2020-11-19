#pragma once

#include <GL/glew.h>
#include <string>

#include "CML.hpp"

using namespace std;

class Shader
{
public:
    Shader() : mVertexShader(0), mFragmentShader(0), mShaderProgram(0) {}
    ~Shader() {}
    
    bool Load(const string& vertexName, const string& fragmentName);
    void Unload();
    
    void SetActive();
    
    void SetMatrixUniform(const char* name, const CML::Matrix4D& matrix);
    
private:
    bool CompileShader(const string& fileName, GLenum shaderType, GLuint& outShader);
    
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();
    
    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mShaderProgram;
};
