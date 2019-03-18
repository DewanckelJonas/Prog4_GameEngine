#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent() = default;
		~FPSComponent() = default;
		void Initialize() override {};
		void Update(float elapsedSec) override;
		void Render() const override{};

		float GetFPS() const { return m_FPS; } 
	private:
		float m_FPS;
	};
}

