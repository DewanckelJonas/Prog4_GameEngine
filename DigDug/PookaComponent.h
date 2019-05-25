#pragma once
#include "DigDugEnemyComponent.h"
class PookaComponent final : public DigDugEnemyComponent
{
public:
	PookaComponent(std::weak_ptr<DigDugLevelComponent> wpLevel) :DigDugEnemyComponent(wpLevel) {};
	const dae::Sprite& GetWalkSprite() override { return m_WalkingSprite; }
	const dae::Sprite& GetGhostSprite() override { return m_GhostSprite; }
	const dae::Sprite& GetBlowUpSprite() override { return m_BlowUpSprite; }
	const dae::Sprite& GetChargeSprite() override { return m_WalkingSprite; }
private:
	dae::Sprite m_WalkingSprite{ "PookaWalk.png", 1, 2 };
	dae::Sprite m_GhostSprite{ "PookaGhost.png", 1, 2 };
	dae::Sprite m_BlowUpSprite{ "PookaBlowUp.png", 1, 4 };
};

