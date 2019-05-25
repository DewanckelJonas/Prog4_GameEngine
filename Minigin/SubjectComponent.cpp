#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include "ObserverComponent.h"

void dae::SubjectComponent::RegisterObserver(const std::weak_ptr<ObserverComponent>& wpObserver)
{
	for (size_t i = 0; i < m_wpObservers.size(); i++)
	{
		if (wpObserver.lock() == m_wpObservers[i].lock())
		{
			std::cout << "Warning: Observer is already added to this subject this was probably not intended." << std::endl;
		}
	}
	m_wpObservers.push_back(wpObserver);
}

void dae::SubjectComponent::UnRegisterObserver(const std::weak_ptr<ObserverComponent>& wpObserver)
{
	for (size_t i = 0; i < m_wpObservers.size(); i++)
	{
		if (wpObserver.lock() == m_wpObservers[i].lock())
		{
			m_wpObservers[i] = m_wpObservers.back();
			m_wpObservers.pop_back();
		}
	}
}

void dae::SubjectComponent::Notify(std::string event, const std::weak_ptr<GameObject>& subject)
{
	for (size_t i = 0; i < m_wpObservers.size(); i++)
	{
		m_wpObservers[i].lock()->OnNotify(event, subject);
	}
}

void dae::SubjectComponent::Update(float)
{
	for (size_t i = 0; i < m_wpObservers.size(); i++)
	{
		if (m_wpObservers[i].expired())
		{
			m_wpObservers[i] = m_wpObservers.back();
			m_wpObservers.pop_back();
			--i;
		}
	}
}
