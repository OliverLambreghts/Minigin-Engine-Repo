#pragma once
#include <string>
#include "MiniginLibType.h"
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		Minigin(const std::string& programName = "Minigin Engine");
		void Initialize();
		virtual void LoadGame() const;
		void Cleanup();
		MINIGIN_ENTRY void Run();
		void Update(float elapsedSec);
	protected:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		int m_WindowWidth, m_WindowHeight;
		std::string m_ProgramName;
	};
}