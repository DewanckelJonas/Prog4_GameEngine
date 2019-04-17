#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextComponent.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto pBackGroundGameObject = new GameObject();
	auto pBackGroundTextureComp = new TextureComponent("background.jpg");
	pBackGroundGameObject->AddComponent(pBackGroundTextureComp);
	scene.Add(pBackGroundGameObject);

	auto pLogoObject = new GameObject();
	auto pLogoTextureComp = new TextureComponent("logo.png");
	pLogoObject->AddComponent(pLogoTextureComp);
	pLogoObject->SetPosition(216, 180, 0);
	scene.Add(pLogoObject);

	auto pTextObject = new GameObject();
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto pTextComponent = new TextComponent("Programming 4 Assignment", font);
	pTextObject->AddComponent(pTextComponent);
	pTextObject->SetPosition(80, 20, 0); 
	scene.Add(pTextObject);

	auto pFPSObject = new GameObject();
	auto pFPSComponent = new FPSComponent();
	pTextComponent = new TextComponent("60", font, {255, 255, 0});
	pFPSObject->AddComponent(pFPSComponent);
	pFPSObject->AddComponent(pTextComponent);
	scene.Add(pFPSObject);

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto prevFrameTime = std::chrono::high_resolution_clock::now();
		float accuTime = 0.f;
		const float msPerUpdate = 1.f/60.f;
		bool doContinue = true;

		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - prevFrameTime).count();
			prevFrameTime = currentTime;
			accuTime += deltaTime;
			doContinue = input.ProcessInput();

			while (accuTime >= msPerUpdate)
			{
				sceneManager.FixedUpdate(msPerUpdate);
				accuTime -= msPerUpdate;
			}

			sceneManager.Update(deltaTime);
			renderer.Render();

		}
	}

	Cleanup();
}
