#pragma once

#include "../Includes.h"

void indexVBO(
	std::vector<Vec2> & in_vertices,
	std::vector<Vec2> & in_uvs,
	std::vector<Vec2> & in_normals,

	std::vector<unsigned short> & out_indices,
	std::vector<Vec2> & out_vertices,
	std::vector<Vec2> & out_uvs,
	std::vector<Vec2> & out_normals
);


void indexVBO_TBN(
	std::vector<Vec2> & in_vertices,
	std::vector<Vec2> & in_uvs,
	std::vector<Vec2> & in_normals,
	std::vector<Vec2> & in_tangents,
	std::vector<Vec2> & in_bitangents,

	std::vector<unsigned short> & out_indices,
	std::vector<Vec2> & out_vertices,
	std::vector<Vec2> & out_uvs,
	std::vector<Vec2> & out_normals,
	std::vector<Vec2> & out_tangents,
	std::vector<Vec2> & out_bitangents
);

