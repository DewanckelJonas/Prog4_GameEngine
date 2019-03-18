#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filePath)
{
	m_spTexture = dae::ResourceManager::GetInstance().LoadTexture(filePath);
}


void dae::TextureComponent::Render() const
{
	auto pos = GetGameObject()->GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y);
}
