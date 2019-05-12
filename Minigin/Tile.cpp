#include "MiniginPCH.h"
#include "Tile.h"
#include "Renderer.h"

void dae::Tile::Render(const glm::vec2 & pos, float width, float height) const
{
	Rect target;
	target.pos = pos;
	target.width = width;
	target.height = height;
	if(m_spTexture)
		Renderer::GetInstance().RenderTexture(*m_spTexture, target, 0, glm::vec2{1,1});
}
