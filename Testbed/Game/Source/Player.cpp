#include "Player.h"

#include "App.h"
#include"Input.h"
#include "Render.h"
#include "Collisions.h"
#include "Collider.h"
#include "Audio.h"
#include "EntityManager.h"
#include "Scene.h"
#include "Win.h"
#include "ModuleFonts.h"

Player::Player(Module* listener, fPoint position, float mass, float weight, float height, SDL_Texture* texture, Type type) : Body(listener, position, mass, weight, height, texture, type)
{
	leftAnimation.loop = true;
	leftAnimation.PushBack({ 21, 17, 21, 26 });
	leftAnimation.PushBack({ 20, 75, 22, 26 });
	leftAnimation.PushBack({ 20, 135, 22, 26 });
	leftAnimation.PushBack({ 20, 195, 22, 26 });
	leftAnimation.PushBack({ 20, 256, 22, 25 });
	leftAnimation.PushBack({ 20, 316, 22, 25 });
	leftAnimation.PushBack({ 20, 376, 22, 25 });
	leftAnimation.PushBack({ 20, 436, 22, 25 });
	leftAnimation.PushBack({ 20, 496, 22, 25 });
	leftAnimation.PushBack({ 20, 556, 22, 25 });
	leftAnimation.PushBack({ 20, 616, 22, 25 });
	leftAnimation.PushBack({ 20, 676, 22, 25 });
	leftAnimation.PushBack({ 20, 736, 22, 25 });
	leftAnimation.PushBack({ 20, 796, 22, 25 });
	leftAnimation.PushBack({ 20, 856, 22, 26 });
	leftAnimation.PushBack({ 20, 916, 22, 26 });
	leftAnimation.PushBack({ 20, 976, 22, 25 });
	leftAnimation.PushBack({ 19, 1037, 23, 25 });
	leftAnimation.PushBack({ 20, 976, 22, 25 });
	leftAnimation.PushBack({ 20, 915, 22, 26 });
	leftAnimation.PushBack({ 20, 855, 22, 26 });
	leftAnimation.PushBack({ 20, 796, 22, 25 });
	leftAnimation.PushBack({ 20, 736, 22, 25 });
	leftAnimation.PushBack({ 20, 676, 22, 25 });
	leftAnimation.PushBack({ 20, 616, 22, 25 });
	leftAnimation.PushBack({ 20, 556, 22, 25 });
	leftAnimation.PushBack({ 20, 496, 22, 25 });
	leftAnimation.PushBack({ 20, 376, 22, 25 });
	leftAnimation.PushBack({ 20, 316, 22, 25 });
	leftAnimation.PushBack({ 20, 256, 22, 25 });
	leftAnimation.PushBack({ 20, 195, 22, 26 });
	leftAnimation.PushBack({ 20, 135, 22, 26 });
	leftAnimation.PushBack({ 20, 75, 22, 26 });
	leftAnimation.PushBack({ 21, 16, 21, 25 });
	leftAnimation.speed = 0.1f;

	rightAnimation.loop = true;
	rightAnimation.PushBack({ 61, 17, 21, 26 });
	rightAnimation.PushBack({ 61, 75, 22, 26 });
	rightAnimation.PushBack({ 61, 135, 22, 26 });
	rightAnimation.PushBack({ 61, 195, 22, 26 });
	rightAnimation.PushBack({ 61, 256, 22, 25 });
	rightAnimation.PushBack({ 61, 316, 22, 25 });
	rightAnimation.PushBack({ 61, 376, 22, 25 });
	rightAnimation.PushBack({ 61, 436, 22, 25 });
	rightAnimation.PushBack({ 61, 496, 22, 25 });
	rightAnimation.PushBack({ 61, 556, 22, 25 });
	rightAnimation.PushBack({ 61, 616, 22, 25 });
	rightAnimation.PushBack({ 61, 676, 22, 25 });
	rightAnimation.PushBack({ 61, 736, 22, 25 });
	rightAnimation.PushBack({ 61, 796, 22, 25 });
	rightAnimation.PushBack({ 61, 856, 22, 26 });
	rightAnimation.PushBack({ 61, 916, 22, 26 });
	rightAnimation.PushBack({ 61, 976, 22, 25 });
	rightAnimation.PushBack({ 61, 1037, 23, 25 });
	rightAnimation.PushBack({ 61, 976, 22, 25 });
	rightAnimation.PushBack({ 61, 915, 22, 26 });
	rightAnimation.PushBack({ 61, 855, 22, 26 });
	rightAnimation.PushBack({ 61, 796, 22, 25 });
	rightAnimation.PushBack({ 61, 736, 22, 25 });
	rightAnimation.PushBack({ 61, 676, 22, 25 });
	rightAnimation.PushBack({ 61, 616, 22, 25 });
	rightAnimation.PushBack({ 61, 556, 22, 25 });
	rightAnimation.PushBack({ 61, 496, 22, 25 });
	rightAnimation.PushBack({ 61, 376, 22, 25 });
	rightAnimation.PushBack({ 61, 316, 22, 25 });
	rightAnimation.PushBack({ 61, 256, 22, 25 });
	rightAnimation.PushBack({ 61, 195, 22, 26 });
	rightAnimation.PushBack({ 61, 135, 22, 26 });
	rightAnimation.PushBack({ 61, 75, 22, 26 });
	rightAnimation.PushBack({ 61, 16, 21, 25 });
	rightAnimation.speed = 0.1f;

	currentAnimation = &rightAnimation;

	collider = collider = app->collisions->AddCollider(SDL_Rect{ (int)position.x,(int)position.y, 22, 25 }, Collider::Type::PLAYER, listener);

	dirVelo = { 1.0f,0 };
	surface = 1;
	cd = 1;
	velRelative = 20;
	volume = 0;
	inWater = false;

	char lookupTable[] = { "! @,_./0123456789$:< ?abcdefghijklmnopqrstuvwxyzA" };
	scoreFont = app->fonts->Load("Assets/Font/fonts.png", lookupTable, 2);
	app->activeFonts++; app->totalFonts++;
}

bool Player::Start()
{
	return true;
}

bool Player::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		
	}
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && isJumping == false)
	{
		
	}
	if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
	{

	}


	

	return true;
}

bool Player::Draw()
{
	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	app->render->DrawTexture(app->scene->waterBckGrnd, 183, 200, NULL);

	app->fonts->BlitText(50, 50, scoreFont, "score:");
	sprintf_s(scoreText, 10, "%4d", app->entityManager->score);
	app->fonts->BlitText(250, 50, scoreFont, scoreText);

	return true;
}

void Player::Collision(Collider* coll)
{
	if (coll->type == Collider::Type::FLOOR)
	{
		

		
	}
	
}

void Player::CleanUp()
{

}