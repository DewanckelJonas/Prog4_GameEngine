#include "pch.h"
#include "DigDugLevelComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "DigDugPrefabs.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SubjectComponent.h"
#include "LivesComponent.h"

DigDugLevelComponent::DigDugLevelComponent(const std::string & filePath, float width, float height, const std::weak_ptr<LivesComponent>& livesComp)
	:m_Grid(filePath, width, height)
	,m_wpLivesComp(livesComp)
{
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
	auto player0 = DigDugPrefabs::CreateDigDug(0, glm::vec2{ 180.f, 20.f }, weak_from_this());
	dae::SceneManager::GetInstance().GetActiveScene().lock()->Add(player0);
	player0->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(weak_from_this());
	player0->GetComponent<dae::SubjectComponent>().lock()->RegisterObserver(m_wpLivesComp);
	m_wpPlayers.push_back(player0);

	auto spAirTile = std::make_shared<DigDugTile>(false, nullptr);
	auto spGroundTexture = dae::ResourceManager::GetInstance().LoadTexture("GroundTile.png");
	auto spGroundTile = std::make_shared<DigDugTile>(true, spGroundTexture);
	m_Grid.AddTile(spAirTile); 
	m_Grid.AddTile(spGroundTile);
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
		subject.lock()->GetComponent<dae::TransformComponent>().lock()->SetPosition(glm::vec3{ 180.f, 20.f, 0 });
	}
}

void DigDugLevelComponent::Save(const std::string & path) const
{
	m_Grid.SaveGrid(path);
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
