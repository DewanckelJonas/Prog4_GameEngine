#include "pch.h"
#include "LivesComponent.h"
#include <SubjectComponent.h>

LivesComponent::~LivesComponent()
{
}

void LivesComponent::OnNotify(const std::string & event, const std::weak_ptr<dae::GameObject>& subject)
{
	if((event == "Died") || (event == "Popped"))
	{
		--m_Lives;
		if(m_Lives < 0)
		{
			GetGameObject().lock()->GetComponent<dae::SubjectComponent>().lock()->Notify("GameOver", subject);
		}
	}
}
