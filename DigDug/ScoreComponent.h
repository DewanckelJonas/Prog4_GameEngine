#pragma once
#include <ObserverComponent.h>
class ScoreComponent : public dae::ObserverComponent
{
public:
	ScoreComponent();
	~ScoreComponent();
	void Update(float) override;
	void OnNotify(const std::string& event, const std::weak_ptr<dae::GameObject>& subject) override;
private:
	int m_Score{ 0 };
};

