#pragma once

#include <GL/glew.h>
#include <string>

#include "CML.hpp"

using namespace std;

class Shader
{
public:
    Shader() : mVertexShaderID(0), mFragmentShaderID(0), mShaderProgramID(0) {}
    ~Shader() {}
    
    bool Load(const string& vertexName, const string& fragmentName);
    void Unload();
    
    void SetActive();
    
private:
    bool CompileShader(const string& fileName, GLenum shaderType, GLuint& outShader);
    
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();
    
    GLuint mVertexShaderID;
    GLuint mFragmentShaderID;
    GLuint mShaderProgramID;
};
