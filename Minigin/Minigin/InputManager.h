#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Command.h"
#include "Controller.h"
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton;
	using ControllerKey = std::pair<UINT, ControllerButton>;
	using ControllerCommandsMap = std::map<ControllerKey, std::pair<std::shared_ptr<Command>, WORD>>;

	enum class ControllerButton
	{
		ButtonA = VK_PAD_A,
		ButtonB = VK_PAD_B,
		ButtonX = VK_PAD_X,
		ButtonY = VK_PAD_Y,
		ButtonLeft = VK_PAD_DPAD_LEFT,
		ButtonRight = VK_PAD_DPAD_RIGHT,
		ButtonUp = VK_PAD_DPAD_UP,
		ButtonDown = VK_PAD_DPAD_DOWN
	};

	class InputManager : public Singleton<InputManager>
	{
	public:
		void ProcessInput();
		
		bool IsPressed(ControllerButton button, UINT& id);
		bool IsPressed(ControllerButton button, WORD keyStroke);

		void AddController();

		template<typename T>
		void AddCommand(ControllerKey cKey, WORD stroke)
		{
			auto cmd = std::make_shared<T>();
			auto pair = std::make_pair(cmd, stroke);
			m_ControllerCommands[cKey] = pair;
		}

		std::vector<std::unique_ptr<Controller>>& GetControllers();
	private:
		static UINT m_ID;

		std::vector<std::unique_ptr<Controller>> m_Controllers;

		ControllerCommandsMap m_ControllerCommands;
	};

}
