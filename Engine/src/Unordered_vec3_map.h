#pragma once
#include "PCH.h"

// Code found from: https://stackoverflow.com/questions/16792751/hashmap-for-2d3d-coordinates-i-e-vector-of-doubles

struct hashFunc
{
	size_t operator()(const irr::core::vector3di& k) const
	{
		size_t h1 = std::hash<int>()(k.X);
		size_t h2 = std::hash<int>()(k.Y);
		size_t h3 = std::hash<int>()(k.Z);
		return (h1 ^ (h2 << 1)) ^ h3;
	}
};

struct equalsFunc
{
	bool operator()(const irr::core::vector3di& lhs, const irr::core::vector3di& rhs) const
	{
		return (lhs.X == rhs.X) && (lhs.Y == rhs.Y) && (lhs.Z == rhs.Z);
	}
};

typedef std::unordered_map<irr::core::vector3di, unsigned int, hashFunc, equalsFunc> unodered_vec3_map;