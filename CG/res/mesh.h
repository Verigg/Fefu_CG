#pragma once

#include "utils/modelloader.cpp"
#include "shader.h"
#include "camera.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"


class Mesh {
public:
    GLuint size;

    Mesh(const GLchar* obj_path) {
        Vertex vertex = loadOBJ(obj_path);
        size = vertex.indexes.size();


		vertex_buffer vertices(vertex.vertices);
        vertices.Bind();
        vao.Bind();
        vao.AttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        vertex_buffer uvs(vertex.uvs);
        uvs.Bind();
        vao.Bind();
        vao.AttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        vertex_buffer normals(vertex.normals);
        normals.Bind();
        vao.Bind();
        vao.AttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        index_buffer indexes(vertex.indexes);
        indexes.Bind();
        vao.Bind();

	}

    void Draw(Shader shader, camera& camera, Vec3 position) {
        shader.Use();
        shader.SetMat4("view", camera.GetViewMatrix());
        shader.SetMat4("projection", camera.GetProjectionMatrix());

        vao.Bind();
        Mat4 model(1.0f);
        model = model.translate(position);
        shader.SetMat4("model", model);
        //glDrawArrays(GL_TRIANGLES, 0, size);
        glDrawElements(
            GL_TRIANGLES,      
            size,    
            GL_UNSIGNED_SHORT,   
            (void*)0           
        );
    }

    void Draw(Shader shader, camera& camera, Vec3 position, float angle, Vec3 rotate) {
        shader.Use();
        shader.SetMat4("view", camera.GetViewMatrix());
        shader.SetMat4("projection", camera.GetProjectionMatrix());

        vao.Bind();
        Mat4 model(1.0f);
        model = model.translate(position);
        model = model.rotate(angle, rotate);
        shader.SetMat4("model", model);
        //glDrawArrays(GL_TRIANGLES, 0, size);
        glDrawElements(
            GL_TRIANGLES,     
            size,    
            GL_UNSIGNED_SHORT,   
            (void*)0           
        );

    }
private:
    Vertex_array vao;


};