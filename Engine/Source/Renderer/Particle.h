#pragma once
#include "../Math/Vector2.h"
#include "Renderer.h"

struct Particle{
	struct Data {
		Vector2 position{ 0, 0 };
		Vector2 velocity{ 0, 0 };
		float lifespan = 0;
		int r = 255;
		int g = 255;
		int b = 255;
		int a = 0;
		bool isActive{ true };
	};

	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	float lifespan = 0;
	int r = 255;
	int g = 255;
	int b = 255;
	int a = 0;
	bool isActive{ true };

	Particle() = default;

	Particle(Vector2 position, Vector2 velocity) : position{ position }, velocity{ velocity } {}
	Particle(Vector2 position, Vector2 velocity, float lifespan) : position{ position }, velocity{ velocity }, lifespan{ lifespan } {}
	Particle(Vector2 position, Vector2 velocity, float lifespan, int r, int g, int b, int a) : position{ position }, velocity{ velocity }, lifespan{ lifespan }, r{ r }, g{ g }, b{ b }, a{ a } {}
	
	void Initialize(const Data& data);

	void Update(float dt);
	void Draw(Renderer& renderer);
};
