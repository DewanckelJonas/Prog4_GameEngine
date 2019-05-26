#pragma once
#include "Singleton.h"
#include <map>
#include <memory>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene* pScene, const std::string& name);

		void Initialize();
		void Update(float deltaTime);
		void Render();
		std::weak_ptr<Scene> GetActiveScene() { return m_spCurrentScene; };
		void SetActiveScene(const std::string& name);

	private:
		std::shared_ptr<Scene> m_NextScene{};
		bool m_HasFinishedGameLoop = true;
		void SwapScene();
		std::map<std::string, std::shared_ptr<Scene>> m_spScenes;
		std::shared_ptr<Scene> m_spCurrentScene;
	};

}
