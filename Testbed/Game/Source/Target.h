#ifndef __TARGET_H__
#define __TARGET_H__

#include "Point.h"
#include "Entity.h"
#include "Animation.h"
#include "DynArray.h"

struct SDL_Texture;
struct Collider;

class Target : Body
{
public:
	Target(Module* listener, fPoint position, float mass, float weight, float height, SDL_Texture* texture, Type type);

	bool Start();

	bool Update(float dt);

	bool Draw();

	void Collision(Collider* coll);

	void CleanUp();

private:
	Animation idleAnimation;

	Animation* currentAnimation;

	SDL_Texture* tex;

	bool isJumping;
	bool gun = false;
};


#endif // __SCENE_H__
