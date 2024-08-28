#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent)

void CharacterComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void CharacterComponent::Update(float dt)
{
	Vector2 direction{ 0, 0 };
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
	
	physics->ApplyForce(direction * speed);

	
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
		physics->ApplyForce(Vector2{0,-90000});
		

	}
	if (physics->velocity.x < -0.1f) animation->hflip = true;
	else if (physics->velocity.x > 0.1f) animation->hflip = false;

	if (Math::Abs(physics->velocity.x) > 0.1f) animation->SetAnimation("Put run anim here");
	else animation->SetAnimation("put idle anim here");

}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
	//std::cout << "player hit\n";
	//EVENT_NOTIFY(playerDead);
	if (actor->tag == "Ground") onGround = true;
	
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{
	if (actor->tag == "Ground") onGround = false;
}

void CharacterComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void CharacterComponent::Write(json_t& value)
{
	//
}
