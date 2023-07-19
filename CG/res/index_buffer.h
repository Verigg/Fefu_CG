#pragma once

#include <GL/glew.h>

class index_buffer {
public:
	index_buffer(unsigned short data[], int size) {
		glGenBuffers(1, &id);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(data), data, GL_STATIC_DRAW);
	}

	index_buffer(vector<unsigned short> data) {
		glGenBuffers(1, &id);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned short), &data[0], GL_STATIC_DRAW);
	}


	void Bind(int flag = -1) {
		if (flag == 0)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		else
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
	void Delete() {
		glDeleteBuffers(1, &id);
	}

private:
	unsigned int id;
};
