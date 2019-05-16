#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(const std::string& filePath, bool drawOnCenter)
	:m_DrawOnCenter(drawOnCenter)
{
	m_spTexture = dae::ResourceManager::GetInstance().LoadTexture(filePath);
}


void dae::TextureComponent::Render() const
{
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	auto pos = transform->GetPosition();
	float angle = transform->GetRotation();
	auto scale = transform->GetScale();
	Rect targetRect{ {pos.x, pos.y }, float(m_spTexture->GetWidth()), float(m_spTexture->GetHeight()) };
	if (m_TargetHeight > 0.f && m_TargetWidth > 0)
	{
		targetRect.width = m_TargetWidth;
		targetRect.height = m_TargetHeight;
	}
	if (m_DrawOnCenter)
	{
		targetRect.pos.x -= targetRect.width / 2;
		targetRect.pos.y -= targetRect.height / 2;
	}

	dae::Renderer::GetInstance().RenderTexture(*m_spTexture, targetRect, angle, scale);
}
