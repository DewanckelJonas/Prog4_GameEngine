#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_pTexture = texture;
}
