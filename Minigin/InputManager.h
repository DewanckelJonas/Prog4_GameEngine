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

//reference: http://gameprogrammingpatterns.com/command.html

namespace dae
{
	class BaseCommand;
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y
	};

	class InputManager : public Singleton<InputManager>
	{ 
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button, size_t controllerIdx = 0) const;
		glm::vec2 GetJoystickMovement(size_t controllerIdx = 0) const;
		void SetCommand(ControllerButton button, BaseCommand* pCommand, size_t controllerIdx = 0);
		BaseCommand* HandleInput(size_t controllerIdx) const;
		size_t GetMaxNrOfControllers() { return m_MaxNrOfControllers; }
		void ClearCommands(size_t controllerIdx);

	private:
		unsigned short m_NrOfConnectedControllers{};
		static const size_t m_MaxNrOfControllers{ 4 };
		XINPUT_STATE m_ControllerStates[m_MaxNrOfControllers];
		bool m_IsControllerConnected[m_MaxNrOfControllers];
		std::map<ControllerButton, BaseCommand*> m_ButtonMappings[m_MaxNrOfControllers];
	};

}
