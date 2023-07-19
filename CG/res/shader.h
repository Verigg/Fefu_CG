#pragma once
#include "Includes.h"
#include "utils/shaderloader.cpp"

class Shader
{
public:
    GLuint id;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
        this->id = LoadShaders(vertexPath, fragmentPath);
    }

    void Use() {
        glUseProgram(this->id);
    }

    void SetMat4(std::string type, const Mat4& mat) {
        Mat4 res = Mat4(mat);
        glUniformMatrix4fv(glGetUniformLocation(id, type.c_str()), 1, GL_FALSE, &res[0][0]);
    }

    void SetVec3(const std::string unif, const Vec3& data) {
        Vec3 res = Vec3(data.x, data.y, data.z);
        glUniform3fv(glGetUniformLocation(id, unif.c_str()), 1, &res[0]);
    }

    void SetInt(const std::string unif, int data) {
        glUniform1i(glGetUniformLocation(id, unif.c_str()), data);
    }

    void SetFloat(const std::string unif, float data) {
        glUniform1f(glGetUniformLocation(id, unif.c_str()), data);
    }



};