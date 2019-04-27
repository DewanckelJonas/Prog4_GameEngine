#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"

dae::SpriteComponent::SpriteComponent(const std::string & filePath, int nrOfRows, int nrOfCols)
	: m_Sprite(dae::ResourceManager::GetInstance().LoadTexture(filePath), nrOfRows, nrOfCols)
	, m_Scale(1,1)
	, m_NrOfFrames(nrOfRows * nrOfCols)
	, m_CurrentFrame(0)
	, m_FrameTime(0.1f)
	, m_ElapsedSec(0)
{
}

void dae::SpriteComponent::Update(float elapsedSec)
{
	if (m_ElapsedSec > m_FrameTime)
	{
		m_ElapsedSec -= m_FrameTime;
		m_CurrentFrame++;
		m_CurrentFrame %= m_NrOfFrames;
	}
}

void dae::SpriteComponent::Render() const
{
	glm::vec3 pos = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	Rect targetRect{ {pos.x, pos.y }, GetWidth(), GetHeight() };
	Rect sourceRect;
	int currentRow{ m_CurrentFrame / m_Sprite.GetRows() };
	int currentCol{ m_CurrentFrame % m_Sprite.GetCols };
	sourceRect.width = m_Sprite.GetTexture()->GetWidth() / m_Sprite.GetCols();
	sourceRect.height = m_Sprite.GetTexture()->GetHeight() / m_Sprite.GetRows();
	sourceRect.pos.x = m_Sprite.GetTexture()->GetWidth() * currentCol;
	sourceRect.pos.y = m_Sprite.GetTexture()->GetHeight()*(m_Sprite.GetCols() - 1 - currentCol);
	Renderer::GetInstance().RenderTexture(*m_Sprite.GetTexture(), targetRect, sourceRect);
}

