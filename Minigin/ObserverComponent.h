#pragma once
#include "BaseComponent.h"
#include <string>
namespace dae
{
	class ObserverComponent : public BaseComponent
	{
	public:
		ObserverComponent() = default;
		virtual ~ObserverComponent() = default;
		virtual void Initialize() override {}
		virtual void Update(float) override {}
		virtual void Render() const {};
		virtual void OnNotify(const std::string& event, const std::weak_ptr<GameObject>& subject) = 0;
	};
}

