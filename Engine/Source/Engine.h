#pragma once
//--core
#include "Engine.h"
#include "Core/EngineTime.h"
#include "Core/EAssert.h"
#include "Core/EFile.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "Core/Singleton.h"
#include "Core/EString.h"
//--systems
// 
//renderer
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Model.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Texture.h"
//input
#include "Input/Input.h"
//audio
#include "Audio/Audio.h"
//--Math
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Math/Rect.h"

//framework
#include "Framework/Actor.h"
#include "Framework/Scene.h"

//resources 
#include "Resource/Resource.h"
#include "Resource/ResourceManager.h"

//event system
#include "Event/EventSystem.h"

//components
#include "Components/TextureComponent.h"
#include "Components/TextureAnimationComponent.h"
#include "Components/EnginePhysicsComponent.h"
#include "Components/TextComponent.h"

//physics
#include "Physics/Physics.h"

//files

#include "Game.h"
#include <SDL.h>
#include <fmod.hpp>
#include <iostream>
#include <memory>

#define RENDERER g_engine.GetRenderer()

class Engine {
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	ParticleSystem& GetPS() { return *m_particleSystem; }
	Physics& GetPhysics() { return *m_physics; }

	Time& GetTime() { return *m_time; }



	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::unique_ptr<Time> m_time;
	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;
	std::unique_ptr<ParticleSystem> m_particleSystem;
	std::unique_ptr<Physics> m_physics;
};

