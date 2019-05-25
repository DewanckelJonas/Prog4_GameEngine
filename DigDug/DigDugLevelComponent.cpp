#include "pch.h"
#include "DigDugLevelComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "DigDugPrefabs.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SubjectComponent.h"
#include "LivesComponent.h"
#include "SceneManager.h"
#include <fstream>
#include "ScoreComponent.h"

DigDugLevelComponent::DigDugLevelComponent(const std::string & filePath, float width, float height, const std::weak_ptr<dae::GameObject>& livesDisplay, const std::weak_ptr<dae::GameObject>& scoreDisplay)
	:m_Grid(filePath, width, height)
	,m_wpLivesDisplay(livesDisplay)
	,m_wpScoreDisplay(scoreDisplay)
{
	std::ifstream saveFile;
	saveFile.open(filePath.c_str(), std::ios::in | std::ios::binary);
	{
		//skip grid part
		short rows, cols;
		saveFile.read((char*)&rows, sizeof(short));
		saveFile.read((char*)&cols, sizeof(short));
		int posAfterGrid = rows * cols + 2 * sizeof(short);
		saveFile.seekg(posAfterGrid);
		//read player spawn positions
		for (size_t i = 0; i < 4; i++)
		{
			saveFile.read((char*)&m_PlayerSpawnPositions[i], sizeof(glm::vec2));
		}
		//read pooka
		short nrOfPookas;
		saveFile.read((char*)&nrOfPookas, sizeof(short));
		for (short i = 0; i < nrOfPookas; i++)
		{
			glm::vec2 pos;
			saveFile.read((char*)&pos, sizeof(glm::vec2));
			m_PookaPositions.push_back(pos);
		}
		//read fygar
		short nrOfFygars;
		saveFile.read((char*)&nrOfFygars, sizeof(short));
		for (short i = 0; i < nrOfFygars; i++)
		{
			glm::vec2 pos;
			saveFile.read((char*)&pos, sizeof(glm::vec2));
			m_FygarPositions.push_back(pos);
		}
		//read rocks
		short nrOfRocks;
		saveFile.read((char*)&nrOfRocks, sizeof(short));
		for (short i = 0; i < nrOfRocks; i++)
		{
			glm::vec2 pos;
			saveFile.read((char*)&pos, sizeof(glm::vec2));
			m_RockPositions.push_back(pos);
		}
	}
	saveFile.close();
}

DigDugLevelComponent::DigDugLevelComponent(unsigned short rows, unsigned short cols, float width, float height)
	:m_Grid(rows, cols, width, height)
{
}

DigDugLevelComponent::~DigDugLevelComponent()
{
}

void DigDugLevelComponent::Initialize()
{
	for (const glm::vec2& pos : m_PookaPositions)
	{
		auto pooka = DigDugPrefabs::CreatePooka(pos, weak_from_this(), m_wpScoreDisplay.lock()->GetComponent<ScoreComponent>());
		m_wpEnemies.push_back(pooka);
		dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(pooka);
	}
	for (const glm::vec2& pos : m_FygarPositions)
	{
		auto fygar = DigDugPrefabs::CreateFygar(pos, weak_from_this(), m_wpScoreDisplay.lock()->GetComponent<ScoreComponent>());
		m_wpEnemies.push_back(fygar);
		dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(fygar);
	}
	for (const glm::vec2& pos : m_RockPositions)
	{
		auto rock = DigDugPrefabs::CreateRock(pos, weak_from_this(), m_wpScoreDisplay.lock()->GetComponent<ScoreComponent>());
		m_wpEnemies.push_back(rock);
		dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(rock);
	}


	auto spAirTile = std::make_shared<DigDugTile>(false, nullptr);
	m_Grid.AddTile(spAirTile); 
	auto spGroundTexture1 = dae::ResourceManager::GetInstance().LoadTexture("GroundTileL1.png");
	auto spGroundTileL1 = std::make_shared<DigDugTile>(true, spGroundTexture1);
	m_Grid.AddTile(spGroundTileL1);
	auto spGroundTexture2 = dae::ResourceManager::GetInstance().LoadTexture("GroundTileL2.png");
	auto spGroundTileL2 = std::make_shared<DigDugTile>(true, spGroundTexture2);
	m_Grid.AddTile(spGroundTileL2);
	auto spGroundTexture3 = dae::ResourceManager::GetInstance().LoadTexture("GroundTileL3.png");
	auto spGroundTileL3 = std::make_shared<DigDugTile>(true, spGroundTexture3);
	m_Grid.AddTile(spGroundTileL3);
	auto spGroundTexture = dae::ResourceManager::GetInstance().LoadTexture("GroundTileL4.png");
	auto spGroundTileL4 = std::make_shared<DigDugTile>(true, spGroundTexture);
	m_Grid.AddTile(spGroundTileL4);


}

void DigDugLevelComponent::Render() const
{
	auto pos = GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	m_Grid.Render(pos);
}

void DigDugLevelComponent::OnNotify(const std::string & event, const std::weak_ptr<dae::GameObject>& subject)
{
	if (event == "Died")
	{
		auto spawnPos = GetNearestTileCenter(glm::vec2{ 180.f, 20.f});
		subject.lock()->GetComponent<dae::TransformComponent>().lock()->SetPosition({ spawnPos.x, spawnPos.y, 0 });
	}
	if(event == "GameOver")
	{
		std::cout << "Game Over" << std::endl;
		dae::SceneManager::GetInstance().SetActiveScene("DigDugScene");
	}
}

void DigDugLevelComponent::Save(const std::string & path) const
{
	m_Grid.SaveGrid(path);
	std::ofstream saveFile;
	saveFile.open(path.c_str(), std::ios::out | std::ios::binary | std::ios_base::app);
	{
		for (unsigned short i = 0; i < 4; i++)
		{
			saveFile.write((char*)&m_PlayerSpawnPositions[i], sizeof(glm::vec2));
		}
		short nrOfPookas = short(m_PookaPositions.size());
		saveFile.write((char*)&nrOfPookas, sizeof(short));
		for (short i = 0; i < nrOfPookas; i++)
		{
			saveFile.write((char*)&m_PookaPositions[i], sizeof(glm::vec2));
		}
		short nrOfFygars = short(m_FygarPositions.size());
		saveFile.write((char*)&nrOfFygars, sizeof(short));
		for (short i = 0; i < nrOfFygars; i++)
		{
			saveFile.write((char*)&m_FygarPositions[i], sizeof(glm::vec2));
		}
		short nrOfRocks = short(m_RockPositions.size());
		saveFile.write((char*)&nrOfRocks, sizeof(short));
		for (short i = 0; i < nrOfRocks; i++)
		{
			saveFile.write((char*)&m_RockPositions[i], sizeof(glm::vec2));
		}
	}
	saveFile.close();
}

void DigDugLevelComponent::AddPookaSpawnPosition(const glm::vec2 & position)
{
	auto alignedPos = GetNearestTileCenter(position);
	m_PookaPositions.push_back(alignedPos);
}

void DigDugLevelComponent::AddFygarSpawnPosition(const glm::vec2 & position)
{
	auto alignedPos = GetNearestTileCenter(position);
	m_FygarPositions.push_back(alignedPos);
}

void DigDugLevelComponent::AddRockSpawnPosition(const glm::vec2 & position)
{
	auto alignedPos = GetNearestTileCenter(position);
	m_RockPositions.push_back(alignedPos);
}

void DigDugLevelComponent::ClearPookaSpawnPositions()
{
	m_PookaPositions.clear();
}

void DigDugLevelComponent::ClearFygarSpawnPositions()
{
	m_FygarPositions.clear();
}

void DigDugLevelComponent::ClearRockSpawnPositions()
{
	m_RockPositions.clear();
}

void DigDugLevelComponent::SetPlayerSpawnPosition(int id, const glm::vec2 & position)
{
	auto alignedPos = GetNearestTileCenter(position);
	m_PlayerSpawnPositions[id] = alignedPos;
}

int DigDugLevelComponent::GetLayer(glm::vec2 pos)
{
	unsigned short row, col;
	GetTileRowCol(pos, row, col);
	auto layerSize = m_Grid.GetRows()/4;
	return row / layerSize;
}

void DigDugLevelComponent::SetTile(const glm::vec2 & pos, TileType type)
{
	glm::vec2 originPos = GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	unsigned short row, col;
	m_Grid.CalculateRowCol(pos - originPos, row, col);
	m_Grid.SetTile(unsigned char(type), row, col);
}

glm::vec2 DigDugLevelComponent::GetNearestTileCenter(const glm::vec2 & pos) const
{
	glm::vec2 originPos = GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	unsigned short row, col;
	m_Grid.CalculateRowCol(pos - originPos, row, col);
	
	glm::vec2 closestCenter{};
	closestCenter.y = (row * m_Grid.GetTileHeight() + m_Grid.GetTileHeight() / 2) + originPos.y;
	closestCenter.x = (col * m_Grid.GetTileWidth() + m_Grid.GetTileWidth() / 2) + originPos.x;
	return closestCenter;
}

glm::vec2 DigDugLevelComponent::GetClosestPlayerPosition(const glm::vec2 & pos) const
{
	glm::vec3 closestPlayerPos{};
	float shortestDistanceSq{10000000000};
	for (const std::weak_ptr<const dae::GameObject>& wpPlayer : m_wpPlayers)
	{
		auto playerPos = wpPlayer.lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
		glm::vec3 distanceVec = playerPos - glm::vec3(pos.x, pos.y, 0);
		float distanceSq = distanceVec.x*distanceVec.x + distanceVec.y*distanceVec.y;
		if (distanceSq < shortestDistanceSq)
		{
			shortestDistanceSq = distanceSq;
			closestPlayerPos = playerPos;
		}
	}
	return glm::vec2(closestPlayerPos.x, closestPlayerPos.y);
}

dae::Rect DigDugLevelComponent::GetBoundaries()
{
	auto pos = GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	return dae::Rect{ pos, m_Grid.GetWidth(), m_Grid.GetHeight() };
}

std::weak_ptr<const DigDugTile> DigDugLevelComponent::GetTile(const glm::vec2 & pos) const
{
	glm::vec2 originPos = GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	unsigned short row, col;
	m_Grid.CalculateRowCol(pos - originPos, row, col);
	auto wpTile = m_Grid.GetTile(row, col);
	return std::static_pointer_cast<const DigDugTile>(wpTile.lock());
}

std::weak_ptr<const DigDugTile> DigDugLevelComponent::GetTile(unsigned short row, unsigned short col) const
{
	auto wpTile = m_Grid.GetTile(row, col);
	return std::static_pointer_cast<const DigDugTile>(wpTile.lock());
}

void DigDugLevelComponent::GetTileRowCol(const glm::vec2& pos, unsigned short & row, unsigned short & col) const
{
	glm::vec2 originPos = GetGameObject().lock()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	m_Grid.CalculateRowCol(pos - originPos, row, col);
}
