#include "Player.h"
#include "App.h"
#include "Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Scene.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Windows.h"

Player::Player(Module* listener, fPoint position, SDL_Texture* texture, Type type) : Entity(listener, position, texture, type)
{
	planeAnimation.loop = true;
	planeAnimation.PushBack({ 0, 0, 14, 20 });

	walkAnimationRight.PushBack({ 0,42, 14, 20 });
	walkAnimationRight.PushBack({ 15,42, 14, 20 });
	walkAnimationRight.PushBack({ 30,42, 14, 20 });
	walkAnimationRight.PushBack({ 45,42, 14, 20 });
	walkAnimationRight.loop = true;
	walkAnimationRight.speed = 0.1f;

	walkAnimationLeft.PushBack({ 0,21, 14, 20 });
	walkAnimationLeft.PushBack({ 15,21, 14, 20 });
	walkAnimationLeft.PushBack({ 30,21, 14, 20 });
	walkAnimationLeft.PushBack({ 45,21, 14, 20 });
	walkAnimationLeft.loop = true;
	walkAnimationLeft.speed = 0.1f;

	walkAnimationUp.PushBack({ 0,63, 14, 20 });
	walkAnimationUp.PushBack({ 15,63, 14, 20 });
	walkAnimationUp.PushBack({ 30,63, 14, 20 });
	walkAnimationUp.PushBack({ 45,63, 14, 20 });
	walkAnimationUp.loop = true;
	walkAnimationUp.speed = 0.1f;

	walkAnimationDown.PushBack({ 0,0, 14, 20 });
	walkAnimationDown.PushBack({ 15,0, 14, 20 });
	walkAnimationDown.PushBack({ 30,0, 14, 20 });
	walkAnimationDown.PushBack({ 45,0, 14, 20 });
	walkAnimationDown.loop = true;
	walkAnimationDown.speed = 0.1f;
	currentAnimation = &planeAnimation;

	collider = app->collisions->AddCollider(SDL_Rect({ (int)position.x, (int)position.y, 12, 11 }), Collider::Type::PLAYER, listener);

	jumpFx = app->audio->LoadFx("Assets/Audio/FX/jump.wav");
	doubleJumpFx = app->audio->LoadFx("Assets/Audio/FX/double_jump.wav");
	checkPointFx = app->audio->LoadFx("Assets/Audio/FX/checkpoint.wav");
	killingEnemyFx = app->audio->LoadFx("Assets/Audio/FX/enemy_death.wav");

	advice = false;
}

bool Player::Start()
{

	return true;
}

bool Player::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE)
	{
		currentAnimation = &planeAnimation;
	}
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && paredarr == false)
	{
		position.y -= 1;
		if (currentAnimation != &walkAnimationUp)
		{
			walkAnimationUp.Reset();
			currentAnimation = &walkAnimationUp;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && paredaba == false)
	{
		position.y += 1;
		if (currentAnimation != &walkAnimationDown)
		{
			walkAnimationDown.Reset();
			currentAnimation = &walkAnimationDown;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && paredizq == false)
	{
		position.x -= 1;
		if (currentAnimation != &walkAnimationLeft)
		{
			walkAnimationLeft.Reset();
			currentAnimation = &walkAnimationLeft;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && paredder == false)
	{
		position.x += 1;
		if (currentAnimation != &walkAnimationRight)
		{
			walkAnimationRight.Reset();
			currentAnimation = &walkAnimationRight;
		}
	}
		if (debug == true)
		{
			app->collisions->DebugDraw();
		}

		paredizq = false;
		paredder = false;
		paredarr = false;
		paredaba = false;

		collider->SetPos(position.x, position.y);
		cameraControl = true;
		currentAnimation->Update();
	return true;
}

bool Player::Draw()
{
	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	return true;
}

void Player::Collision(Collider* coll)
{
	if (coll->type == Collider::Type::PLAYERWALLLEFT)
	{
		paredizq = true;
	}
	if (coll->type == Collider::Type::PLAYERWALLRIGHT)
	{
		paredder = true;
	}
	if (coll->type == Collider::Type::PLAYERWALLUP)
	{
		paredarr = true;
	}
	if (coll->type == Collider::Type::PLAYERWALLDOWN)
	{
		paredaba = true;
	}



}
void Player::CleanUp()
{

}