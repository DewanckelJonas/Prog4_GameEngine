#pragma once
#include "SceneManager.h"
#include <future>

namespace dae
{
	class BaseCommand;
	class GameObject;
	class Scene
	{
		
	public:
		explicit Scene(const std::string& name);
		void Add(std::shared_ptr<GameObject> spObject);

		virtual void Initialize();
		void UpdateAI();
		virtual void Update(float deltaTime);
		virtual void Render() const;
		virtual void CleanUp();

		const std::string& GetName() { return m_Name; };
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		std::future<std::vector<std::weak_ptr<BaseCommand>>> m_wpAICommands;
		std::string m_Name{};
		std::vector<std::shared_ptr<GameObject>> m_spObjects{};
	};

}
