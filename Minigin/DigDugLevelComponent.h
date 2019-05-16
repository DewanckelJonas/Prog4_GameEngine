#pragma once
#include "Grid.h"
#include "BaseComponent.h"



class DigDugTile : public dae::Tile
{
public:
	DigDugTile(bool isSolid, const std::shared_ptr<dae::Texture2D>& spTexture) :Tile(spTexture), m_IsSolid(isSolid) {}
	bool IsSolid() const { return m_IsSolid; }

private:
	bool m_IsSolid;
};

class DigDugLevelComponent final : public BaseComponent
{
public:

	enum class TileType
	{
		Air,
		Ground
	};

	DigDugLevelComponent(const std::string& filePath, float width, float height);
	DigDugLevelComponent(unsigned short rows, unsigned short cols, float width, float height);
	~DigDugLevelComponent();

	void Initialize() override;
	void Update(float) override {};
	void Render() const override;

	void Save(const std::string& path) const;

	float GetTileWidth() { return m_Grid.GetTileWidth(); }
	float GetTileHeight() { return m_Grid.GetTileHeight(); }

	void SetTile(const glm::vec2& pos, TileType type);
	std::weak_ptr<DigDugTile> GetTile(const glm::vec2& pos) const;
	glm::vec2 GetNearestTileCenter(const glm::vec2& pos) const;

private:
	dae::Grid m_Grid;
};

