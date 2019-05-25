#pragma once
#include <ObserverComponent.h>
class LivesComponent : public dae::ObserverComponent
{
public:
	LivesComponent(int lives) :m_Lives(lives) {};
	~LivesComponent();
	void OnNotify(const std::string& event, const std::weak_ptr<dae::GameObject>& subject);
	int GetLives() { return m_Lives; }
private:
	int m_Lives;
};

