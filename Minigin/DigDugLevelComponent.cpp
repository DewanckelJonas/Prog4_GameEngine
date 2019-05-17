#include "MiniginPCH.h"
#include "DigDugLevelComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

DigDugLevelComponent::DigDugLevelComponent(const std::string & filePath, float width, float height)
	:m_Grid(filePath, width, height)
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
	auto spAirTile = std::make_shared<DigDugTile>(false, nullptr);
	auto spGroundTexture = dae::ResourceManager::GetInstance().LoadTexture("GroundTile.png");
	auto spGroundTile = std::make_shared<DigDugTile>(true, spGroundTexture);
	m_Grid.AddTile(spAirTile);
	m_Grid.AddTile(spGroundTile);
}

void DigDugLevelComponent::Render() const
{
	auto pos = GetGameObject()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	m_Grid.Render(pos);
}

void DigDugLevelComponent::Save(const std::string & path) const
{
	m_Grid.SaveGrid(path);
}

void DigDugLevelComponent::SetTile(const glm::vec2 & pos, TileType type)
{
	glm::vec2 originPos = GetGameObject()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	unsigned short row, col;
	m_Grid.CalculateRowCol(pos - originPos, row, col);
	m_Grid.SetTile(unsigned char(type), row, col);
}

glm::vec2 DigDugLevelComponent::GetNearestTileCenter(const glm::vec2 & pos) const
{
	glm::vec2 originPos = GetGameObject()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	unsigned short row, col;
	m_Grid.CalculateRowCol(pos - originPos, row, col);
	
	glm::vec2 closestCenter{};
	closestCenter.y = (row * m_Grid.GetTileHeight() + m_Grid.GetTileHeight() / 2) + originPos.y;
	closestCenter.x = (col * m_Grid.GetTileWidth() + m_Grid.GetTileWidth() / 2) + originPos.x;
	return closestCenter;
}

std::weak_ptr<DigDugTile> DigDugLevelComponent::GetTile(const glm::vec2 & pos) const
{
	glm::vec2 originPos = GetGameObject()->GetComponent<dae::TransformComponent>().lock()->GetPosition();
	unsigned short row, col;
	m_Grid.CalculateRowCol(pos - originPos, row, col);
	auto wpTile = m_Grid.GetTile(row, col);
	return std::static_pointer_cast<DigDugTile>(wpTile.lock());
}
