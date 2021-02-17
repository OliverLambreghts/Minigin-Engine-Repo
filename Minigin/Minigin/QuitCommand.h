#pragma once
#include "Command.h"

class QuitCommand final : public Command
{
public:
	virtual ~QuitCommand() = default;
	virtual void Execute() override
	{
		exit(0);
	}
};