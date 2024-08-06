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
	{
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("../Assets/Images/smile.png", engine->GetRenderer());
		//texture->Load("../Assets/Images/smile.png", engine->GetRenderer());

		Transform transform{ {30,30}, 0,1 };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform);
		std::unique_ptr<TextureComponent> component = std::make_unique<TextureComponent>();
		component->texture = texture;
		actor->AddComponent(std::move(component));


		while (!engine->IsQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			engine->GetPS().Draw(engine->GetRenderer());
			engine->GetPS().Update(engine->GetTime().GetDeltaTime());
			engine->GetRenderer().DrawTexture(texture.get(), 0, 0, 0, 0.5f, 0.1f);
			actor->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}
	ResourceManager::Instance().Clear();

	engine->Shutdown();

	return 0;
}