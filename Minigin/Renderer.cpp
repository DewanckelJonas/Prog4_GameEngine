#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, float angle, const glm::vec2& scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (scale.x < 0 && scale.y < 0)
		flip = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (scale.x < 0)
		flip = SDL_FLIP_HORIZONTAL;
	else if (scale.y < 0)
		flip = SDL_FLIP_VERTICAL;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, nullptr, flip);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, float angle, const glm::vec2& scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (scale.x < 0 && scale.y < 0)
		flip = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (scale.x < 0)
		flip = SDL_FLIP_HORIZONTAL;
	else if (scale.y < 0)
		flip = SDL_FLIP_VERTICAL;
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, nullptr, flip);
}

void dae::Renderer::RenderTexture(const Texture2D & texture, const Rect & targetRect, float angle, const glm::vec2& scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(targetRect.pos.x);
	dst.y = static_cast<int>(targetRect.pos.y);
	dst.w = static_cast<int>(targetRect.width);
	dst.h = static_cast<int>(targetRect.height);
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (scale.x < 0 && scale.y < 0)
		flip = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (scale.x < 0)
		flip = SDL_FLIP_HORIZONTAL;
	else if (scale.y < 0)
		flip = SDL_FLIP_VERTICAL;
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, nullptr, flip);
}

void dae::Renderer::RenderTexture(const Texture2D & texture, const Rect & targetRect, const Rect & sourceRect, float angle, const glm::vec2& scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(targetRect.pos.x);
	dst.y = static_cast<int>(targetRect.pos.y);
	dst.w = static_cast<int>(targetRect.width);
	dst.h = static_cast<int>(targetRect.height);

	SDL_Rect src;
	src.x = static_cast<int>(sourceRect.pos.x);
	src.y = static_cast<int>(sourceRect.pos.y);
	src.w = static_cast<int>(sourceRect.width);
	src.h = static_cast<int>(sourceRect.height);

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (scale.x < 0 && scale.y < 0)
		flip = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (scale.x < 0)
		flip = SDL_FLIP_HORIZONTAL;
	else if (scale.y < 0)
		flip = SDL_FLIP_VERTICAL;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, angle, nullptr, flip);
}
