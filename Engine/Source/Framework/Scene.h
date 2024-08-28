#pragma once
#include "Object.h"
#include <list>
#include <memory>

class Renderer;
class Actor;
class Game;
class Engine;

class Scene : public Object{
public:
	Scene(Engine* engine, Game* game = nullptr) : m_game{ game }, engine {engine} {}
	Scene(const Scene& other);

	CLASS_DECLARATION(Scene)
	CLASS_PROTOTYPE(Scene)


	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor, bool initialize = false);

	void RemoveAll(bool force = false);

	template<typename T> T* GetActor();
	template<typename T> T* GetActor(const std::string& name);

	Engine* engine{ nullptr };
	Game* m_game{ nullptr };
	void Initialize() override;


protected:
	std::list<std::unique_ptr<Actor>> m_actors;

	// Inherited via Object
};
template<typename T>
T* Scene::GetActor() {
	for (auto& actor : m_actors) {
		T* result = dynamic_cast<T*>(actor.get());
		if (result != nullptr) return result;
	}

	return nullptr;
}

template<typename T>
inline T* Scene::GetActor(const std::string& name)
{
	for (auto& actor : m_actors) {
		T* result = dynamic_cast<T*>(actor.get());
		if (result != nullptr && IsEqualIgnoreCase(result->name, name)) return result;
	}

	return nullptr;
}
