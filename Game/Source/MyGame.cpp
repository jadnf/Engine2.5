#include "MyGame.h"
#include "Engine.h"

#include <memory>
#include <functional>

bool MyGame::Initialize()
{
	//read json
	rapidjson::Document document;
	Json::Load("Scenes/game.json", document);

	//create + init
	m_scene = std::make_unique<Scene>(m_engine);
	std::string sceneNames[] = { "Scenes/tilemap.json", "Scenes/game.json" };
	for (auto sceneName : sceneNames) {
		//read json
		rapidjson::Document document;
		Json::Load(sceneName, document);
		m_scene->Read(document);
	}


	m_scene->Read(document);
	m_scene->Initialize();

	ADD_OBSERVER(playerDead, MyGame::OnPlayerDead)
	//ADD_OBSERVER(addPoints, MyGame::AddPoints)

	
    return false;
}

void MyGame::Shutdown()
{
	m_scene->RemoveAll(true);
}

void MyGame::Update(float dt)
{
	m_scene->Update(dt);
}

void MyGame::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnPlayerDead(const Event& event)
{
	std::cout << "game player dead\n";
}

void MyGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
}
