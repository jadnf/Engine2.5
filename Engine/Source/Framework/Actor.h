#pragma once
#include "../Math/Transform.h"
#include "Renderer/Renderer.h"
#include "Components/Component.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>

class Model;
class Renderer;
class Scene;

class Actor : public Object
{
public:
	Actor() = default;
	Actor(const Transform& transform) : transform{ transform } {}
	Actor(const Actor& other);

	CLASS_DECLARATION(Actor)
	CLASS_PROTOTYPE(Actor)

	void Initialize() override;
	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	std::function<void(Actor*)> OnCollisionEnter;
	std::function<void(Actor*)> OnCollisionExit;

	void AddComponent(std::unique_ptr<Component> component);

	template<typename T>
	T* GetComponent();
	template<typename T>
	std::vector<T*> GetComponents();

	bool GetDestroyed() { return destroyed; }

	friend class Scene;

	std::string tag;
	float lifespan = 0;
	bool destroyed = false;
	Transform transform;
	Scene* scene{ nullptr };
protected:
	std::vector<std::unique_ptr<Component>> m_components;
};

template<typename T>
inline T* Actor::GetComponent()
{
	for (auto& component : m_components) {
		T* result = dynamic_cast<T*>(component.get());
		if (result != nullptr) return result;
	}
	return nullptr;
}

template<typename T>
inline std::vector<T*> Actor::GetComponents()
{
	std::vector<T*> results;
	for (auto& component : m_components) {
		T* result = dynamic_cast<T*>(component.get());
		if (result != nullptr) results.puch_back(result);
	}
	return results;
}
