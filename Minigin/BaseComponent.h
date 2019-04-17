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
	dae::GameObject* GetGameObject() const { return m_GameObject; };

private:
	dae::GameObject* m_GameObject{nullptr};
};

