#include "MiniginPCH.h"
#include "QBertGame.h"


#include "InputManager.h"
#include "Session.h"
#include "LevelManager.h"

QBertGame::QBertGame()
	: Minigin("QBert - Oliver Lambreghts")
{

}

void QBertGame::LoadGame() const
{
	//Session::GetInstance().BeginSession();

	LevelManager lvlManager{ m_WindowWidth };
	lvlManager.LoadMainMenu();
	
	//Session::GetInstance().EndSession();
}
