#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	for (size_t i = 0; i < m_MaxNrOfControllers; i++)
	{
		if (XInputGetState(i, &m_ControllerStates[i]) == ERROR_SUCCESS) 
		{
			if (!m_IsControllerConnected[i])
			{
				++m_NrOfConnectedControllers;
				m_IsControllerConnected[i] = true;
				std::cout << "Controller " << i << " connected." << std::endl;
			}
		}
		else
		{
			if (m_IsControllerConnected[i])
			{
				--m_NrOfConnectedControllers;
				m_IsControllerConnected[i] = false;
				std::cout << "Controller " << i << " disconnected." << std::endl;
			}
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button, size_t controllerIdx) const
{
	return (m_ControllerStates[controllerIdx].Gamepad.wButtons & int(button)) != 0;
}

glm::vec2 dae::InputManager::GetJoystickMovement(size_t controllerIdx) const
{
	return glm::vec2{ m_ControllerStates[controllerIdx].Gamepad.sThumbLX, m_ControllerStates[controllerIdx].Gamepad.sThumbLY };
}

void dae::InputManager::SetCommand(ControllerButton button, BaseCommand* pCommand, size_t controllerIdx)
{
	m_ButtonMappings[controllerIdx][button] = pCommand;
}

dae::BaseCommand* dae::InputManager::HandleInput(size_t controllerIdx) const
{
	for (auto it = m_ButtonMappings[controllerIdx].begin(); it != m_ButtonMappings[controllerIdx].end(); it++)
	{
		if(IsPressed(it->first, controllerIdx)) 
			return m_ButtonMappings[controllerIdx].at(it->first);
	}
	return nullptr;
}

void dae::InputManager::ClearCommands(size_t controllerIdx)
{
	for (auto it = m_ButtonMappings[controllerIdx].begin(); it != m_ButtonMappings[controllerIdx].end(); it++)
	{
		it->second = nullptr;
	}
}

