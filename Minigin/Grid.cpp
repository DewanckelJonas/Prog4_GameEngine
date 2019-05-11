#include "MiniginPCH.h"
#include "Grid.h"
#include <fstream>


dae::Grid::Grid(unsigned short rows, unsigned short cols, float width, float height)
	:m_Width(width)
	,m_Height(height)
	,m_Rows(rows)
	,m_Cols(cols)
{
	m_TileHeight = m_Height / m_Rows;
	m_TileWidth = m_Width / m_Cols;
	m_Grid = new unsigned char[m_Rows * m_Cols]{0};
}

dae::Grid::Grid(const std::string & filePath, float width, float height)
	:m_Height(height)
	,m_Width(width)
{
	std::ifstream saveFile;
	saveFile.open(filePath.c_str(), std::ios::in | std::ios::binary);
	{
		saveFile.read((char*)&m_Rows, sizeof(short));
		saveFile.read((char*)&m_Cols, sizeof(short));
		m_Grid = new unsigned char[m_Rows * m_Cols]{ 0 };
		for (unsigned short i = 0; i < m_Rows*m_Cols; i++)
		{
			saveFile.read((char*)&m_Grid[i], sizeof(char));
		}
	}
	saveFile.close();

	m_TileHeight = m_Height / m_Rows;
	m_TileWidth = m_Width / m_Cols;
}

dae::Grid::~Grid()
{
	delete[] m_Grid;
}

void dae::Grid::SetTile(unsigned char tileId, unsigned short rowIdx, unsigned short colIdx)
{
	m_Grid[rowIdx*m_Cols + colIdx] = tileId;
}

std::weak_ptr<dae::Tile> dae::Grid::GetTile(unsigned short rowIdx, unsigned short colIdx) const
{
	return m_TileSet[m_Grid[rowIdx*m_Cols + colIdx]];
}

void dae::Grid::CalculateRowCol(glm::vec2 pos, unsigned short& row, unsigned short& col) const
{
	row = unsigned short(pos.y / m_TileHeight);
	col = unsigned short(pos.x / m_TileWidth);
	if (row >= m_Rows)
		row = m_Rows-1;
	if (col >= m_Cols)
		col = m_Cols-1;
}

void dae::Grid::SaveGrid(const std::string & filePath) const
{
	std::ofstream saveFile;
	saveFile.open(filePath.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
	{
		saveFile.write((char*)&m_Rows, sizeof(short));
		saveFile.write((char*)&m_Cols, sizeof(short));
		for (unsigned short i = 0; i < m_Cols*m_Rows; i++)
		{
			saveFile.write((char*)&m_Grid[i], sizeof(char));
		}
	}
	saveFile.close();
}


void dae::Grid::Render(glm::vec2 position) const
{
	glm::vec2 originPos{ position };
	glm::vec2 pos{position};
	for (short r = 0; r < m_Rows; r++)
	{
		for (short c = 0; c < m_Cols; c++)
		{
			auto spTile = m_TileSet[m_Grid[r*m_Cols + c]];
			if(spTile)
				spTile->Render(pos, m_TileWidth, m_TileHeight);
			else
			{
				std::cout << "Trying to acces invalid tile from tileset! Make sure you add all the necessary tiles.\n";
				return;
			}
			pos.x += m_TileWidth;
		}
		pos.y += m_TileHeight;
		pos.x = originPos.x;
	}
}

void dae::Grid::AddTile(const std::shared_ptr<Tile>& tile)
{
	m_TileSet[m_NrOfFilledTiles++] = tile;
}
