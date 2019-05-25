#pragma once
#include "Grid.h"
#include "BaseComponent.h"
#include "Shapes.h"
#include <ObserverComponent.h>
class LivesComponent;

class DigDugTile : public dae::Tile
{
public:
	DigDugTile(bool isSolid, const std::shared_ptr<dae::Texture2D>& spTexture) :Tile(spTexture), m_IsSolid(isSolid) {}
	bool IsSolid() const { return m_IsSolid; }

private:
	bool m_IsSolid;
};

class DigDugLevelComponent final : public dae::ObserverComponent, public std::enable_shared_from_this<DigDugLevelComponent>
{
public:

	enum class TileType
	{
		Air,
		Ground
	};

	DigDugLevelComponent(const std::string& filePath, float width, float height, const std::weak_ptr<LivesComponent>& livesComp);
	DigDugLevelComponent(unsigned short rows, unsigned short cols, float width, float height);
	~DigDugLevelComponent();

	void Initialize() override;
	void Update(float) override {};
	void Render() const override;

	void OnNotify(const std::string& event, const std::weak_ptr<dae::GameObject>& subject);

	void Save(const std::string& path) const;

	float GetTileWidth() { return m_Grid.GetTileWidth(); }
	float GetTileHeight() { return m_Grid.GetTileHeight(); }

	void SetTile(const glm::vec2& pos, TileType type);
	std::weak_ptr<const DigDugTile> GetTile(const glm::vec2& pos) const;
	std::weak_ptr<const DigDugTile> GetTile(unsigned short row, unsigned short col) const;
	void GetTileRowCol(const glm::vec2& pos, unsigned short& row, unsigned short& col) const;
	glm::vec2 GetNearestTileCenter(const glm::vec2& pos) const;
	glm::vec2 GetClosestPlayerPosition(const glm::vec2& pos) const;
	dae::Rect GetBoundaries();

private:
	std::vector<std::weak_ptr<const dae::GameObject>> m_wpPlayers;
	dae::Grid m_Grid;
	std::weak_ptr<LivesComponent> m_wpLivesComp;
};

