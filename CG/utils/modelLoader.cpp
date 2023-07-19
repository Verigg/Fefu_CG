#pragma once
#include "modelLoader.h"
#include "vboindexer.cpp"

inline Vertex loadOBJ(
	const char* path)
{
	Vertex out;
	std::vector < Vec3 > out_vertices;
	std::vector < Vec2 > out_uvs;
	std::vector < Vec3 > out_normals;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< Vec3 > temp_vertices;
	std::vector< Vec2 > temp_uvs;
	std::vector< Vec3 > temp_normals;

	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");   
		return out;
	}

	while (true) {
		char lineHeader[128];
		// читаем первый символ в файле
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = Конец файла. Заканчиваем цикл чтения
		// else : парсим строку

		if (strcmp(lineHeader, "v") == 0) {
			Vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return out;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		Vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		Vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		Vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}
	std::vector<unsigned short> out_indices;
	std::vector < Vec3 > indexed_out_vertices;
	std::vector < Vec2 > indexed_out_uvs;
	std::vector < Vec3 > indexed_out_normals;
	indexVBO(out_vertices, out_uvs, out_normals, out_indices, indexed_out_vertices, indexed_out_uvs, indexed_out_normals);


	out = { indexed_out_vertices , indexed_out_uvs, indexed_out_normals, out_indices };
	return out;
}

