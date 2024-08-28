#include "Engine.h"
#include "MyGame.h"
#include "Core/Singleton.h"
#include "Core/EString.h"
#include "Components/PlayerComponent.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[])
{
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	std::unique_ptr<MyGame> game = std::make_unique<MyGame>(engine.get());
	game->Initialize();

	while (!engine->IsQuit())
	{
		engine->Update();
		game->Update(engine->GetTime().GetDeltaTime());

		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		game->Draw(engine->GetRenderer());

		engine->GetRenderer().EndFrame();
	}
	
	game->Shutdown();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}