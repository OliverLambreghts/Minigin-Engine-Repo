#include <ctime>
#include <iostream>
#include <Minigin.h>
#include "QBertGame.h"
#include "vld.h"

int main(int, char* []) {
	try
	{
		srand((unsigned)time(nullptr));
		QBertGame game{};
		game.Run();
	}
	catch(const std::exception& exc)
	{
		std::cout << exc.what() << '\n';
	}
	catch (...)
	{
		std::cout << "Caught an exception of an undetermined type\n";
	}
	return 0;
}