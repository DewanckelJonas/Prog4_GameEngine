#include "pch.h"
#include "LivesDisplayComponent.h"
#include <TextComponent.h>
#include "LivesComponent.h"

LivesDisplayComponent::LivesDisplayComponent()
{
}


LivesDisplayComponent::~LivesDisplayComponent()
{
}

void LivesDisplayComponent::Update(float)
{
	int lives = GetGameObject().lock()->GetComponent<LivesComponent>().lock()->GetLives();
	std::string liveDisplay = "Lives: ";
	liveDisplay += std::to_string(lives);
	GetGameObject().lock()->GetComponent<dae::TextComponent>().lock()->SetText(liveDisplay);
}
