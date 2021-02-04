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
	planeAnimation.PushBack({ 0, 0, 13, 19 });

	walkAnimationRight.PushBack({ 13,0, 12, 11 });
	walkAnimationRight.PushBack({ 26,0, 12, 11 });
	walkAnimationRight.PushBack({ 39,0, 12, 11 });
	walkAnimationRight.PushBack({ 53,0, 14, 11 });
	walkAnimationRight.loop = true;
	walkAnimationRight.speed = 0.1f;

	walkAnimationLeft.PushBack({ 13,12, 12, 11 });
	walkAnimationLeft.PushBack({ 26,12, 12, 11 });
	walkAnimationLeft.PushBack({ 39,12, 12, 11 });
	walkAnimationLeft.PushBack({ 53,12, 14, 11 });
	walkAnimationLeft.loop = true;
	walkAnimationLeft.speed = 0.1f;

	jumpAnimation.PushBack({ 1, 23, 12, 12 });
	jumpAnimation.loop = true;

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
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && paredarr == false)
	{
		position.y -= 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && paredaba == false)
	{
		position.y += 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && paredizq == false)
	{
		position.x -= 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && paredder == false)
	{
		position.x += 1;
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