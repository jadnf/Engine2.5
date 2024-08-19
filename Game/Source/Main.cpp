#include "Engine.h"
#include "Core/Singleton.h"
#include "Core/EString.h"
#include "Components/PlayerComponent.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>

void func1(int i) { std::cout << "func1:" << i << std::endl; }
void func2(int i) { std::cout << "func2:" << i << std::endl; }
int main(int argc, char* argv[])
{
	void(*fp)(int);

	fp = &func1;

	fp(5);

	/*Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	Factory::Instance().Register<EnginePhysicsComponent>(EnginePhysicsComponent::GetTypeName());
	Factory::Instance().Register<PlayerComponent>(PlayerComponent::GetTypeName());
	Factory::Instance().Register<TextComponent>(TextComponent::GetTypeName());*/
	

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();


	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string s;
	File::ReadFile("Scenes/scene.json", s);
	//std::cout << s << std::endl;

	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());

	scene->Read(document);
	scene->Initialize();
	

	{
	


		while (!engine->IsQuit())
		{
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime());

			auto actor = scene->GetActor<Actor>("text");
			if (actor) {
				actor->transform.scale = 1.0f + ((Math::Sin(engine->GetTime().GetTime())) * 5) * engine->GetTime().GetDeltaTime();
				actor->transform.rotation += 90 * engine->GetTime().GetDeltaTime();
			}

			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			engine->GetPS().Draw(engine->GetRenderer());
			engine->GetPS().Update(engine->GetTime().GetDeltaTime());
			//engine->GetRenderer().DrawTexture(texture.get(), 0, 0, 0, 0.5f, 0.1f);
			//actor->Draw(engine->GetRenderer());
			//text->Draw(engine->GetRenderer(), 200, 200);
			scene->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}
	scene->RemoveAll();
	ResourceManager::Instance().Clear();

	engine->Shutdown();

	return 0;
}