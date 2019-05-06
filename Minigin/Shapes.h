#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	struct Rect
	{
		glm::vec2 pos;
		float width;
		float height;
	};
}

