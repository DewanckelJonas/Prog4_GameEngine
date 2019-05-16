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
		SpriteComponent(const std::string& filePath, int nrOfRows, int nrOfCols, float targetWidth = 0.f, float targetHeight = 0.f, bool drawOnCenter = true);
		void Initialize() override {};
		void Update(float elapsedSec) override;
		void Render() const override;

		int GetSpriteWidth() const { return m_Sprite.GetTexture()->GetWidth(); };
		int GetSpriteHeight() const { return m_Sprite.GetTexture()->GetHeight(); };
		void SetTargetWidth(float width) { m_TargetWidth = width; }
		void SetTargetHeight(float height) { m_TargetHeight = height; }

	private:
		Sprite m_Sprite;
		float m_ElapsedSec;
		int m_NrOfFrames;
		int m_CurrentFrame;
		float m_FrameTime;
		bool m_DrawOnCenter;
		float m_TargetWidth;
		float m_TargetHeight;
	};
}