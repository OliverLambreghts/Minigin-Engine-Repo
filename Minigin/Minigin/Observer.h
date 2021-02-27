#pragma once
#include "GameObject.h"

// "Points are awarded for each color change (25), defeating Coily with a flying disc (500),
// remaining discs at the end of a stage (50) and catching Slick and Sam (300 each)."

enum class Message
{
	DoNothing,
	ColorChange,
	CoilyDefeatedDisc,
	RemainingDisc,
	CaughtSlickOrSam,
	PlayerDied
};

class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(const dae::GameObject& obj, Message message) = 0;
};
