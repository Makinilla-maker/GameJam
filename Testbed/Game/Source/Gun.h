#pragma once
#ifndef __GUN_H__
#define __GUN_H__

#include "Point.h"
#include "Entity.h"
#include "Animation.h"
#include "DynArray.h"

struct SDL_Texture;
struct Collider;

class Gun : Body
{
public:
	Gun(Module* listener, fPoint position, float mass, float weight, float height, SDL_Texture* texture, Type type);

	bool Start();

	bool Update(float dt);

	bool Draw();

	void Collision(Collider* coll);

	void CleanUp();

private:

	Animation* currentAnimation;
	Animation rightAnimation;

	SDL_Texture* tex;

	fPoint vDestination;
	float modDestination;
	fPoint normDestination;
	int x;
	int y;

	float speedX;
	float speedY;
};


#endif // __SCENE_H__
