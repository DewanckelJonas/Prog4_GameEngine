#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const Color& color)
	: m_NeedsUpdate(true), m_Text(text), m_spFont(font), m_spTexture(nullptr), m_Color(color)
{ }

void dae::TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_NeedsUpdate)
	{
		m_NeedsUpdate = false;
		const auto surf = TTF_RenderText_Blended(m_spFont->GetFont(), m_Text.c_str(), SDL_Color{m_Color.r, m_Color.g, m_Color.b, m_Color.a});
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		const auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_spTexture = std::make_shared<Texture2D>(texture);
	}
}

void dae::TextComponent::Render() const
{
	if (m_spTexture)
	{
		const auto pos = GetGameObject()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const Color& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}


