#pragma once
#include "BaseComponent.h"
class DigDugLevelComponent;
namespace dae { class ColliderComponent; class TextureComponent; }
class PumpComponent final : public BaseComponent
{
public:
	PumpComponent(float speed, float lifeTime, glm::vec2 direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel);
	void Initialize() override;
	void Update(float deltaTime);
	void Render() const override {};
	void Pump();

private:
	dae::GameObject* m_pVictim;
	std::weak_ptr<DigDugLevelComponent> m_pLevel;
	std::weak_ptr<dae::ColliderComponent> m_pCollider;
	std::weak_ptr<dae::TextureComponent> m_pTexture;
	float m_Speed;
	float m_LifeTime;
	glm::vec2 m_Direction;
};

