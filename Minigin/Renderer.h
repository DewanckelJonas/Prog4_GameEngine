#pragma once
#include "Singleton.h"
#include "Shapes.h"
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, float angle, SDL_Point* rotationCenter, const glm::vec2& scale) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float angle, SDL_Point* rotationCenter, const glm::vec2& scale) const;
		void RenderTexture(const Texture2D& texture, const Rect& targetRect, float angle, SDL_Point* rotationCenter, const glm::vec2& scale) const;
		void RenderTexture(const Texture2D& texture, const Rect& targetRect, const Rect& sourceRect, float angle, SDL_Point* rotationCenter, const glm::vec2& scale) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

