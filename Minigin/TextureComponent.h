#pragma once
#include "BaseComponent.h"

namespace dae
{

	class Texture2D;

	class TextureComponent  final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& filePath, bool drawOnCenter = true);
		~TextureComponent() = default;
		void Initialize() override{};
		void Update(float) override {}
		void Render() const override;

		void SetTargetWidth(float width) { m_TargetWidth = width; }
		void SetTargetHeight(float height) { m_TargetHeight = height; }

	private:
		float m_TargetWidth{0};
		float m_TargetHeight{0};
		std::shared_ptr<Texture2D> m_spTexture;
		bool m_DrawOnCenter;
	};

}
