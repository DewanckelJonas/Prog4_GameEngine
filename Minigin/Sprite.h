#pragma once
#include "Texture2D.h"
namespace dae
{
	class Sprite
	{
	private:
		const int m_NrOfRows;
		const int m_NrOfCols;
		std::shared_ptr<Texture2D> m_spTexture;
	public:
		explicit Sprite(const std::shared_ptr<Texture2D> spTexture, int nrOfRows, int nrOfCols) 
			: m_spTexture(spTexture)
			, m_NrOfRows(nrOfRows)
			, m_NrOfCols(nrOfCols)
		{}

		int GetRows() const { return m_NrOfRows; }
		int GetCols() const { m_NrOfCols; }
		std::shared_ptr<Texture2D> GetTexture() const { return m_spTexture; };
	};
}

