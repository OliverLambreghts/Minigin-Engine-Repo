#include "MiniginPCH.h"
#include "QBertGame.h"


#include "InputManager.h"
#include "Session.h"
#include "LevelManager.h"

QBertGame::QBertGame()
	: dae::Minigin("QBert - Oliver Lambreghts" )
{

}

void QBertGame::LoadGame() const
{
	LevelManager lvlManager{ m_WindowWidth };
	lvlManager.LoadMainMenu();
}
