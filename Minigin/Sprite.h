#pragma once
#include "Texture2D.h"
#include "ResourceManager.h"
namespace dae
{
	class Sprite
	{
	private:
		int m_NrOfRows;
		int m_NrOfCols;
		std::shared_ptr<Texture2D> m_spTexture;
	public:
		Sprite(const std::shared_ptr<Texture2D> spTexture, int nrOfRows, int nrOfCols) 
			: m_spTexture(spTexture)
			, m_NrOfRows(nrOfRows)
			, m_NrOfCols(nrOfCols)
		{}
		Sprite(const std::string& path, int nrOfRows, int nrOfCols)
			: m_NrOfRows(nrOfRows)
			, m_NrOfCols(nrOfCols)
		{
			m_spTexture = ResourceManager::GetInstance().LoadTexture(path);
		}

		int GetRows() const { return m_NrOfRows; }
		int GetCols() const { return m_NrOfCols; }
		std::shared_ptr<Texture2D> GetTexture() const { return m_spTexture; };
	};
}

