#pragma once
#include "Tile.h"
#include "BaseComponent.h"
#include <memory>
namespace dae
{
	class Grid final
	{
	public:
		Grid(unsigned short rows, unsigned short cols, float width, float height);
		Grid(const std::string& filePath, float width, float height);
		~Grid();

		void SetTile(unsigned char tileId, unsigned short rowIdx, unsigned short colIdx);
		std::weak_ptr<const Tile> GetTile(unsigned short rowIdx, unsigned short colIdx) const;
		void CalculateRowCol(glm::vec2 pos, unsigned short& row, unsigned short& col) const;
		void SaveGrid(const std::string& filePath) const;

		float GetTileWidth() const { return m_TileWidth; }
		float GetTileHeight() const { return m_TileHeight; }

		void Render(glm::vec2 position) const;
		void AddTile(const std::shared_ptr<Tile>& tile);

	private:
		float m_Width;
		float m_Height;
		float m_TileHeight;
		float m_TileWidth;
		unsigned short m_Rows;
		unsigned short m_Cols;
		unsigned char* m_Grid{};
		static const size_t m_TileSetSize = 255;
		size_t m_NrOfFilledTiles{ 0 };
		std::shared_ptr<Tile> m_TileSet[m_TileSetSize];
	};
}

