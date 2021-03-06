#ifndef __COINS_H__
#define __COINS_H__

#include "Point.h"
#include "Entity.h"
#include "Animation.h"
#include "DynArray.h"

struct SDL_Texture;
struct Collider;

class Coins : Entity
{
public:
	Coins(Module* listener, fPoint position, SDL_Texture* texture, Type type);

	bool Start();

	bool Update(float dt);

	bool Draw();

	void Collision(Collider* coll);

	void CleanUp();



	bool collected = false;
private:
	Animation idleAnimation;

	Animation* currentAnimation;

	SDL_Texture* tex;
	int health;
	bool isJumping;
	bool gun = false;
	bool hit = false;
	bool goDown = true;
	bool goUp = false;
	bool goLeft = false;
	bool goRight = false;
};


#endif // __SCENE_H__
