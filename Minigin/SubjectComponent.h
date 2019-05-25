#pragma once
#include "BaseComponent.h"
namespace dae
{
	class ObserverComponent;
	class SubjectComponent final : public BaseComponent
	{
	public:
		SubjectComponent() = default;
		~SubjectComponent() = default;
		void RegisterObserver(const std::weak_ptr<ObserverComponent>& wpObserver);
		void UnRegisterObserver(const std::weak_ptr<ObserverComponent>& wpObserver);
		void Notify(std::string event, const std::weak_ptr<GameObject>& subject);
		void Initialize() override {};
		void Update(float) override;
		void Render() const {};

	private:
		std::vector<std::weak_ptr<ObserverComponent>> m_wpObservers;
	};
}

