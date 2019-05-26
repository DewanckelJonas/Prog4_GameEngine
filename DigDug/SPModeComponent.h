#pragma once
#include <ObserverComponent.h>
#include "DigDugLevelComponent.h"
class SPModeComponent final : public dae::ObserverComponent
{
public:
	SPModeComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel);
	~SPModeComponent();
	void OnNotify(const std::string& event, const std::weak_ptr<dae::GameObject>& subject);
	void Update(float) override;
private:
	std::weak_ptr<DigDugLevelComponent> m_wpLevel;
};

