#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene* pScene, const std::string& name);

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render();

	private:
		std::map<std::string, std::shared_ptr<Scene>> m_spScenes;
		std::shared_ptr<Scene> m_spCurrentScene;
	};

}
