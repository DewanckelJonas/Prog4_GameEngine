#include "pch.h"
#include "DigDugGame.h"
#include "DigDugScene.h"
#include "SceneManager.h"

DigDugGame::DigDugGame()
{
}


DigDugGame::~DigDugGame()
{
}

void DigDugGame::LoadGame() const
{
	dae::SceneManager::GetInstance().AddScene(new DigDugScene(), "DigDugScene");
}
