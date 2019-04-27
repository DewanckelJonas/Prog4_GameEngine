#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(const std::string& filePath)
{
	m_spTexture = dae::ResourceManager::GetInstance().LoadTexture(filePath);
}


void dae::TextureComponent::Render() const
{
	glm::vec3 pos = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y);
}
