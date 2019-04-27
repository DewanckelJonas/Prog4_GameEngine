#include "InputManager.h"

void dae::InputManager::ProcessInput()
{
	// todo: read the input
	XInputGetState(0, &m_ControllerState);
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	// todo: return whether the given button is pressed or not.
	return (m_ControllerState.Gamepad.wButtons & int(button)) != 0;
}

void dae::InputManager::SetCommand(ControllerButton button, Command* pCommand)
{
	m_ButtonMappings[button] = pCommand;
}

dae::Command* dae::InputManager::HandleInput()
{
	for (auto it = m_ButtonMappings.begin(); it != m_ButtonMappings.end(); it++)
	{
		if(IsPressed(it->first)) return m_ButtonMappings[it->first];
	}
	return nullptr;
}
