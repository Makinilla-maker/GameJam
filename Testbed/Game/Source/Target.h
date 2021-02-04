#ifndef __TARGET_H__
#define __TARGET_H__

#include "Point.h"
#include "Entity.h"
#include "Animation.h"
#include "DynArray.h"

struct SDL_Texture;
struct Collider;

class Target : Entity
{
public:
	Target(Module* listener, fPoint position, SDL_Texture* texture, Type type);

	bool Start();

	bool Update(float dt);

	bool Draw();

	void Collision(Collider* coll);

	void CleanUp();

private:
	Animation idleAnimation;

	Animation* currentAnimation;

	SDL_Texture* tex;
	int health;
	bool isJumping;
	bool gun = false;
	bool hit = false;
};


#endif // __SCENE_H__
