#include "pch.h"
#include "DigDugGame.h"
#include "DigDugLevelEditScene.h"
#include "DigDug1PlayerScene.h"
#include "DigDug2PlayerScene.h"
#include "DigDugVersusScene.h"
#include "GameSelectScene.h"
#include "SceneManager.h"

DigDugGame::DigDugGame()
{
}


DigDugGame::~DigDugGame()
{
}

void DigDugGame::LoadGame() const
{
	dae::SceneManager::GetInstance().AddScene(new DigDugLevelEditScene(), "DigDugLevelEditScene");
	dae::SceneManager::GetInstance().AddScene(new DigDug1PlayerScene(), "DigDug1PlayerScene");
	dae::SceneManager::GetInstance().AddScene(new DigDug2PlayerScene(), "DigDug2PlayerScene");
	dae::SceneManager::GetInstance().AddScene(new DigDugVersusScene(), "DigDugVersusScene");
	dae::SceneManager::GetInstance().AddScene(new GameSelectScene(), "GameSelectScene");
	dae::SceneManager::GetInstance().SetActiveScene("GameSelectScene");
}
