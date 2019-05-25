#include "pch.h"
#include "ScoreComponent.h"
#include <TextComponent.h>
#include "PookaComponent.h"
#include "FygarComponent.h"
#include "DigDugLevelComponent.h"
#include <TransformComponent.h>
#include "RockComponent.h"

ScoreComponent::ScoreComponent()
{
}


ScoreComponent::~ScoreComponent()
{
}

void ScoreComponent::OnNotify(const std::string & event, const std::weak_ptr<dae::GameObject>& subject)
{
	if (event == "Popped")
	{
		auto pos = subject.lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
		std::shared_ptr<DigDugEnemyComponent> enemy = subject.lock()->GetComponent<DigDugEnemyComponent>().lock();
		if (enemy)
		{
			int layer = enemy->GetLevel().lock()->GetLayer({ pos.x, pos.y });
			int score = 200;
			score += layer * 100;
			if (subject.lock()->GetComponent<FygarComponent>().lock())
				score *= 2;
			m_Score += score;
		}
	}

	if(event == "Crushed")
	{
		auto nrOfKills = subject.lock()->GetComponent<RockComponent>().lock()->GetNrOfEnemiesKilled();

		switch (nrOfKills)
		{
		case 0:
			break;
		case 1:
			m_Score += 1000;
			break;
		case 2:
			m_Score += 2500;
			break;
		case 3:
			m_Score += 4000;
			break;
		case 4: 
			m_Score += 6000;
			break;
		case 5:
			m_Score += 8000;
			break;
		case 6:
			m_Score += 10000;
			break;
		case 7:
			m_Score += 12000;
			break;
		case 8:
			m_Score += 15000;
			break;
		default:
			m_Score += 15000;
			break;
		}
	}
}

void ScoreComponent::Update(float)
{
	std::string scoreDisplay = "Score: ";
	scoreDisplay += std::to_string(m_Score);
	GetGameObject().lock()->GetComponent<dae::TextComponent>().lock()->SetText(scoreDisplay);
}
