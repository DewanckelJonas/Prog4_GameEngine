#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
class BaseComponent;
class ColliderComponent;

namespace dae
{
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void Initialize();
		void Update(float deltaTime);
		void Render() const;
		void AddComponent(std::shared_ptr<BaseComponent> pComponent);
		bool IsDestroyed() { return m_IsDestroyed; }
		void Destroy() { m_IsDestroyed = true; }

		template<class T>
		std::weak_ptr<T> GetComponent()
		{
			for (auto spComponent : m_spComponents)
			{
				std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(spComponent);
				if (result) return result;
			}
			return {};
		}

		template<class T>
		std::weak_ptr<const T> GetComponent() const
		{
			for (auto spComponent : m_spComponents)
			{
				std::shared_ptr<const T> result = std::dynamic_pointer_cast<T>(spComponent);
				if (result) return result;
			}
			return {};
		}


		GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_IsDestroyed = false;
		std::vector<std::shared_ptr<BaseComponent>> m_spComponents;
	};
}
