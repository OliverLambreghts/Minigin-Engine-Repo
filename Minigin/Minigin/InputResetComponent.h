#pragma once
#include <SDL_keycode.h>
#include "Command.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "Scene.h"

class InputResetComponent final : public InputComponent
{
public:
	InputResetComponent(const Scene& scene);
	virtual ~InputResetComponent() = default;
	InputResetComponent(const InputResetComponent& other) = delete;
	InputResetComponent(InputResetComponent&& other) = delete;
	void operator=(const InputResetComponent& rhs) = delete;
	void operator=(const InputResetComponent&& rhs) = delete;

	virtual void Update(float elapsedSec, dae::GameObject & obj) override;

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
private:
	const Scene& m_Scene;
	ControllerCommandsMap m_ControllerCommands;
	std::map<SDL_Keycode, std::pair<Uint32, std::shared_ptr<Command>>> m_KeyboardCommands;
	bool m_HasAddedCMDS;
};
