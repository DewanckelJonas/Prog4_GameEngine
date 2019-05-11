#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

struct Transform
{
	glm::vec3 Position{};
	float Rotation{};
	glm::vec2 Scale{ 1,1 };
};

