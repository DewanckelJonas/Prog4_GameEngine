#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"

dae::SpriteComponent::SpriteComponent(const std::string & filePath, int nrOfRows, int nrOfCols, bool drawOnCenter)
	: m_Sprite(dae::ResourceManager::GetInstance().LoadTexture(filePath), nrOfRows, nrOfCols)
	, m_Scale(1,1)
	, m_NrOfFrames(nrOfRows * nrOfCols)
	, m_CurrentFrame(0)
	, m_FrameTime(0.1f)
	, m_ElapsedSec(0)
	, m_DrawOnCenter(drawOnCenter)
{
}

void dae::SpriteComponent::Update(float deltaTime)
{
	m_ElapsedSec += deltaTime;
	if (m_ElapsedSec > m_FrameTime)
	{
		m_ElapsedSec -= m_FrameTime;
		m_CurrentFrame++;
		m_CurrentFrame %= m_NrOfFrames;
	}
}

void dae::SpriteComponent::Render() const
{
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	auto pos = transform->GetPosition();
	float angle = transform->GetRotation();
	auto scale = transform->GetScale();
	Rect sourceRect;
	int currentRow{ m_CurrentFrame / m_Sprite.GetCols() };
	int currentCol{ m_CurrentFrame % m_Sprite.GetCols() };
	sourceRect.width = m_Sprite.GetTexture()->GetWidth() / float(m_Sprite.GetCols());
	sourceRect.height = float(m_Sprite.GetTexture()->GetHeight()) / m_Sprite.GetRows();
	sourceRect.pos.x = sourceRect.width * currentCol;
	sourceRect.pos.y = sourceRect.height*(m_Sprite.GetRows() - 1 - currentRow);
	Rect targetRect{ {pos.x, pos.y }, sourceRect.width, sourceRect.height };
	if(m_DrawOnCenter)
	{
		targetRect.pos.x -= targetRect.width / 2;
		targetRect.pos.y -= targetRect.height / 2;
	}
	Renderer::GetInstance().RenderTexture(*m_Sprite.GetTexture(), targetRect, sourceRect, angle, scale);
}

