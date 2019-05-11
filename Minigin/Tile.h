#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <memory>

namespace dae
{
	class Texture2D;
	class Tile
	{
	public:
		Tile(const std::shared_ptr<Texture2D> spTexture) :m_spTexture(spTexture){};

		void Render(const glm::vec2& pos, float width, float height) const;
	private:
		std::shared_ptr<Texture2D> m_spTexture;
	};
}


