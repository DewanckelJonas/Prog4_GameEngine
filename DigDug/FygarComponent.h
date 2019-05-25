#pragma once
#include "DigDugEnemyComponent.h"
#include "Sprite.h"
class FygarComponent final : public DigDugEnemyComponent
{
public:
	FygarComponent(std::weak_ptr<DigDugLevelComponent> wpLevel) :DigDugEnemyComponent(wpLevel) {}
	void Attack() override;
	const dae::Sprite& GetWalkSprite() override { return m_WalkingSprite; }
	const dae::Sprite& GetGhostSprite() override { return m_GhostSprite; }
	const dae::Sprite& GetBlowUpSprite() override { return m_BlowUpSprite; }
	const dae::Sprite& GetChargeSprite() override { return m_ChargeSprite; }
private:
	dae::Sprite m_WalkingSprite{ "FygarWalk.png", 1, 2 };
	dae::Sprite m_GhostSprite{ "FygarGhost.png", 1, 2 };
	dae::Sprite m_BlowUpSprite{ "FygarBlowUp.png", 1, 4 };
	dae::Sprite m_ChargeSprite{ "FygarFiring.png" , 1, 2 };
};

