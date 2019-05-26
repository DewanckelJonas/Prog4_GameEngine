#include <ObserverComponent.h>
#include "DigDugLevelComponent.h"

class LivesComponent;
class VSModeComponent final : public dae::ObserverComponent
{
public:
	VSModeComponent(const std::weak_ptr<DigDugLevelComponent>& wpLevel, const std::weak_ptr<LivesComponent>& livesComp);
	~VSModeComponent();
	void OnNotify(const std::string& event, const std::weak_ptr<dae::GameObject>& subject);
private:
	std::weak_ptr<DigDugLevelComponent> m_wpLevel;
	std::weak_ptr<LivesComponent> m_wpFygarLives;
};


