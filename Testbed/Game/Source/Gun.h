#pragma once
#ifndef __GUN_H__
#define __GUN_H__

#include "Point.h"
#include "Entity.h"
#include "Animation.h"
#include "DynArray.h"
#include "Timer.h"

struct SDL_Texture;
struct Collider;

class Gun : Entity
{
public:
	Gun(Module* listener, fPoint position, SDL_Texture* texture, Type type);

	bool Start();

	bool Update(float dt);

	bool Draw();

	void Collision(Collider* coll);

	void CleanUp();

private:

	Animation* currentAnimation;
	Animation bulet1;
	Animation bulet2;
	Animation bulet3;

	SDL_Texture* tex;

	fPoint vDestination;
	float modDestination;
	fPoint normDestination;
	int x;
	int y;

	float speedX;
	float speedY;

	Timer timer;

	bool stopu;
};


#endif // __SCENE_H__
