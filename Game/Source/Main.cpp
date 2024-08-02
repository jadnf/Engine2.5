#include "Engine.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	while (!engine->IsQuit())
	{
		engine->Update();

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();
		engine->GetPS().Draw(engine->GetRenderer());
		engine->GetPS().Update(engine->GetTime().GetDeltaTime());

		engine->GetRenderer().EndFrame();
	}

	engine->Shutdown();

	return 0;
}