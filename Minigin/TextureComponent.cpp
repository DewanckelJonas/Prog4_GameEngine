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
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	auto pos = transform->GetPosition();
	float angle = transform->GetRotation();
	auto scale = transform->GetScale();

	dae::Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y, angle, scale);
}
