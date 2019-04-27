#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "Singleton.h"

//reference: http://gameprogrammingpatterns.com/command.html

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y
	};

	class Command
	{
	public:
		Command(const std::function<void()>& callBack) 
			: m_CallBack(callBack) {}
		template<class T>
		Command(const std::function<void(T*)>& callBack, T* thisPointer)
			: m_CallBack(std::bind(callBack, thisPointer))
		void Execute() { m_CallBack(); };
	private:
		std::function<void()> m_CallBack;
	};

	class InputManager : public Singleton<InputManager>
	{ 
	private:
		XINPUT_STATE m_ControllerState;

		std::map<ControllerButton, Command*> m_ButtonMappings;

	public:
		void ProcessInput();
		bool IsPressed(ControllerButton button) const;
		void SetCommand(ControllerButton button, Command* pCommand);
		Command* HandleInput();
	};

}
