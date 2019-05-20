#pragma once
#include "BaseComponent.h"
class DigDugLevelComponent;
namespace dae { class ColliderComponent; class TextureComponent; }

class FygarFireComponent : public BaseComponent
{
public:
	FygarFireComponent(float speed, float lifeTime, glm::vec2 direction, const std::weak_ptr<DigDugLevelComponent>& wpLevel);
	~FygarFireComponent();
	void Initialize() override;
	void Update(float deltaTime);
	void Render() const override {};
private:
	std::weak_ptr<DigDugLevelComponent> m_wpLevel;
	std::weak_ptr<dae::ColliderComponent> m_pCollider;
	std::weak_ptr<dae::TextureComponent> m_pTexture;
	glm::vec2 m_Direction;
	float m_LifeTime;
	float m_Speed;
	float m_ElapsedSec{};
};

