#ifndef _PLAYERENTITY_H_
#define _PLAYERENTITY_H_

#include "Point.h"
#include "Window.h"
#include "Entity.h"
#include "Animation.h"
#include "DynArray.h"
#include "Timer.h"


struct SDL_Texture;
struct Collider;

class PlayerEntity : Entity
{
public:
	PlayerEntity(Module* listener, fPoint position, SDL_Texture* texture, Type type);

	bool Start();

	bool Update(float dt);

	bool Draw();

	void Collision(Collider* coll);

	void CleanUp();

	bool changed1 = false;
	bool changed2 = false;
	bool changed3 = false;	
private:

	Animation planeAnimation;
	Animation letitiaXeringa;
	Animation adaComputer;
	Animation towerAnimation;


	Animation* currentAnimation;

	Collider* footCollider;

	SDL_Texture* eButton;

	uint jumpFx = 0;
	uint doubleJumpFx = 0;
	uint checkPointFx = 0;
	uint killingEnemyFx = 0;

	float vely = 0.0f;
	float velx = 0.0f;
	float gravity = 0.2f;

	bool onGround = false;
	bool godMode = false;
	bool debug;
	bool playerJumping = true;
	bool doubleJump = false;
	bool cameraControl = false;
	bool winCondition = false;
	bool deathCondition = false;
	bool advice;
	bool minigame;
	bool rapidfire = false;
	bool doubleshot = false;

	int scoreFont = -1;
	char scoreText[10] = { "\0" };
	bool a = true;


	Timer timer;
};

#endif // _GROUNDENEMY_H_