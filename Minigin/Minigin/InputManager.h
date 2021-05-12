#pragma once
#include <map>
#include <memory>
#include <SDL_events.h>
#include <vector>

#include "Controller.h"
#include "GameObject.h"
#include "Singleton.h"

class Command;

namespace dae
{
	enum class ControllerButton;
	using ControllerKey = std::pair<UINT, ControllerButton>;
	using ControllerCommandsMap = std::map<ControllerKey, std::pair<std::shared_ptr<Command>, WORD>>;

	enum class ControllerButton
	{
		ButtonA = 0x5800,
		ButtonB = 0x5801,
		ButtonX = 0x5802,
		ButtonY = 0x5803,
		ButtonLeft = 0x5812,
		ButtonRight = 0x5813,
		ButtonUp = 0x5810,
		ButtonDown = 0x5811
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool ProcessKeyboardInput();
		
		bool IsPressed(ControllerButton button, UINT& id);
		bool IsPressed(ControllerButton button, UINT id, WORD keyStroke);

		void AddController();

		template<typename T>
		void AddCommand(ControllerKey cKey, WORD stroke)
		{
			auto cmd = std::make_shared<T>();
			auto pair = std::make_pair(cmd, stroke);
			m_ControllerCommands[cKey] = pair;
		}

		template<typename T>
		void AddCommand(ControllerKey cKey, WORD stroke, std::shared_ptr<GameObject>& obj)
		{
			auto cmd = std::make_shared<T>(obj);
			auto pair = std::make_pair(cmd, stroke);
			m_ControllerCommands[cKey] = pair;
		}

		template<typename T>
		void AddCommand(SDL_Keycode kKey, Uint32 stroke, std::shared_ptr<GameObject>& obj)
		{
			auto cmd = std::make_shared<T>(obj);
			auto pair = std::make_pair(stroke, cmd);
			m_KeyboardCommands[kKey] = pair;
		}

		void AddCommands(const ControllerCommandsMap& controllerCmds)
		{
			m_ControllerCommands = controllerCmds;
		}

		void AddCommands(const std::map<SDL_Keycode, std::pair<Uint32, std::shared_ptr<Command>>>& keyboardCmds)
		{
			m_KeyboardCommands = keyboardCmds;
		}

		void ClearCommands();

		std::vector<std::unique_ptr<Controller>>& GetControllers();
	private:
		static UINT m_ID;

		std::vector<std::unique_ptr<Controller>> m_Controllers;

		ControllerCommandsMap m_ControllerCommands;

		std::map<SDL_Keycode, std::pair<Uint32, std::shared_ptr<Command>>> m_KeyboardCommands;
	};

}
