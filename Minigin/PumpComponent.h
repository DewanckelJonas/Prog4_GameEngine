#pragma once
#include "BaseComponent.h"
class DigDugLevelComponent;
namespace dae { class ColliderComponent; class TextureComponent; }
class PumpComponent final : public BaseComponent
{
public:
	PumpComponent(float speed, float lifeTime, glm::vec2 direction, DigDugLevelComponent* pLevel);
	void Initialize() override;
	void Update(float deltaTime);
	void Render() const override {};

private:
	DigDugLevelComponent* m_pLevel;
	dae::ColliderComponent* m_pCollider;
	dae::TextureComponent* m_pTexture;
	float m_Speed;
	float m_LifeTime;
	glm::vec2 m_Direction;
};

