#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		
	public:
		explicit Scene(const std::string& name);
		void Add(GameObject* object);

		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Render() const;

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 

		std::string mName{};
		std::vector <GameObject*> mObjects{};

		static unsigned int idCounter; 
	};

}
