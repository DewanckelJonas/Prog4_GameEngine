#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "Structs.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public BaseComponent
	{
	public:
		void Initialize() override{};
		void Update(float deltaTime)override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const Color& color);

		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const Color& color = {255, 255, 255, 255});
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_spFont;
		std::shared_ptr<Texture2D> m_spTexture;
		Color m_Color;
	};

}
