#include <ctime>
#include <Minigin.h>
#include "QBertGame.h"
//#include "vld.h"

int main(int, char* []) {
	srand((unsigned)time(nullptr));
	QBertGame game;
	//_CrtSetBreakAlloc(634);
	game.Run();
	return 0;
}