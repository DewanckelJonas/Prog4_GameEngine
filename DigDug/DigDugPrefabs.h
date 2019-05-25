#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae { class GameObject;  }
class DigDugLevelComponent;
class ScoreComponent;
namespace DigDugPrefabs
{
	std::shared_ptr<dae::GameObject> CreatePump(const glm::vec2& position, const glm::vec2& direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel);
	std::shared_ptr<dae::GameObject> CreateFire(const glm::vec2& position, const glm::vec2& direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel);
	std::shared_ptr<dae::GameObject> CreatePooka(const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel, const std::weak_ptr<ScoreComponent>& wpScore);
	std::shared_ptr<dae::GameObject> CreateFygar(const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel, const std::weak_ptr<ScoreComponent>& wpScore);
	std::shared_ptr<dae::GameObject> CreateRock(const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel, const std::weak_ptr<ScoreComponent>& wpScore);
	std::shared_ptr<dae::GameObject> CreateDigDug(int playerIndex, const glm::vec2& position, const std::weak_ptr<DigDugLevelComponent> wpLevel);
}

