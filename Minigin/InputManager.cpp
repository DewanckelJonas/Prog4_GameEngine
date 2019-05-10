#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "PlayerController.h"

dae::InputManager::~InputManager()
{
	for (size_t i = 0; i < m_MaxNrOfControllers; i++)
	{
		delete m_PlayerControllers[i];
	}
}

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

void dae::InputManager::Initialize()
{
	for (size_t i = 0; i < m_MaxNrOfControllers; i++)
	{
		m_PlayerControllers[i] = new PlayerController(nullptr, i);
	}
}

bool dae::InputManager::IsPressed(ControllerButton button, size_t controllerIdx) const
{
	return (m_ControllerStates[controllerIdx].Gamepad.wButtons & int(button)) != 0;
}

glm::vec2 dae::InputManager::GetJoystickMovement(size_t controllerIdx) const
{
	return glm::vec2{ m_ControllerStates[controllerIdx].Gamepad.sThumbLX, m_ControllerStates[controllerIdx].Gamepad.sThumbLY };
}

void dae::InputManager::SetCommand(ControllerButton button, const std::shared_ptr<BaseCommand>& spCommand, size_t controllerIdx)
{
	m_spButtonMappings[controllerIdx][button] = spCommand;
}

std::shared_ptr<dae::BaseCommand> dae::InputManager::GetCommand(ControllerButton button, size_t controllerIdx) const
{
	return m_spButtonMappings[controllerIdx].at(button);
}

void dae::InputManager::ClearButton(ControllerButton button, size_t controllerIdx)
{
	m_spButtonMappings[controllerIdx][button] = nullptr;
}

std::shared_ptr<dae::BaseCommand> dae::InputManager::HandleInput(size_t controllerIdx) const
{
	for (auto it = m_spButtonMappings[controllerIdx].begin(); it != m_spButtonMappings[controllerIdx].end(); it++)
	{
		if(IsPressed(it->first, controllerIdx)) 
			return m_spButtonMappings[controllerIdx].at(it->first);
	}
	return nullptr;
}

void dae::InputManager::ClearCommands(size_t controllerIdx)
{
	for (auto it = m_spButtonMappings[controllerIdx].begin(); it != m_spButtonMappings[controllerIdx].end(); it++)
	{
		it->second = nullptr;
	}
}

dae::PlayerController * dae::InputManager::GetPlayerControllers(size_t controllerIdx)
{
	return m_PlayerControllers[controllerIdx];
}

