#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    Shader(const Shader& otherShader) = delete;
    Shader& operator = (const Shader& otherShader) = delete;

    unsigned int GetID() const { return m_ID; }
    // use/activate the shader
    void Use() const;
    // utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;


private:
    unsigned int m_ID;
};

#endif // SHADER_H