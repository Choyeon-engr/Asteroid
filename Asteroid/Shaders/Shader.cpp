#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>

#include "Shader.hpp"

bool Shader::Load(const string& vertexName, const string& fragmentName)
{
    if (!CompileShader(vertexName, GL_VERTEX_SHADER, mVertexShaderID) || !CompileShader(fragmentName, GL_FRAGMENT_SHADER, mFragmentShaderID))
        return false;
    
    mShaderProgramID = glCreateProgram();
    glAttachShader(mShaderProgramID, mVertexShaderID);
    glAttachShader(mShaderProgramID, mVertexShaderID);
    glLinkProgram(mShaderProgramID);
    
    if (!IsValidProgram())
        return false;
    
    return true;
}

void Shader::Unload()
{
    glDeleteProgram(mShaderProgramID);
    glDeleteShader(mVertexShaderID);
    glDeleteShader(mFragmentShaderID);
}

void Shader::SetActive()
{
    glUseProgram(mShaderProgramID);
}

bool Shader::CompileShader(const string& fileName, GLenum shaderType, GLuint& outShader)
{
    const string absolutePath = string("/Users/choyeon/Game/Asteroid/Asteroid") + fileName;
    ifstream shaderFile(absolutePath);
    if (shaderFile.is_open())
    {
        stringstream sstream;
        sstream << shaderFile.rdbuf();
        string contents = sstream.str();
        const char* contentsChar = contents.c_str();
        
        outShader = glCreateShader(shaderType);
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);
        
        if (!IsCompiled(outShader))
            return false;
    }
    else
        return false;
    
    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint status;
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compile Failed:\n%s", buffer);
        
        return false;
    }
    
    return true;
}

bool Shader::IsValidProgram()
{
    GLint status;
    
    glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        
        glGetShaderInfoLog(mShaderProgramID, 511, nullptr, buffer);
        SDL_Log("GLSL Link Status:\n%s", buffer);
        
        return false;
    }
    
    return true;
}
