#pragma once


#include <../Includes.h>

Vertex loadOBJ(
	const char* path,
	std::vector < Vec3 >& out_vertices,
	std::vector < Vec2 >& out_uvs,
	std::vector < Vec3 >& out_normals
);