#pragma once
#include <BaseComponent.h>
class LivesDisplayComponent : public BaseComponent
{
public:
	LivesDisplayComponent();
	~LivesDisplayComponent();
	void Initialize() override {};
	void Update(float) override;
	void Render() const override {};
};

