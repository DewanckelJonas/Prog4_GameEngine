#pragma once
#include "GameObject.h"
class BaseComponent
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent() = default;
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() const = 0;
	std::weak_ptr<dae::GameObject> GetGameObject() { return m_GameObject; };
	std::weak_ptr<const dae::GameObject> GetGameObject() const { return m_GameObject; }

	friend void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> pComponent);

private:
	std::weak_ptr<dae::GameObject> m_GameObject{};
};

