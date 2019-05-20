#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"


void dae::FPSComponent::Update(float elapsedSec)
{
	m_FPS = 1 / elapsedSec;
	auto textComp = GetGameObject().lock()->GetComponent<TextComponent>();
	if (!textComp.expired())
	{
		textComp.lock()->SetText(std::to_string(m_FPS));
	}
}
