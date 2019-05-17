#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae { class GameObject;  }
class DigDugLevelComponent;
namespace DigDugPrefabs
{
	dae::GameObject* CreatePump(const glm::vec2& position, const glm::vec2& direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel);
	dae::GameObject* CreatePooka(const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel);
}

