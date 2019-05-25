#pragma once
#include <Minigin.h>
class DigDugGame final : public dae::Minigin
{
public:
	DigDugGame();
	~DigDugGame();
	void LoadGame() const override;
};

