#pragma once
struct SDL_Texture;

namespace dae
{
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		int GetWidth() { return m_Width; };
		int GetHeight() { return m_Height; };

	private:
		SDL_Texture* m_pTexture;
		int m_Width, m_Height;
	};
}
