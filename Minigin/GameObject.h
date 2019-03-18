#pragma once
#include <memory>
#include "Transform.h"
class BaseComponent;

namespace dae
{
	class GameObject final
	{
	public:
		void Initialize();
		void Update(float deltaTime);
		void Render() const;
		void AddComponent(BaseComponent* pComponent);

		void SetPosition(float x, float y, float z) { m_Transform.m_Position = glm::vec3(x, y, z); }
		glm::vec3 GetPosition() const { return m_Transform.m_Position; }


		template<class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (BaseComponent* pComponent : m_pComponents)
			{
				if (pComponent && typeid(*pComponent) == ti)
					return static_cast<T*>(pComponent);

				//does not work for some reason
				/*T* pCastedComponent = std::dynamic_pointer_cast<T>(pComponent);
				if (pCastedComponent)
					return pCastedComponent;*/
			}
			return nullptr;
		}


		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:

		Transform m_Transform;
		std::vector<BaseComponent*> m_pComponents;
	};
}
