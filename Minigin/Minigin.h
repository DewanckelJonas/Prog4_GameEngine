#pragma once
#pragma comment(lib,"xinput.lib")
#include "SDL.h"

struct SDL_Window;

namespace dae
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		virtual void LoadGame() const = 0;
		void Run();
	private:
		void Initialize();
		void Cleanup();
	};
}