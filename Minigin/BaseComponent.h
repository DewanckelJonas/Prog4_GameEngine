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

	friend void dae::GameObject::Initialize();
	friend void dae::GameObject::Update(float deltaTime);
	friend void dae::GameObject::Render() const;
	friend void dae::GameObject::AddComponent(BaseComponent* pComponent);

	dae::GameObject* GetGameObject() const { return m_GameObject; };

private:
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() const = 0;
	dae::GameObject* m_GameObject{nullptr};
};

