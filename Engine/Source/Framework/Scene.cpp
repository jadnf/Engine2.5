#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Model.h"
#include "Core/Factory.h"
#include "Components\CollisionComponent.h"
#include "Core/EAssert.h"
#include <algorithm>

void Scene::Initialize()
{
	for (auto& actor : m_actors) {
		actor->Initialize();
	}
}

Scene::Scene(const Scene& other)
{
	ASSERT(false);
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, m_actors) && GET_DATA(value, m_actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, m_actors).GetArray()) {
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			bool prototype = false;
			READ_DATA(actorValue, prototype);

			if (prototype) {
				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
			else {
				AddActor(std::move(actor));

			}
		}
	}
}

void Scene::Write(json_t& value)
{
}

void Scene::Update(float dt)
{
	// update
	for (auto& actor : m_actors) {
		if (actor->active) actor->Update(dt);
	}
	//destroy
	
	std::erase_if(m_actors, [](auto& actor) { return actor->destroyed; });
	

	//collision
	/*for (auto& actor1 : m_actors) {
		CollisionComponent* collision1 = actor1->GetComponent<CollisionComponent>();
		if (!collision1) continue;

		for (auto& actor2 : m_actors) {
			//dont check with self
			if (actor1 == actor2) continue;
			
			CollisionComponent* collision2 = actor2->GetComponent<CollisionComponent>();
			if (!collision2) continue;

			if (collision1->CheckCollision(collision2)) {
				//std::cout << "Hit!\n";
				if (actor1->OnCollisionEnter) actor1->OnCollisionEnter(actor2.get());
				if (actor2->OnCollisionEnter) actor2->OnCollisionEnter(actor1.get());
			}
		}
	}*/
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : m_actors) {
		if (actor->active) actor->Draw(renderer);
	}
	
}

void Scene::AddActor(std::unique_ptr<Actor> actor, bool initialize)
{
	actor->scene = this;
	if (initialize) actor->Initialize();
	m_actors.push_back(std::move(actor));
}

void Scene::RemoveAll(bool force) {
	std::erase_if(m_actors, [force](auto& actor) { return (force || !actor->persistent); });
}

