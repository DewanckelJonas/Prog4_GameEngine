#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "Singleton.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <memory>
#include <SDL.h>

//reference: http://gameprogrammingpatterns.com/command.html


namespace dae
{
	class PlayerController;
	class BaseCommand;
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y
	};

	enum class MouseButton
	{
		Left = SDL_BUTTON_LEFT,
		Right = SDL_BUTTON_RIGHT,
		Middle = SDL_BUTTON_MIDDLE
	};

	class InputManager : public Singleton<InputManager>
	{ 
	public:
		~InputManager();
		bool ProcessInput();
		void Initialize();
		bool IsPressed(ControllerButton button, size_t controllerIdx = 0) const;
		glm::vec2 GetJoystickMovement(size_t controllerIdx = 0) const;
		void SetCommand(ControllerButton button, const std::shared_ptr<BaseCommand>& pCommand, size_t controllerIdx = 0);
		std::shared_ptr<BaseCommand> GetCommand(ControllerButton button, size_t controllerIdx = 0) const;
		void ClearButton(ControllerButton button, size_t controllerIdx = 0);
		std::shared_ptr<BaseCommand> HandleInput(size_t controllerIdx) const;
		size_t GetMaxNrOfControllers() { return m_MaxNrOfControllers; }
		void ClearCommands(size_t controllerIdx);
		PlayerController* GetPlayerControllers(size_t controllerIdx);

		glm::vec2 GetMousePosition() { return m_MousePos; }
		bool IsMouseButtonPressed(MouseButton button) const;

	private:
		//Controller and commands
		unsigned short m_NrOfConnectedControllers{};
		static const size_t m_MaxNrOfControllers{ 4 };
		PlayerController* m_PlayerControllers[m_MaxNrOfControllers];
		XINPUT_STATE m_ControllerStates[m_MaxNrOfControllers];
		bool m_IsControllerConnected[m_MaxNrOfControllers];
		std::map<ControllerButton, std::shared_ptr<BaseCommand>> m_spButtonMappings[m_MaxNrOfControllers];

		//Mouse
		glm::vec2 m_MousePos{};
		std::map<MouseButton, bool> m_MouseButtonStates;
	};

}
