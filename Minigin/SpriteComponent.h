#pragma once
#include "BaseComponent.h"
#include "Sprite.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(const std::string& filePath, int nrOfRows, int nrOfCols);
		void Initialize() override {};
		void Update(float elapsedSec) override;
		void Render() const override;

		int GetWidth() const { return m_Sprite.GetTexture()->GetWidth(); };
		int GetHeight() const { return m_Sprite.GetTexture()->GetHeight(); };
		glm::vec2 GetScale() const { return m_Scale; }
		void SetScale(const glm::vec2& scale) { m_Scale = scale; }

	private:
		Sprite m_Sprite;
		glm::vec2 m_Scale;
		float m_ElapsedSec;
		int m_NrOfFrames;
		int m_CurrentFrame;
		float m_FrameTime;
	};
}