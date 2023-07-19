#pragma once
#include <GL/glew.h>

class Vertex_array {
public:

	Vertex_array() {
		glGenVertexArrays(1, &id);
		Bind();
	}

	void AttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) {
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		glEnableVertexAttribArray(index);
	}

	void Bind(int flag = -1) {
		if (flag == 0)
			glBindVertexArray(0);
		else
			glBindVertexArray(id);
	}

	void Delete() {
		glDeleteVertexArrays(1, &id);
	}

private:
	unsigned int id;
};