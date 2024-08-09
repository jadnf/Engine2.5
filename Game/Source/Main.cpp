#include "Engine.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string s;
	File::ReadFile("Text/Test.txt", s);
	std::cout << s;

	rapidjson::Document document;
	Json::Load("Text/Test.txt", document);

	std::string name;
	int age;
	bool isAlive;

	READ_DATA(document, age);
	READ_DATA(document, name);
	READ_DATA(document, isAlive);

	std::cout << name << std::endl;
	std::cout << age << std::endl;
	std::cout << isAlive << std::endl;

	{
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("../Assets/Images/votv.png", engine->GetRenderer());
		//texture->Load("../Assets/Images/smile.png", engine->GetRenderer());

		Transform transform{ {30,30}, 0,1 };
		std::unique_ptr<Actor> actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform(transform);
		std::unique_ptr<TextureComponent> component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		component->texture = texture;
		actor->AddComponent(std::move(component));

		res_t<Font> font = ResourceManager::Instance().Get<Font>("../Assets/Fonts/Open 24 Display St.ttf", 12);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Hello!", { 1, 1, 0, 1 });


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
			text->Draw(engine->GetRenderer(), 200, 200);

			engine->GetRenderer().EndFrame();
		}
	}
	ResourceManager::Instance().Clear();

	engine->Shutdown();

	return 0;
}